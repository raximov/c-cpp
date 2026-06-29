#include "geometric_objects.h"
#include <cmath>
#include <algorithm>
#include <stdexcept>

namespace s21 {

// ---- AnalyticSphere --------------------------------------------------------

std::optional<HitRecord> AnalyticSphere::Intersect(
    const Ray& ray, double t_min, double t_max) const {
  Vec3 oc = ray.origin - center_;
  double a = ray.direction.dot(ray.direction);
  double half_b = oc.dot(ray.direction);
  double c = oc.dot(oc) - radius_ * radius_;
  double disc = half_b * half_b - a * c;
  if (disc < 0) return std::nullopt;

  double sq = std::sqrt(disc);
  double t = (-half_b - sq) / a;
  if (t < t_min || t > t_max) {
    t = (-half_b + sq) / a;
    if (t < t_min || t > t_max) return std::nullopt;
  }

  HitRecord rec;
  rec.t = t;
  rec.point = ray.origin + ray.direction * t;
  Vec3 outward = (rec.point - center_) / radius_;
  rec.front_face = ray.direction.dot(outward) < 0;
  rec.normal = rec.front_face ? outward : outward * -1.0;
  return rec;
}

// ---- AnalyticCylinder ------------------------------------------------------

std::optional<HitRecord> AnalyticCylinder::Intersect(
    const Ray& ray, double t_min, double t_max) const {
  // Infinite cylinder along Y axis at base_
  Vec3 oc = Vec3{ray.origin.x - base_.x, 0, ray.origin.z - base_.z};
  Vec3 d = Vec3{ray.direction.x, 0, ray.direction.z};

  double a = d.dot(d);
  if (a < 1e-12) return std::nullopt;
  double half_b = oc.dot(d);
  double c = oc.dot(oc) - radius_ * radius_;
  double disc = half_b * half_b - a * c;
  if (disc < 0) return std::nullopt;

  double sq = std::sqrt(disc);
  for (double sign : {-1.0, 1.0}) {
    double t = (-half_b + sign * sq) / a;
    if (t < t_min || t > t_max) continue;
    Vec3 p = ray.origin + ray.direction * t;
    double y = p.y - base_.y;
    if (y < 0 || y > height_) continue;
    HitRecord rec;
    rec.t = t;
    rec.point = p;
    Vec3 outward = Vec3{p.x - base_.x, 0, p.z - base_.z} / radius_;
    rec.front_face = ray.direction.dot(outward) < 0;
    rec.normal = rec.front_face ? outward : outward * -1.0;
    return rec;
  }
  return std::nullopt;
}

// ---- AnalyticCone ----------------------------------------------------------

std::optional<HitRecord> AnalyticCone::Intersect(
    const Ray& ray, double t_min, double t_max) const {
  double k = std::tan(half_angle_);
  Vec3 co = ray.origin - apex_;
  double a = ray.direction.x * ray.direction.x
           + ray.direction.z * ray.direction.z
           - k * k * ray.direction.y * ray.direction.y;
  double b = 2 * (co.x * ray.direction.x + co.z * ray.direction.z
                  - k * k * co.y * ray.direction.y);
  double c_val = co.x*co.x + co.z*co.z - k*k*co.y*co.y;
  double disc = b*b - 4*a*c_val;
  if (disc < 0 || std::abs(a) < 1e-12) return std::nullopt;

  double sq = std::sqrt(disc);
  for (double sign : {-1.0, 1.0}) {
    double t = (-b + sign * sq) / (2 * a);
    if (t < t_min || t > t_max) continue;
    Vec3 p = ray.origin + ray.direction * t;
    double y = p.y - apex_.y;
    if (y < 0 || y > height_) continue;
    HitRecord rec;
    rec.t = t;
    rec.point = p;
    Vec3 outward = Vec3{p.x - apex_.x, -k * k * y, p.z - apex_.z}.normalized();
    rec.front_face = ray.direction.dot(outward) < 0;
    rec.normal = rec.front_face ? outward : outward * -1.0;
    return rec;
  }
  return std::nullopt;
}

// ---- AnalyticCube ----------------------------------------------------------

std::optional<HitRecord> AnalyticCube::Intersect(
    const Ray& ray, double t_min, double t_max) const {
  double t_enter = t_min, t_exit = t_max;
  Vec3 hit_normal;
  for (int axis = 0; axis < 3; ++axis) {
    double o = (axis == 0) ? ray.origin.x : (axis == 1) ? ray.origin.y : ray.origin.z;
    double d = (axis == 0) ? ray.direction.x : (axis == 1) ? ray.direction.y : ray.direction.z;
    double lo = (axis == 0) ? min_.x : (axis == 1) ? min_.y : min_.z;
    double hi = (axis == 0) ? max_.x : (axis == 1) ? max_.y : max_.z;
    if (std::abs(d) < 1e-12) {
      if (o < lo || o > hi) return std::nullopt;
      continue;
    }
    double t0 = (lo - o) / d, t1 = (hi - o) / d;
    if (t0 > t1) std::swap(t0, t1);
    if (t0 > t_enter) {
      t_enter = t0;
      Vec3 n{};
      if (axis == 0) n.x = (d < 0) ? 1.0 : -1.0;
      else if (axis == 1) n.y = (d < 0) ? 1.0 : -1.0;
      else n.z = (d < 0) ? 1.0 : -1.0;
      hit_normal = n;
    }
    t_exit = std::min(t_exit, t1);
    if (t_enter > t_exit) return std::nullopt;
  }
  if (t_enter < t_min) return std::nullopt;
  HitRecord rec;
  rec.t = t_enter;
  rec.point = ray.origin + ray.direction * t_enter;
  rec.normal = hit_normal;
  rec.front_face = true;
  return rec;
}

// ---- Polygonal factory helpers ---------------------------------------------

static void AddTriangle(ModelData& m, Vec3 a, Vec3 b, Vec3 c) {
  int base = static_cast<int>(m.vertices.size());
  m.vertices.push_back(a);
  m.vertices.push_back(b);
  m.vertices.push_back(c);
  Vec3 n = (b - a).cross(c - a).normalized();
  m.normals.push_back(n); m.normals.push_back(n); m.normals.push_back(n);
  Face f;
  f.vertex_indices = {base, base+1, base+2};
  f.normal_indices = {base, base+1, base+2};
  m.faces.push_back(f);
}

ModelData MakeSphereModel(int stacks, int slices) {
  ModelData m;
  m.file_name = "Sphere";
  for (int i = 0; i < stacks; ++i) {
    double phi0 = M_PI * i / stacks - M_PI_2;
    double phi1 = M_PI * (i + 1) / stacks - M_PI_2;
    for (int j = 0; j < slices; ++j) {
      double th0 = 2 * M_PI * j / slices;
      double th1 = 2 * M_PI * (j + 1) / slices;
      auto P = [](double phi, double th) {
        return Vec3{std::cos(phi)*std::cos(th), std::sin(phi), std::cos(phi)*std::sin(th)};
      };
      AddTriangle(m, P(phi0, th0), P(phi1, th0), P(phi1, th1));
      AddTriangle(m, P(phi0, th0), P(phi1, th1), P(phi0, th1));
    }
  }
  m.vertex_count = static_cast<int>(m.vertices.size());
  m.edge_count = stacks * slices * 2;
  return m;
}

ModelData MakeCylinderModel(int slices, double radius, double height) {
  ModelData m;
  m.file_name = "Cylinder";
  for (int i = 0; i < slices; ++i) {
    double a0 = 2*M_PI*i/slices, a1 = 2*M_PI*(i+1)/slices;
    Vec3 b0{radius*std::cos(a0), 0, radius*std::sin(a0)};
    Vec3 b1{radius*std::cos(a1), 0, radius*std::sin(a1)};
    Vec3 t0{radius*std::cos(a0), height, radius*std::sin(a0)};
    Vec3 t1{radius*std::cos(a1), height, radius*std::sin(a1)};
    AddTriangle(m, b0, b1, t0);
    AddTriangle(m, b1, t1, t0);
    // caps
    AddTriangle(m, Vec3{0,0,0}, b1, b0);
    AddTriangle(m, Vec3{0,height,0}, t0, t1);
  }
  m.vertex_count = static_cast<int>(m.vertices.size());
  m.edge_count = slices * 3;
  return m;
}

ModelData MakeConeModel(int slices, double radius, double height) {
  ModelData m;
  m.file_name = "Cone";
  Vec3 apex{0, height, 0};
  Vec3 base_center{0, 0, 0};
  for (int i = 0; i < slices; ++i) {
    double a0 = 2*M_PI*i/slices, a1 = 2*M_PI*(i+1)/slices;
    Vec3 b0{radius*std::cos(a0), 0, radius*std::sin(a0)};
    Vec3 b1{radius*std::cos(a1), 0, radius*std::sin(a1)};
    AddTriangle(m, b0, apex, b1);
    AddTriangle(m, base_center, b1, b0);
  }
  m.vertex_count = static_cast<int>(m.vertices.size());
  m.edge_count = slices * 2;
  return m;
}

ModelData MakeCubeModel(double s) {
  ModelData m;
  m.file_name = "Cube";
  double h = s / 2;
  // 6 faces, each 2 triangles
  std::vector<std::pair<Vec3,Vec3>> face_tris = {
    {{-h,-h,-h},{h,h,-h}},{{-h,-h,h},{h,h,h}},
    {{-h,-h,-h},{-h,h,h}},{{h,-h,-h},{h,h,h}},
    {{-h,-h,-h},{h,-h,h}},{{-h,h,-h},{h,h,h}},
  };
  for (auto& [mn, mx] : face_tris) {
    AddTriangle(m, {mn.x,mn.y,mn.z},{mx.x,mn.y,mn.z},{mx.x,mx.y,mn.z});
    AddTriangle(m, {mn.x,mn.y,mn.z},{mx.x,mx.y,mn.z},{mn.x,mx.y,mn.z});
  }
  m.vertex_count = 8;
  m.edge_count = 12;
  return m;
}

ModelData MakePyramidModel(int n, double radius, double height) {
  ModelData m;
  m.file_name = "Pyramid";
  Vec3 apex{0, height, 0};
  Vec3 base_c{0, 0, 0};
  for (int i = 0; i < n; ++i) {
    double a0 = 2*M_PI*i/n, a1 = 2*M_PI*(i+1)/n;
    Vec3 b0{radius*std::cos(a0), 0, radius*std::sin(a0)};
    Vec3 b1{radius*std::cos(a1), 0, radius*std::sin(a1)};
    AddTriangle(m, b0, apex, b1);
    AddTriangle(m, base_c, b1, b0);
  }
  m.vertex_count = n + 1;
  m.edge_count = n * 2;
  return m;
}

std::unique_ptr<AnalyticShape> MakeAnalyticShape(const std::string& type,
                                                  Vec3 pos,
                                                  double radius,
                                                  double height) {
  if (type == "Sphere")
    return std::make_unique<AnalyticSphere>(pos, radius);
  if (type == "Cylinder")
    return std::make_unique<AnalyticCylinder>(pos, radius, height);
  if (type == "Cone")
    return std::make_unique<AnalyticCone>(pos, std::atan(radius/height), height);
  if (type == "Cube")
    return std::make_unique<AnalyticCube>(
        Vec3{pos.x-radius, pos.y-radius, pos.z-radius},
        Vec3{pos.x+radius, pos.y+radius, pos.z+radius});
  if (type == "Pyramid")
    return std::make_unique<AnalyticCone>(pos, std::atan(radius/height), height);
  throw std::invalid_argument("Unknown shape: " + type);
}

}  // namespace s21
