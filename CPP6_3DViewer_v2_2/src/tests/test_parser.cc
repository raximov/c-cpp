#include <gtest/gtest.h>
#include "../model/obj_parser.h"
#include <fstream>
#include <cstdio>

namespace s21 {

static std::string WriteTempObj(const std::string& content) {
  std::string path = "/tmp/test_model.obj";
  std::ofstream f(path);
  f << content;
  return path;
}

TEST(ObjParser, ParseVertices) {
  auto path = WriteTempObj("v 1.0 2.0 3.0\nv -1.0 0.5 -0.5\n");
  ObjParser p;
  auto data = p.Parse(path);
  ASSERT_EQ(data.vertices.size(), 2u);
  EXPECT_DOUBLE_EQ(data.vertices[0].x, 1.0);
  EXPECT_DOUBLE_EQ(data.vertices[0].y, 2.0);
  EXPECT_DOUBLE_EQ(data.vertices[0].z, 3.0);
  EXPECT_DOUBLE_EQ(data.vertices[1].x, -1.0);
}

TEST(ObjParser, ParseNormals) {
  auto path = WriteTempObj("vn 0 1 0\nvn 0 0 1\n");
  ObjParser p;
  auto data = p.Parse(path);
  ASSERT_EQ(data.normals.size(), 2u);
  EXPECT_DOUBLE_EQ(data.normals[0].y, 1.0);
}

TEST(ObjParser, ParseFaceTriangle) {
  auto path = WriteTempObj(
      "v 0 0 0\nv 1 0 0\nv 0 1 0\n"
      "f 1 2 3\n");
  ObjParser p;
  auto data = p.Parse(path);
  ASSERT_EQ(data.faces.size(), 1u);
  ASSERT_EQ(data.faces[0].vertex_indices.size(), 3u);
  EXPECT_EQ(data.faces[0].vertex_indices[0], 0);
  EXPECT_EQ(data.faces[0].vertex_indices[1], 1);
  EXPECT_EQ(data.faces[0].vertex_indices[2], 2);
}

TEST(ObjParser, ParseFaceWithNormalsUV) {
  auto path = WriteTempObj(
      "v 0 0 0\nv 1 0 0\nv 0 1 0\n"
      "vn 0 0 1\nvt 0 0\n"
      "f 1/1/1 2/1/1 3/1/1\n");
  ObjParser p;
  auto data = p.Parse(path);
  ASSERT_EQ(data.faces.size(), 1u);
  EXPECT_EQ(data.faces[0].normal_indices[0], 0);
  EXPECT_EQ(data.faces[0].uv_indices[0], 0);
}

TEST(ObjParser, VertexCount) {
  auto path = WriteTempObj(
      "v 0 0 0\nv 1 0 0\nv 0 1 0\nv 0 0 1\n"
      "f 1 2 3\nf 1 3 4\n");
  ObjParser p;
  auto data = p.Parse(path);
  EXPECT_EQ(data.vertex_count, 4);
}

TEST(ObjParser, InvalidFile) {
  ObjParser p;
  EXPECT_THROW(p.Parse("/nonexistent/path.obj"), std::runtime_error);
}

TEST(ObjParser, EdgeCount) {
  auto path = WriteTempObj(
      "v 0 0 0\nv 1 0 0\nv 0 1 0\n"
      "f 1 2 3\n");
  ObjParser p;
  auto data = p.Parse(path);
  EXPECT_EQ(data.edge_count, 3);
}

TEST(ObjParser, CommentAndBlankLines) {
  auto path = WriteTempObj(
      "# comment\n\nv 1 2 3\n# another\nv 4 5 6\n");
  ObjParser p;
  auto data = p.Parse(path);
  ASSERT_EQ(data.vertices.size(), 2u);
}

}  // namespace s21
