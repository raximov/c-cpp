#include <gtest/gtest.h>
#include <cmath>
#include "../model/geometry/transform.h"
#include "../utils/math_utils.h"

namespace s21 {

TEST(TransformTest, DefaultIsIdentity) {
  Transform t;
  Mat4 m = t.GetModelMatrix();
  Mat4 id = MathUtils::Identity();
  for (int i = 0; i < 16; ++i)
    EXPECT_NEAR(m[i], id[i], 1e-5f) << "at index " << i;
}

TEST(TransformTest, Translation) {
  Transform t;
  t.SetTranslation(1.0f, 2.0f, 3.0f);
  Mat4 m = t.GetModelMatrix();
  // Column-major: translation is at [12],[13],[14]
  EXPECT_NEAR(m[12], 1.0f, 1e-5f);
  EXPECT_NEAR(m[13], 2.0f, 1e-5f);
  EXPECT_NEAR(m[14], 3.0f, 1e-5f);
}

TEST(TransformTest, ScaleApplied) {
  Transform t;
  t.SetScale(2.0f);
  Mat4 m = t.GetModelMatrix();
  EXPECT_NEAR(m[0], 2.0f, 1e-5f);
  EXPECT_NEAR(m[5], 2.0f, 1e-5f);
  EXPECT_NEAR(m[10], 2.0f, 1e-5f);
}

TEST(TransformTest, ScaleClampedPositive) {
  Transform t;
  t.SetScale(-1.0f);  // should clamp to tiny positive
  EXPECT_GT(t.GetScale(), 0.0f);
}

TEST(TransformTest, Reset) {
  Transform t;
  t.SetTranslation(5, 5, 5);
  t.SetRotation(45, 45, 45);
  t.SetScale(3.0f);
  t.Reset();
  EXPECT_NEAR(t.GetTranslationX(), 0.0f, 1e-6f);
  EXPECT_NEAR(t.GetScale(), 1.0f, 1e-6f);
  Mat4 m = t.GetModelMatrix();
  Mat4 id = MathUtils::Identity();
  for (int i = 0; i < 16; ++i)
    EXPECT_NEAR(m[i], id[i], 1e-5f);
}

TEST(TransformTest, RotationXAt90) {
  // Rotating point (0,1,0) by 90° around X should give ~(0,0,1)
  Transform t;
  t.SetRotation(90.0f, 0.0f, 0.0f);
  Mat4 m = t.GetModelMatrix();
  Vec4 p = MathUtils::MultiplyVec4(m, {0.0f, 1.0f, 0.0f, 1.0f});
  EXPECT_NEAR(p[0], 0.0f, 1e-4f);
  EXPECT_NEAR(p[1], 0.0f, 1e-4f);
  EXPECT_NEAR(p[2], 1.0f, 1e-4f);
}

TEST(MathUtilsTest, NormalizeUnit) {
  Vec3 v = MathUtils::Normalize({3.0f, 0.0f, 0.0f});
  EXPECT_NEAR(v[0], 1.0f, 1e-6f);
  EXPECT_NEAR(v[1], 0.0f, 1e-6f);
  EXPECT_NEAR(v[2], 0.0f, 1e-6f);
}

TEST(MathUtilsTest, CrossProduct) {
  Vec3 x = {1.0f, 0.0f, 0.0f};
  Vec3 y = {0.0f, 1.0f, 0.0f};
  Vec3 z = MathUtils::Cross(x, y);
  EXPECT_NEAR(z[0], 0.0f, 1e-6f);
  EXPECT_NEAR(z[1], 0.0f, 1e-6f);
  EXPECT_NEAR(z[2], 1.0f, 1e-6f);
}

TEST(MathUtilsTest, MatrixMultiplyIdentity) {
  Mat4 id = MathUtils::Identity();
  Mat4 T = MathUtils::Translation(1, 2, 3);
  Mat4 r = MathUtils::Multiply(id, T);
  for (int i = 0; i < 16; ++i)
    EXPECT_NEAR(r[i], T[i], 1e-6f);
}

}  // namespace s21
