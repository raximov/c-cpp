#include <gtest/gtest.h>
#include "../model/geometric_objects.h"
#include "../model/kd_tree.h"
#include "../model/ray_tracer.h"
#include "../model/light.h"
#include "../model/camera.h"

namespace s21 {

// ---- Geometric objects -----------------------------------------------------

TEST(AnalyticSphere, FrontFace) {
  AnalyticSphere s({0,0,0}, 1.0);
  Ray ray{{0,0,-5},{0,0,1}};
  auto hit = s.Intersect(ray, 1e-4, 1e9);
  ASSERT_TRUE(hit.has_value());
  EXPECT_TRUE(hit->front_face);
  EXPECT_NEAR(hit->normal.z, -1.0, 1e-6);
}

TEST(AnalyticSphere, InsideRay) {
  AnalyticSphere s({0,0,0}, 2.0);
  // ray inside sphere
  Ray ray{{0,0,0},{0,0,1}};
  auto hit = s.Intersect(ray, 1e-4, 1e9);
  ASSERT_TRUE(hit.has_value());
  EXPECT_FALSE(hit->front_face);
}

TEST(AnalyticCylinder, BasicHit) {
  AnalyticCylinder c({0,0,0}, 1.0, 3.0);
  Ray ray{{0,1.5,-5},{0,0,1}};
  auto hit = c.Intersect(ray, 1e-4, 1e9);
  ASSERT_TRUE(hit.has_value());
  EXPECT_NEAR(hit->t, 4.0, 1e-5);
}

TEST(AnalyticCylinder, MissAbove) {
  AnalyticCylinder c({0,0,0}, 1.0, 1.0);
  Ray ray{{0,5,-5},{0,0,1}};
  auto hit = c.Intersect(ray, 1e-4, 1e9);
  EXPECT_FALSE(hit.has_value());
}

TEST(AnalyticCube, NormalCheck) {
  AnalyticCube cube({-1,-1,-1},{1,1,1});
  Ray ray{{0,0,-5},{0,0,1}};
  auto hit = cube.Intersect(ray, 1e-4, 1e9);
  ASSERT_TRUE(hit.has_value());
  EXPECT_NEAR(hit->normal.z, -1.0, 1e-6);
}

// ---- Polygonal factories ---------------------------------------------------

TEST(MakeSphereModel, VertexCount) {
  auto m = MakeSphereModel(8, 16);
  EXPECT_GT(m.vertices.size(), 0u);
  EXPECT_GT(m.faces.size(), 0u);
}

TEST(MakeCylinderModel, HasFaces) {
  auto m = MakeCylinderModel(16, 1.0, 2.0);
  EXPECT_GT(m.faces.size(), 0u);
}

TEST(MakeConeModel, HasFaces) {
  auto m = MakeConeModel(12, 1.0, 2.0);
  EXPECT_GT(m.faces.size(), 0u);
}

TEST(MakeCubeModel, HasFaces) {
  auto m = MakeCubeModel(1.0);
  EXPECT_GT(m.faces.size(), 0u);
}

TEST(MakePyramidModel, HasFaces) {
  auto m = MakePyramidModel(4, 1.0, 2.0);
  EXPECT_GT(m.faces.size(), 0u);
}

// ---- KD-Tree ---------------------------------------------------------------

TEST(KDTree, EmptyTree) {
  KDTree tree;
  Ray ray{{0,0,-5},{0,0,1}};
  auto hit = tree.Intersect(ray, 1e-4, 1e9);
  EXPECT_FALSE(hit.has_value());
}

TEST(KDTree, MultipleTriangles) {
  std::vector<TrianglePrimitive> prims;
  // Triangle at z=0
  TrianglePrimitive t1;
  t1.v0={-1,0,0}; t1.v1={1,0,0}; t1.v2={0,1,0};
  t1.n0=t1.n1=t1.n2={0,0,-1};
  // Triangle at z=2
  TrianglePrimitive t2;
  t2.v0={-1,0,2}; t2.v1={1,0,2}; t2.v2={0,1,2};
  t2.n0=t2.n1=t2.n2={0,0,-1};
  prims.push_back(t1);
  prims.push_back(t2);
  KDTree tree;
  tree.Build(prims);
  Ray ray{{0,0.3,-5},{0,0,1}};
  auto hit = tree.Intersect(ray, 1e-4, 1e9);
  ASSERT_TRUE(hit.has_value());
  EXPECT_NEAR(hit->point.z, 0.0, 1e-5);  // closer triangle hit first
}

// ---- Camera ----------------------------------------------------------------

TEST(Camera, GenerateRayCenter) {
  Camera cam;
  cam.SetPosition({0,0,5});
  cam.SetTarget({0,0,0});
  // Center ray (u=0.5, v=0.5) should point along -Z
  Ray ray = cam.GenerateRay(0.5, 0.5, 1.0);
  EXPECT_NEAR(ray.direction.x, 0.0, 1e-5);
  EXPECT_NEAR(ray.direction.y, 0.0, 1e-5);
  EXPECT_LT(ray.direction.z, 0.0);  // pointing toward -Z
}

TEST(Camera, GenerateRayParallel) {
  Camera cam;
  cam.SetPosition({0,0,5});
  cam.SetTarget({0,0,0});
  cam.SetProjection(ProjectionType::kParallel);
  Ray ray = cam.GenerateRay(0.5, 0.5, 1.0);
  // direction should be same as forward (-Z)
  EXPECT_LT(ray.direction.z, 0.0);
}

// ---- Light manager ---------------------------------------------------------

TEST(LightManager, DefaultLights) {
  LightManager lm;
  EXPECT_EQ(lm.GetPointLights().size(), 0u);
}

TEST(LightManager, UpdatePointLight) {
  LightManager lm;
  PointLight pt;
  pt.position = {1,2,3};
  lm.AddPointLight(pt);
  PointLight updated;
  updated.position = {4,5,6};
  lm.UpdatePointLight(0, updated);
  EXPECT_NEAR(lm.GetPointLights()[0].position.x, 4.0, 1e-9);
}

TEST(LightManager, RemoveInvalid) {
  LightManager lm;
  EXPECT_FALSE(lm.RemovePointLight(0));
  EXPECT_FALSE(lm.RemovePointLight(-1));
}

// ---- AABB ------------------------------------------------------------------

TEST(AABB, BasicIntersect) {
  AABB box;
  box.Expand({-1,-1,-1});
  box.Expand({ 1, 1, 1});
  Ray ray{{0,0,-5},{0,0,1}};
  EXPECT_TRUE(box.Intersect(ray, 1e-4, 1e9));
}

TEST(AABB, MissIntersect) {
  AABB box;
  box.Expand({-1,-1,-1});
  box.Expand({ 1, 1, 1});
  Ray ray{{5,0,-5},{0,0,1}};
  EXPECT_FALSE(box.Intersect(ray, 1e-4, 1e9));
}

}  // namespace s21
