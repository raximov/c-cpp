#include "camera.h"
#include <cmath>

namespace s21 {

Camera::Camera() = default;

Ray Camera::GenerateRay(double u, double v, double aspect_ratio) const {
  Vec3 forward = (target_ - position_).normalized();
  Vec3 right = forward.cross(up_).normalized();
  Vec3 cam_up = right.cross(forward);

  double half_h = std::tan(fov_deg_ * M_PI / 360.0);
  double half_w = half_h * aspect_ratio;

  // Map [0,1] -> [-1,1]
  double su = (2.0 * u - 1.0) * half_w;
  double sv = (1.0 - 2.0 * v) * half_h;

  Ray ray;
  if (projection_ == ProjectionType::kCentral) {
    ray.origin = position_;
    ray.direction = (forward + right * su + cam_up * sv).normalized();
  } else {
    // Parallel projection
    ray.origin = position_ + right * su + cam_up * sv;
    ray.direction = forward;
  }
  return ray;
}

}  // namespace s21
