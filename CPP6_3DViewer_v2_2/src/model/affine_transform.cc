#include "affine_transform.h"
#include <cmath>

namespace s21 {

Matrix4x4 AffineTransform::Identity() {
  Matrix4x4 m{};
  for (int i = 0; i < 4; ++i) m[i][i] = 1.0;
  return m;
}

Matrix4x4 AffineTransform::Translation(double tx, double ty, double tz) {
  auto m = Identity();
  m[0][3] = tx;
  m[1][3] = ty;
  m[2][3] = tz;
  return m;
}

Matrix4x4 AffineTransform::RotationX(double a) {
  auto m = Identity();
  m[1][1] =  std::cos(a); m[1][2] = -std::sin(a);
  m[2][1] =  std::sin(a); m[2][2] =  std::cos(a);
  return m;
}

Matrix4x4 AffineTransform::RotationY(double a) {
  auto m = Identity();
  m[0][0] =  std::cos(a); m[0][2] =  std::sin(a);
  m[2][0] = -std::sin(a); m[2][2] =  std::cos(a);
  return m;
}

Matrix4x4 AffineTransform::RotationZ(double a) {
  auto m = Identity();
  m[0][0] =  std::cos(a); m[0][1] = -std::sin(a);
  m[1][0] =  std::sin(a); m[1][1] =  std::cos(a);
  return m;
}

Matrix4x4 AffineTransform::Scale(double sx, double sy, double sz) {
  auto m = Identity();
  m[0][0] = sx; m[1][1] = sy; m[2][2] = sz;
  return m;
}

Matrix4x4 AffineTransform::Multiply(const Matrix4x4& a, const Matrix4x4& b) {
  Matrix4x4 c{};
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      for (int k = 0; k < 4; ++k)
        c[i][j] += a[i][k] * b[k][j];
  return c;
}

Vec3 AffineTransform::TransformPoint(const Matrix4x4& m, const Vec3& p) {
  double x = m[0][0]*p.x + m[0][1]*p.y + m[0][2]*p.z + m[0][3];
  double y = m[1][0]*p.x + m[1][1]*p.y + m[1][2]*p.z + m[1][3];
  double z = m[2][0]*p.x + m[2][1]*p.y + m[2][2]*p.z + m[2][3];
  return {x, y, z};
}

Vec3 AffineTransform::TransformDirection(const Matrix4x4& m, const Vec3& d) {
  double x = m[0][0]*d.x + m[0][1]*d.y + m[0][2]*d.z;
  double y = m[1][0]*d.x + m[1][1]*d.y + m[1][2]*d.z;
  double z = m[2][0]*d.x + m[2][1]*d.y + m[2][2]*d.z;
  return Vec3{x, y, z}.normalized();
}

void AffineTransform::ApplyToVertices(const Matrix4x4& m, std::vector<Vec3>& verts) {
  for (auto& v : verts) v = TransformPoint(m, v);
}

void AffineTransform::ApplyToNormals(const Matrix4x4& m, std::vector<Vec3>& normals) {
  for (auto& n : normals) n = TransformDirection(m, n);
}

}  // namespace s21
