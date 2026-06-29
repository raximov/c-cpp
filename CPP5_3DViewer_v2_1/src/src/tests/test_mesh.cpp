#include <gtest/gtest.h>
#include "../model/geometry/mesh.h"

namespace s21 {

TEST(MeshTest, EmptyMesh) {
  Mesh m;
  EXPECT_EQ(m.GetVertexCount(), 0u);
  EXPECT_EQ(m.GetEdgeCount(), 0u);
  EXPECT_TRUE(m.GetFaces().empty());
}

TEST(MeshTest, EdgeCount) {
  Mesh m;
  m.GetVertices() = {{0,0,0},{1,0,0},{0,1,0},{0,0,1}};
  // Triangle: 3 edges
  Face f;
  f.vertex_indices = {0, 1, 2};
  m.GetFaces().push_back(f);
  EXPECT_EQ(m.GetEdgeCount(), 3u);
}

TEST(MeshTest, SharedEdgeCountedOnce) {
  Mesh m;
  m.GetVertices() = {{0,0,0},{1,0,0},{0,1,0},{-1,0,0}};
  // Two triangles sharing edge 0-2
  Face f1; f1.vertex_indices = {0, 1, 2};
  Face f2; f2.vertex_indices = {0, 2, 3};
  m.GetFaces().push_back(f1);
  m.GetFaces().push_back(f2);
  EXPECT_EQ(m.GetEdgeCount(), 5u);  // 3+3-1 shared
}

TEST(MeshTest, NormalizeCenter) {
  Mesh m;
  m.GetVertices() = {{-10,0,0},{10,0,0},{0,0,0}};
  m.Normalize();
  // After normalize, centroid should be near origin
  float cx = 0;
  for (const auto& v : m.GetVertices()) cx += v.x;
  cx /= 3;
  EXPECT_NEAR(cx, 0.0f, 1e-4f);
}

TEST(MeshTest, ComputeVertexNormals) {
  Mesh m;
  m.GetVertices() = {{0,0,0},{1,0,0},{0,1,0}};
  Face f; f.vertex_indices = {0,1,2};
  m.GetFaces().push_back(f);
  EXPECT_NO_THROW(m.ComputeVertexNormals());
}

TEST(MeshTest, BuildVertexBufferSize) {
  Mesh m;
  m.GetVertices() = {{0,0,0},{1,0,0},{0,1,0}};
  Face f; f.vertex_indices = {0,1,2};
  m.GetFaces().push_back(f);
  m.ComputeVertexNormals();
  auto buf = m.BuildVertexBuffer();
  // 1 triangle, 3 vertices, 8 floats each
  EXPECT_EQ(buf.size(), 3u * 8u);
}

TEST(MeshTest, Clear) {
  Mesh m;
  m.GetVertices() = {{0,0,0},{1,0,0}};
  m.Clear();
  EXPECT_EQ(m.GetVertexCount(), 0u);
  EXPECT_TRUE(m.GetFaces().empty());
}

TEST(MeshTest, WireframeBuffer) {
  Mesh m;
  m.GetVertices() = {{0,0,0},{1,0,0},{0,1,0}};
  Face f; f.vertex_indices = {0,1,2};
  m.GetFaces().push_back(f);
  auto idx = m.BuildWireframeIndexBuffer();
  // 3 edges × 2 endpoints
  EXPECT_EQ(idx.size(), 6u);
}

}  // namespace s21

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
