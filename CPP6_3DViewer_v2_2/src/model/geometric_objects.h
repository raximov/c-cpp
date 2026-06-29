#pragma once
#include "model_data.h"
#include "camera.h"
#include <optional>
#include <memory>
#include <string>

namespace s21 {

struct HitRecord {
  double t = 0.0;
  Vec3 point;
  Vec3 normal;
  bool front_face = true;
};

// Abstract base for analytically described objects (for ray tracing)
class AnalyticShape {
 public:
  virtual ~AnalyticShape() = default;
  // Returns closest intersection > t_min, or nullopt
  virtual std::optional<HitRecord> Intersect(const Ray& ray,
                                              double t_min,
                                              double t_max) const = 0;
  virtual std::string Name() const = 0;
};

class AnalyticSphere : public AnalyticShape {
 public:
  AnalyticSphere(Vec3 center, double radius)
      : center_(center), radius_(radius) {}
  std::optional<HitRecord> Intersect(const Ray& ray,
                                     double t_min,
                                     double t_max) const override;
  std::string Name() const override { return "Sphere"; }
 private:
  Vec3 center_;
  double radius_;
};

class AnalyticCylinder : public AnalyticShape {
 public:
  AnalyticCylinder(Vec3 base, double radius, double height)
      : base_(base), radius_(radius), height_(height) {}
  std::optional<HitRecord> Intersect(const Ray& ray,
                                     double t_min,
                                     double t_max) const override;
  std::string Name() const override { return "Cylinder"; }
 private:
  Vec3 base_;
  double radius_, height_;
};

class AnalyticCone : public AnalyticShape {
 public:
  AnalyticCone(Vec3 apex, double half_angle, double height)
      : apex_(apex), half_angle_(half_angle), height_(height) {}
  std::optional<HitRecord> Intersect(const Ray& ray,
                                     double t_min,
                                     double t_max) const override;
  std::string Name() const override { return "Cone"; }
 private:
  Vec3 apex_;
  double half_angle_, height_;
};

class AnalyticCube : public AnalyticShape {
 public:
  AnalyticCube(Vec3 min, Vec3 max) : min_(min), max_(max) {}
  std::optional<HitRecord> Intersect(const Ray& ray,
                                     double t_min,
                                     double t_max) const override;
  std::string Name() const override { return "Cube"; }
 private:
  Vec3 min_, max_;
};

// Factory: build polygonal ModelData approximation of standard shapes
ModelData MakeSphereModel(int stacks, int slices);
ModelData MakeCylinderModel(int slices, double radius, double height);
ModelData MakeConeModel(int slices, double radius, double height);
ModelData MakeCubeModel(double size);
ModelData MakePyramidModel(int base_n, double radius, double height);

// Build analytic shape paired with a model name tag
std::unique_ptr<AnalyticShape> MakeAnalyticShape(const std::string& type,
                                                  Vec3 position,
                                                  double radius,
                                                  double height);

}  // namespace s21
