#pragma once
#include "model_data.h"
#include <array>

namespace s21 {

// 4x4 matrix stored row-major
using Matrix4x4 = std::array<std::array<double, 4>, 4>;

class AffineTransform {
 public:
  static Matrix4x4 Identity();
  static Matrix4x4 Translation(double tx, double ty, double tz);
  static Matrix4x4 RotationX(double angle_rad);
  static Matrix4x4 RotationY(double angle_rad);
  static Matrix4x4 RotationZ(double angle_rad);
  static Matrix4x4 Scale(double sx, double sy, double sz);
  static Matrix4x4 Multiply(const Matrix4x4& a, const Matrix4x4& b);

  // Apply transform to a set of vertices in-place
  static void ApplyToVertices(const Matrix4x4& m, std::vector<Vec3>& vertices);
  static void ApplyToNormals(const Matrix4x4& m, std::vector<Vec3>& normals);

  // Convenience: transform single point / direction
  static Vec3 TransformPoint(const Matrix4x4& m, const Vec3& p);
  static Vec3 TransformDirection(const Matrix4x4& m, const Vec3& d);
};

}  // namespace s21
