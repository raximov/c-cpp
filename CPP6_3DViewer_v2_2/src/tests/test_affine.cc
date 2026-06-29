#include <gtest/gtest.h>
#include "../model/affine_transform.h"
#include <cmath>

namespace s21 {

static const double kEps = 1e-9;

TEST(AffineTransform, Identity) {
  auto m = AffineTransform::Identity();
  Vec3 p{1, 2, 3};
  Vec3 r = AffineTransform::TransformPoint(m, p);
  EXPECT_NEAR(r.x, 1.0, kEps);
  EXPECT_NEAR(r.y, 2.0, kEps);
  EXPECT_NEAR(r.z, 3.0, kEps);
}

TEST(AffineTransform, Translation) {
  auto m = AffineTransform::Translation(1, 2, 3);
  Vec3 p{0, 0, 0};
  Vec3 r = AffineTransform::TransformPoint(m, p);
  EXPECT_NEAR(r.x, 1.0, kEps);
  EXPECT_NEAR(r.y, 2.0, kEps);
  EXPECT_NEAR(r.z, 3.0, kEps);
}

TEST(AffineTransform, RotationX90) {
  auto m = AffineTransform::RotationX(M_PI_2);
  Vec3 p{0, 1, 0};
  Vec3 r = AffineTransform::TransformPoint(m, p);
  EXPECT_NEAR(r.x, 0.0, kEps);
  EXPECT_NEAR(r.y, 0.0, kEps);
  EXPECT_NEAR(r.z, 1.0, kEps);
}

TEST(AffineTransform, RotationY90) {
  auto m = AffineTransform::RotationY(M_PI_2);
  Vec3 p{1, 0, 0};
  Vec3 r = AffineTransform::TransformPoint(m, p);
  EXPECT_NEAR(r.x, 0.0, kEps);
  EXPECT_NEAR(r.y, 0.0, kEps);
  EXPECT_NEAR(r.z, -1.0, kEps);
}

TEST(AffineTransform, RotationZ90) {
  auto m = AffineTransform::RotationZ(M_PI_2);
  Vec3 p{1, 0, 0};
  Vec3 r = AffineTransform::TransformPoint(m, p);
  EXPECT_NEAR(r.x, 0.0, kEps);
  EXPECT_NEAR(r.y, 1.0, kEps);
  EXPECT_NEAR(r.z, 0.0, kEps);
}

TEST(AffineTransform, Scale) {
  auto m = AffineTransform::Scale(2, 3, 4);
  Vec3 p{1, 1, 1};
  Vec3 r = AffineTransform::TransformPoint(m, p);
  EXPECT_NEAR(r.x, 2.0, kEps);
  EXPECT_NEAR(r.y, 3.0, kEps);
  EXPECT_NEAR(r.z, 4.0, kEps);
}

TEST(AffineTransform, Multiply) {
  auto t  = AffineTransform::Translation(1, 0, 0);
  auto sc = AffineTransform::Scale(2, 2, 2);
  // Scale then Translate
  auto m = AffineTransform::Multiply(t, sc);
  Vec3 p{1, 0, 0};
  Vec3 r = AffineTransform::TransformPoint(m, p);
  EXPECT_NEAR(r.x, 3.0, kEps);  // 1*2 + 1
}

TEST(AffineTransform, ApplyToVertices) {
  auto m = AffineTransform::Translation(1, 1, 1);
  std::vector<Vec3> verts{{0,0,0},{1,0,0}};
  AffineTransform::ApplyToVertices(m, verts);
  EXPECT_NEAR(verts[0].x, 1.0, kEps);
  EXPECT_NEAR(verts[1].x, 2.0, kEps);
}

TEST(Vec3, Dot) {
  Vec3 a{1, 0, 0}, b{0, 1, 0};
  EXPECT_NEAR(a.dot(b), 0.0, kEps);
  Vec3 c{1, 0, 0};
  EXPECT_NEAR(a.dot(c), 1.0, kEps);
}

TEST(Vec3, Cross) {
  Vec3 a{1,0,0}, b{0,1,0};
  Vec3 c = a.cross(b);
  EXPECT_NEAR(c.x, 0.0, kEps);
  EXPECT_NEAR(c.y, 0.0, kEps);
  EXPECT_NEAR(c.z, 1.0, kEps);
}

TEST(Vec3, Length) {
  Vec3 a{3, 4, 0};
  EXPECT_NEAR(a.length(), 5.0, kEps);
}

TEST(Vec3, Normalized) {
  Vec3 a{3, 4, 0};
  Vec3 n = a.normalized();
  EXPECT_NEAR(n.length(), 1.0, kEps);
}

}  // namespace s21
