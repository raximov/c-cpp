#include "ray_tracer.h"
#include <cmath>
#include <algorithm>
#include <thread>
#include <mutex>
#include <atomic>

// stb_image_write (header-only) – bundled inline
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../utils/stb_image_write.h"

namespace s21 {

// ---- Helpers ---------------------------------------------------------------

static double ColorComp(float c) { return static_cast<double>(c); }
static uint8_t Clamp255(double v) {
  return static_cast<uint8_t>(std::clamp(v * 255.0, 0.0, 255.0));
}

Vec3 RayTracer::Reflect(const Vec3& v, const Vec3& n) const {
  return v - n * (2.0 * v.dot(n));
}

Vec3 RayTracer::Refract(const Vec3& v, const Vec3& n, double eta) const {
  double cos_i = -v.dot(n);
  double sin2_t = eta * eta * (1.0 - cos_i * cos_i);
  if (sin2_t > 1.0) return Reflect(v, n);
  return v * eta + n * (eta * cos_i - std::sqrt(1.0 - sin2_t));
}

// ---- KD-tree build ---------------------------------------------------------

KDTree RayTracer::BuildTree(const std::vector<ModelData>& models) const {
  std::vector<TrianglePrimitive> prims;
  for (int mi = 0; mi < static_cast<int>(models.size()); ++mi) {
    const auto& m = models[mi];
    for (const auto& face : m.faces) {
      int n = static_cast<int>(face.vertex_indices.size());
      for (int i = 1; i < n - 1; ++i) {
        TrianglePrimitive tri;
        tri.model_index = mi;
        int i0 = face.vertex_indices[0];
        int i1 = face.vertex_indices[i];
        int i2 = face.vertex_indices[i + 1];
        if (i0 < 0 || i0 >= static_cast<int>(m.vertices.size())) continue;
        if (i1 < 0 || i1 >= static_cast<int>(m.vertices.size())) continue;
        if (i2 < 0 || i2 >= static_cast<int>(m.vertices.size())) continue;
        tri.v0 = m.vertices[i0];
        tri.v1 = m.vertices[i1];
        tri.v2 = m.vertices[i2];
        // normals
        auto GetNorm = [&](int ni_idx) -> Vec3 {
          if (!face.normal_indices.empty() &&
              ni_idx < static_cast<int>(face.normal_indices.size())) {
            int ni = face.normal_indices[ni_idx];
            if (ni >= 0 && ni < static_cast<int>(m.normals.size()))
              return m.normals[ni];
          }
          return (tri.v1 - tri.v0).cross(tri.v2 - tri.v0).normalized();
        };
        tri.n0 = GetNorm(0);
        tri.n1 = GetNorm(i);
        tri.n2 = GetNorm(i + 1);
        prims.push_back(tri);
      }
    }
  }
  KDTree tree;
  tree.Build(std::move(prims));
  return tree;
}

// ---- Shadow test -----------------------------------------------------------

bool RayTracer::IsInShadow(
    const Vec3& point, const Vec3& light_dir, double light_dist,
    const KDTree& tree,
    const std::vector<std::unique_ptr<AnalyticShape>>& analytic) const {
  Ray shadow_ray{point + light_dir * 1e-4, light_dir};
  if (tree.Intersect(shadow_ray, 1e-4, light_dist)) return true;
  for (const auto& shape : analytic) {
    if (shape->Intersect(shadow_ray, 1e-4, light_dist)) return true;
  }
  return false;
}

// ---- Shade -----------------------------------------------------------------

Color RayTracer::Shade(
    const HitRecord& hit, const Vec3& ray_dir, int depth,
    const KDTree& tree,
    const std::vector<std::unique_ptr<AnalyticShape>>& analytic,
    const std::vector<MaterialProperties>& materials,
    const LightManager& lights,
    const MaterialProperties& mat) const {
  Color result{0, 0, 0, 1};
  // Ambient
  const auto& amb = lights.GetAmbient();
  result.r += amb.color.r * amb.intensity * mat.base_color.r;
  result.g += amb.color.g * amb.intensity * mat.base_color.g;
  result.b += amb.color.b * amb.intensity * mat.base_color.b;

  auto AddLight = [&](const Vec3& light_pos, const Color& lc, float intensity) {
    Vec3 to_light = (light_pos - hit.point);
    double dist = to_light.length();
    Vec3 light_dir = to_light / dist;
    if (IsInShadow(hit.point, light_dir, dist, tree, analytic)) return;
    double diff = std::max(0.0, hit.normal.dot(light_dir));
    Vec3 reflect_dir = Reflect(light_dir * -1.0, hit.normal);
    double spec = std::pow(std::max(0.0, reflect_dir.dot(ray_dir * -1.0)),
                           16.0 * (1.0 - mat.roughness));
    float atten = intensity / static_cast<float>(1.0 + 0.1 * dist * dist);
    result.r += (diff * lc.r * mat.base_color.r + spec * lc.r) * atten;
    result.g += (diff * lc.g * mat.base_color.g + spec * lc.g) * atten;
    result.b += (diff * lc.b * mat.base_color.b + spec * lc.b) * atten;
  };

  const auto& dir = lights.GetDirectional();
  Vec3 dir_pos = hit.point + Vec3{dir.position.x, dir.position.y, dir.position.z} * 1000;
  AddLight(dir_pos, dir.color, dir.intensity);
  for (const auto& pt : lights.GetPointLights()) AddLight(pt.position, pt.color, pt.intensity);

  // Reflection
  if (mat.reflectivity > 0.01f && depth > 0) {
    Vec3 refl_dir = Reflect(ray_dir, hit.normal).normalized();
    Ray refl_ray{hit.point + refl_dir * 1e-4, refl_dir};
    Color refl_color = TraceRay(refl_ray, depth - 1, tree, analytic, materials, lights);
    result.r += refl_color.r * mat.reflectivity;
    result.g += refl_color.g * mat.reflectivity;
    result.b += refl_color.b * mat.reflectivity;
  }

  // Refraction / transparency
  if (mat.transparency > 0.01f && depth > 0) {
    double eta = 1.0 / static_cast<double>(mat.refraction_index);
    Vec3 refr_dir = Refract(ray_dir, hit.normal, eta).normalized();
    Ray refr_ray{hit.point + refr_dir * 1e-4, refr_dir};
    Color refr_color = TraceRay(refr_ray, depth - 1, tree, analytic, materials, lights);
    float t = mat.transparency;
    result.r = result.r * (1 - t) + refr_color.r * t;
    result.g = result.g * (1 - t) + refr_color.g * t;
    result.b = result.b * (1 - t) + refr_color.b * t;
  }

  return result;
}

// ---- TraceRay --------------------------------------------------------------

Color RayTracer::TraceRay(
    const Ray& ray, int depth,
    const KDTree& tree,
    const std::vector<std::unique_ptr<AnalyticShape>>& analytic,
    const std::vector<MaterialProperties>& materials,
    const LightManager& lights) const {
  if (depth <= 0) return {0, 0, 0, 1};

  std::optional<HitRecord> closest;
  int hit_model = 0;
  bool hit_analytic = false;
  int analytic_idx = -1;

  auto mesh_hit = tree.Intersect(ray, 1e-4, 1e9);
  if (mesh_hit) {
    closest = mesh_hit;
  }

  for (int i = 0; i < static_cast<int>(analytic.size()); ++i) {
    double t_max = closest ? closest->t : 1e9;
    auto ah = analytic[i]->Intersect(ray, 1e-4, t_max);
    if (ah) {
      closest = ah;
      hit_analytic = true;
      analytic_idx = i;
    }
  }

  if (!closest) {
    // Sky gradient
    double t = 0.5 * (ray.direction.y + 1.0);
    return Color{static_cast<float>(0.5*(1-t) + 0.7*t),
                 static_cast<float>(0.5*(1-t) + 0.8*t),
                 static_cast<float>(1.0f), 1.0f};
  }

  const MaterialProperties& mat = (!materials.empty())
      ? materials[std::min(hit_model, static_cast<int>(materials.size())-1)]
      : MaterialProperties{};

  return Shade(*closest, ray.direction, depth, tree, analytic, materials, lights, mat);
}

// ---- Render ----------------------------------------------------------------

PixelBuffer RayTracer::Render(
    const std::vector<ModelData>& models,
    const std::vector<MaterialProperties>& materials,
    const std::vector<std::unique_ptr<AnalyticShape>>& analytic,
    const LightManager& lights,
    const Camera& camera,
    const RenderSettings& settings,
    std::function<void(int)> progress_cb) {
  int W = settings.width, H = settings.height;
  PixelBuffer buf(W * H * 3, 0);

  KDTree tree = BuildTree(models);
  double aspect = static_cast<double>(W) / H;

  std::atomic<int> rows_done{0};
  std::mutex buf_mutex;

  auto render_row = [&](int y) {
    for (int x = 0; x < W; ++x) {
      double r_acc = 0, g_acc = 0, b_acc = 0;
      for (int s = 0; s < settings.samples; ++s) {
        double u = (x + 0.5) / W;
        double v = (y + 0.5) / H;
        Ray ray = camera.GenerateRay(u, v, aspect);
        Color c = TraceRay(ray, settings.max_depth, tree, analytic, materials, lights);
        r_acc += c.r; g_acc += c.g; b_acc += c.b;
      }
      int idx = (y * W + x) * 3;
      buf[idx]   = Clamp255(r_acc / settings.samples);
      buf[idx+1] = Clamp255(g_acc / settings.samples);
      buf[idx+2] = Clamp255(b_acc / settings.samples);
    }
    int done = ++rows_done;
    if (progress_cb) progress_cb(done * 100 / H);
  };

  // Multi-threaded row rendering
  unsigned int nthreads = std::max(1u, std::thread::hardware_concurrency());
  std::vector<std::thread> threads;
  std::atomic<int> next_row{0};

  for (unsigned int i = 0; i < nthreads; ++i) {
    threads.emplace_back([&]() {
      while (true) {
        int row = next_row.fetch_add(1);
        if (row >= H) break;
        render_row(row);
      }
    });
  }
  for (auto& t : threads) t.join();

  return buf;
}

// ---- Save image ------------------------------------------------------------

bool SaveImage(const PixelBuffer& buf, int w, int h, const std::string& path) {
  if (path.ends_with(".png"))
    return stbi_write_png(path.c_str(), w, h, 3, buf.data(), w*3) != 0;
  if (path.ends_with(".jpg") || path.ends_with(".jpeg"))
    return stbi_write_jpg(path.c_str(), w, h, 3, buf.data(), 90) != 0;
  if (path.ends_with(".bmp"))
    return stbi_write_bmp(path.c_str(), w, h, 3, buf.data()) != 0;
  return false;
}

}  // namespace s21
