#include <gtest/gtest.h>
#include "../model/scene.h"
#include <fstream>

namespace s21 {

static std::string MakeTempObj() {
  std::string path = "/tmp/scene_test.obj";
  std::ofstream f(path);
  f << "v 0 0 0\nv 1 0 0\nv 0 1 0\nf 1 2 3\n";
  return path;
}

TEST(Scene, InitialState) {
  Scene s;
  EXPECT_EQ(s.GetModelCount(), 0);
  EXPECT_EQ(s.GetActiveModel(), 0);
}

TEST(Scene, LoadObjModel) {
  Scene s;
  std::string path = MakeTempObj();
  EXPECT_TRUE(s.LoadObjModel(path));
  EXPECT_EQ(s.GetModelCount(), 1);
}

TEST(Scene, MaxModels) {
  Scene s;
  std::string path = MakeTempObj();
  for (int i = 0; i < 6; ++i) EXPECT_TRUE(s.LoadObjModel(path));
  EXPECT_FALSE(s.LoadObjModel(path));  // 7th should fail
}

TEST(Scene, RemoveModel) {
  Scene s;
  std::string path = MakeTempObj();
  s.LoadObjModel(path);
  EXPECT_EQ(s.GetModelCount(), 1);
  EXPECT_TRUE(s.RemoveModel(0));
  EXPECT_EQ(s.GetModelCount(), 0);
}

TEST(Scene, RemoveInvalidIndex) {
  Scene s;
  EXPECT_FALSE(s.RemoveModel(0));
  EXPECT_FALSE(s.RemoveModel(-1));
}

TEST(Scene, AddPrimitive) {
  Scene s;
  EXPECT_TRUE(s.AddPrimitive("Sphere", {0,0,0}));
  EXPECT_EQ(s.GetModelCount(), 1);
  EXPECT_EQ(s.GetModel(0).shape_type, "Sphere");
}

TEST(Scene, AddPrimitiveAllTypes) {
  Scene s;
  EXPECT_TRUE(s.AddPrimitive("Sphere",   {0,0,0}));
  EXPECT_TRUE(s.AddPrimitive("Cylinder", {0,0,0}));
  EXPECT_TRUE(s.AddPrimitive("Cone",     {0,0,0}));
  EXPECT_TRUE(s.AddPrimitive("Cube",     {0,0,0}));
  EXPECT_TRUE(s.AddPrimitive("Pyramid",  {0,0,0}));
  EXPECT_EQ(s.GetModelCount(), 5);
}

TEST(Scene, TranslateModel) {
  Scene s;
  std::string path = MakeTempObj();
  s.LoadObjModel(path);
  Vec3 before = s.GetModel(0).data.vertices[0];
  s.TranslateModel(0, 1, 2, 3);
  Vec3 after = s.GetModel(0).data.vertices[0];
  EXPECT_NEAR(after.x - before.x, 1.0, 1e-9);
  EXPECT_NEAR(after.y - before.y, 2.0, 1e-9);
  EXPECT_NEAR(after.z - before.z, 3.0, 1e-9);
}

TEST(Scene, ScaleModel) {
  Scene s;
  std::string path = MakeTempObj();
  s.LoadObjModel(path);
  // vertex[1] = (1,0,0)
  s.ScaleModel(0, 3, 3, 3);
  Vec3 v = s.GetModel(0).data.vertices[1];
  EXPECT_NEAR(v.x, 3.0, 1e-9);
}

TEST(LightManager, AddRemovePointLight) {
  LightManager lm;
  PointLight pt;
  for (int i = 0; i < 5; ++i) EXPECT_TRUE(lm.AddPointLight(pt));
  EXPECT_FALSE(lm.AddPointLight(pt));  // 6th should fail
  EXPECT_TRUE(lm.RemovePointLight(0));
  EXPECT_EQ(lm.GetPointLights().size(), 4u);
}

TEST(GeometricObjects, SphereIntersect) {
  AnalyticSphere sphere({0,0,0}, 1.0);
  Ray ray{{0,0,-5},{0,0,1}};
  auto hit = sphere.Intersect(ray, 0.001, 1e9);
  ASSERT_TRUE(hit.has_value());
  EXPECT_NEAR(hit->t, 4.0, 1e-6);
}

TEST(GeometricObjects, SphereMiss) {
  AnalyticSphere sphere({0,0,0}, 1.0);
  Ray ray{{5,0,0},{0,0,1}};
  auto hit = sphere.Intersect(ray, 0.001, 1e9);
  EXPECT_FALSE(hit.has_value());
}

TEST(GeometricObjects, CubeIntersect) {
  AnalyticCube cube({-1,-1,-1},{1,1,1});
  Ray ray{{0,0,-5},{0,0,1}};
  auto hit = cube.Intersect(ray, 0.001, 1e9);
  ASSERT_TRUE(hit.has_value());
  EXPECT_NEAR(hit->t, 4.0, 1e-6);
}

TEST(KDTree, BuildAndIntersect) {
  TrianglePrimitive tri;
  tri.v0 = {-1,0,0}; tri.v1 = {1,0,0}; tri.v2 = {0,1,0};
  tri.n0 = tri.n1 = tri.n2 = {0,0,1};
  KDTree tree;
  tree.Build({tri});
  Ray ray{{0,0.5,-5},{0,0,1}};
  auto hit = tree.Intersect(ray, 0.001, 1e9);
  ASSERT_TRUE(hit.has_value());
}

}  // namespace s21
