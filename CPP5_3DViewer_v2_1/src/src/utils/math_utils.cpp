#include "math_utils.h"
#include <cstring>

namespace s21 {

Mat4 MathUtils::Identity() {
  Mat4 m{};
  m[0] = m[5] = m[10] = m[15] = 1.0f;
  return m;
}

Mat4 MathUtils::Multiply(const Mat4& a, const Mat4& b) {
  Mat4 result{};
  for (int col = 0; col < 4; ++col)
    for (int row = 0; row < 4; ++row)
      for (int k = 0; k < 4; ++k)
        result[col * 4 + row] += a[k * 4 + row] * b[col * 4 + k];
  return result;
}

Mat4 MathUtils::Translation(float tx, float ty, float tz) {
  Mat4 m = Identity();
  m[12] = tx;
  m[13] = ty;
  m[14] = tz;
  return m;
}

Mat4 MathUtils::RotationX(float angle_deg) {
  float r = angle_deg * M_PI / 180.0f;
  Mat4 m = Identity();
  m[5] = std::cos(r);
  m[6] = std::sin(r);
  m[9] = -std::sin(r);
  m[10] = std::cos(r);
  return m;
}

Mat4 MathUtils::RotationY(float angle_deg) {
  float r = angle_deg * M_PI / 180.0f;
  Mat4 m = Identity();
  m[0] = std::cos(r);
  m[2] = -std::sin(r);
  m[8] = std::sin(r);
  m[10] = std::cos(r);
  return m;
}

Mat4 MathUtils::RotationZ(float angle_deg) {
  float r = angle_deg * M_PI / 180.0f;
  Mat4 m = Identity();
  m[0] = std::cos(r);
  m[1] = std::sin(r);
  m[4] = -std::sin(r);
  m[5] = std::cos(r);
  return m;
}

Mat4 MathUtils::Scale(float sx, float sy, float sz) {
  Mat4 m = Identity();
  m[0] = sx;
  m[5] = sy;
  m[10] = sz;
  return m;
}

Mat4 MathUtils::Perspective(float fov_deg, float aspect, float near_z,
                             float far_z) {
  float f = 1.0f / std::tan(fov_deg * M_PI / 360.0f);
  Mat4 m{};
  m[0] = f / aspect;
  m[5] = f;
  m[10] = (far_z + near_z) / (near_z - far_z);
  m[11] = -1.0f;
  m[14] = (2.0f * far_z * near_z) / (near_z - far_z);
  return m;
}

Mat4 MathUtils::Orthographic(float left, float right, float bottom, float top,
                              float near_z, float far_z) {
  Mat4 m = Identity();
  m[0] = 2.0f / (right - left);
  m[5] = 2.0f / (top - bottom);
  m[10] = -2.0f / (far_z - near_z);
  m[12] = -(right + left) / (right - left);
  m[13] = -(top + bottom) / (top - bottom);
  m[14] = -(far_z + near_z) / (far_z - near_z);
  return m;
}

Mat4 MathUtils::LookAt(Vec3 eye, Vec3 center, Vec3 up) {
  Vec3 f = Normalize(Subtract(center, eye));
  Vec3 s = Normalize(Cross(f, up));
  Vec3 u = Cross(s, f);
  Mat4 m = Identity();
  m[0] = s[0]; m[4] = s[1]; m[8]  = s[2];
  m[1] = u[0]; m[5] = u[1]; m[9]  = u[2];
  m[2] = -f[0]; m[6] = -f[1]; m[10] = -f[2];
  m[12] = -Dot(s, eye);
  m[13] = -Dot(u, eye);
  m[14] =  Dot(f, eye);
  return m;
}

Vec3 MathUtils::Normalize(Vec3 v) {
  float len = std::sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
  if (len < 1e-8f) return {0, 0, 0};
  return {v[0]/len, v[1]/len, v[2]/len};
}

Vec3 MathUtils::Cross(Vec3 a, Vec3 b) {
  return {a[1]*b[2] - a[2]*b[1],
          a[2]*b[0] - a[0]*b[2],
          a[0]*b[1] - a[1]*b[0]};
}

float MathUtils::Dot(Vec3 a, Vec3 b) {
  return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

Vec3 MathUtils::Subtract(Vec3 a, Vec3 b) {
  return {a[0]-b[0], a[1]-b[1], a[2]-b[2]};
}

Vec4 MathUtils::MultiplyVec4(const Mat4& m, Vec4 v) {
  Vec4 result{};
  for (int row = 0; row < 4; ++row)
    for (int col = 0; col < 4; ++col)
      result[row] += m[col * 4 + row] * v[col];
  return result;
}

}  // namespace s21
