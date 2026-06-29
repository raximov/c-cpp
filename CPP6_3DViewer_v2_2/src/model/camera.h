#pragma once
#include "model_data.h"

namespace s21 {

struct Ray {
  Vec3 origin;
  Vec3 direction;
};

class Camera {
 public:
  Camera();

  void SetPosition(const Vec3& pos) { position_ = pos; }
  void SetTarget(const Vec3& target) { target_ = target; }
  void SetUp(const Vec3& up) { up_ = up_; }
  void SetFov(double fov_deg) { fov_deg_ = fov_deg; }
  void SetProjection(ProjectionType type) { projection_ = type; }

  const Vec3& GetPosition() const { return position_; }
  const Vec3& GetTarget() const { return target_; }
  ProjectionType GetProjection() const { return projection_; }

  // Generate ray for pixel (u,v) in [0,1]x[0,1]
  Ray GenerateRay(double u, double v, double aspect_ratio) const;

 private:
  Vec3 position_{0.0, 0.0, 5.0};
  Vec3 target_{0.0, 0.0, 0.0};
  Vec3 up_{0.0, 1.0, 0.0};
  double fov_deg_ = 60.0;
  ProjectionType projection_ = ProjectionType::kCentral;
};

}  // namespace s21
