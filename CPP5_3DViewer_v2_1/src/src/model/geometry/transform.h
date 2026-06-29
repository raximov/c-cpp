#pragma once
#include "../../utils/math_utils.h"

namespace s21 {

// Command pattern: each transform action is recorded
enum class ProjectionType { kPerspective, kOrthographic };

class Transform {
 public:
  Transform();

  void SetTranslation(float x, float y, float z);
  void SetRotation(float rx, float ry, float rz);
  void SetScale(float s);

  float GetTranslationX() const { return tx_; }
  float GetTranslationY() const { return ty_; }
  float GetTranslationZ() const { return tz_; }
  float GetRotationX() const { return rx_; }
  float GetRotationY() const { return ry_; }
  float GetRotationZ() const { return rz_; }
  float GetScale() const { return scale_; }

  Mat4 GetModelMatrix() const;
  void Reset();

 private:
  float tx_, ty_, tz_;
  float rx_, ry_, rz_;
  float scale_;
};

}  // namespace s21
