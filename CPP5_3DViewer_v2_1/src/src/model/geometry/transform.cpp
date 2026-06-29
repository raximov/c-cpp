#include "transform.h"

namespace s21 {

Transform::Transform() : tx_(0), ty_(0), tz_(0), rx_(0), ry_(0), rz_(0), scale_(1.0f) {}

void Transform::SetTranslation(float x, float y, float z) {
  tx_ = x; ty_ = y; tz_ = z;
}

void Transform::SetRotation(float rx, float ry, float rz) {
  rx_ = rx; ry_ = ry; rz_ = rz;
}

void Transform::SetScale(float s) {
  scale_ = (s > 1e-6f) ? s : 1e-6f;
}

Mat4 Transform::GetModelMatrix() const {
  Mat4 T = MathUtils::Translation(tx_, ty_, tz_);
  Mat4 Rx = MathUtils::RotationX(rx_);
  Mat4 Ry = MathUtils::RotationY(ry_);
  Mat4 Rz = MathUtils::RotationZ(rz_);
  Mat4 S = MathUtils::Scale(scale_, scale_, scale_);

  // TRS order: first scale, then rotate, then translate
  Mat4 rot = MathUtils::Multiply(Rz, MathUtils::Multiply(Ry, Rx));
  return MathUtils::Multiply(T, MathUtils::Multiply(rot, S));
}

void Transform::Reset() {
  tx_ = ty_ = tz_ = rx_ = ry_ = rz_ = 0;
  scale_ = 1.0f;
}

}  // namespace s21
