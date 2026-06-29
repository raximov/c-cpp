#pragma once
#include <array>
#include <cmath>

namespace s21 {

// 4x4 matrix stored in column-major order (OpenGL convention)
using Mat4 = std::array<float, 16>;
using Vec3 = std::array<float, 3>;
using Vec4 = std::array<float, 4>;

class MathUtils {
 public:
  static Mat4 Identity();
  static Mat4 Multiply(const Mat4& a, const Mat4& b);
  static Mat4 Translation(float tx, float ty, float tz);
  static Mat4 RotationX(float angle_deg);
  static Mat4 RotationY(float angle_deg);
  static Mat4 RotationZ(float angle_deg);
  static Mat4 Scale(float sx, float sy, float sz);
  static Mat4 Perspective(float fov_deg, float aspect, float near_z, float far_z);
  static Mat4 Orthographic(float left, float right, float bottom, float top,
                            float near_z, float far_z);
  static Mat4 LookAt(Vec3 eye, Vec3 center, Vec3 up);
  static Vec3 Normalize(Vec3 v);
  static Vec3 Cross(Vec3 a, Vec3 b);
  static float Dot(Vec3 a, Vec3 b);
  static Vec3 Subtract(Vec3 a, Vec3 b);
  static Vec4 MultiplyVec4(const Mat4& m, Vec4 v);
};

}  // namespace s21
