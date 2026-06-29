#pragma once
#include "model_data.h"
#include "camera.h"
#include "light.h"
#include "kd_tree.h"
#include "geometric_objects.h"
#include <vector>
#include <string>
#include <functional>

namespace s21 {

struct RenderSettings {
  int width  = 1920;
  int height = 1440;
  int max_depth = 5;   // ray bounces
  int samples  = 1;    // rays per pixel (anti-aliasing)
};

// RGBA pixel buffer
using PixelBuffer = std::vector<uint8_t>;

class RayTracer {
 public:
  // progress_cb receives 0..100
  PixelBuffer Render(
      const std::vector<ModelData>& models,
      const std::vector<MaterialProperties>& materials,
      const std::vector<std::unique_ptr<AnalyticShape>>& analytic,
      const LightManager& lights,
      const Camera& camera,
      const RenderSettings& settings,
      std::function<void(int)> progress_cb = nullptr);

 private:
  Color TraceRay(const Ray& ray,
                 int depth,
                 const KDTree& tree,
                 const std::vector<std::unique_ptr<AnalyticShape>>& analytic,
                 const std::vector<MaterialProperties>& materials,
                 const LightManager& lights) const;

  Color Shade(const HitRecord& hit,
              const Vec3& ray_dir,
              int depth,
              const KDTree& tree,
              const std::vector<std::unique_ptr<AnalyticShape>>& analytic,
              const std::vector<MaterialProperties>& materials,
              const LightManager& lights,
              const MaterialProperties& mat) const;

  bool IsInShadow(const Vec3& point,
                  const Vec3& light_dir,
                  double light_dist,
                  const KDTree& tree,
                  const std::vector<std::unique_ptr<AnalyticShape>>& analytic) const;

  Vec3 Reflect(const Vec3& v, const Vec3& n) const;
  Vec3 Refract(const Vec3& v, const Vec3& n, double eta) const;

  // Build KD-tree from model list
  KDTree BuildTree(const std::vector<ModelData>& models) const;
};

// Save pixel buffer to file (bmp/jpg/png) using stb_image_write
bool SaveImage(const PixelBuffer& buf, int w, int h, const std::string& path);

}  // namespace s21
