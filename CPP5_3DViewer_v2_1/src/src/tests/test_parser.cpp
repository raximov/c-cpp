#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include "../model/parser/obj_parser.h"
#include "../model/geometry/mesh.h"

namespace s21 {

// Helper: write a temp OBJ file and return its path
static std::string WriteTempObj(const char* content) {
  std::string path = "/tmp/test_model.obj";
  std::ofstream f(path);
  f << content;
  return path;
}

TEST(ObjParserTest, ParsesSimpleTriangle) {
  auto path = WriteTempObj(
    "v 0.0 0.0 0.0\n"
    "v 1.0 0.0 0.0\n"
    "v 0.0 1.0 0.0\n"
    "f 1 2 3\n");
  Mesh mesh;
  ObjParser parser;
  ASSERT_TRUE(parser.Parse(path, mesh));
  EXPECT_EQ(mesh.GetVertexCount(), 3u);
  EXPECT_EQ(mesh.GetFaces().size(), 1u);
  EXPECT_EQ(mesh.GetFaces()[0].vertex_indices.size(), 3u);
}

TEST(ObjParserTest, ParsesQuad) {
  auto path = WriteTempObj(
    "v 0 0 0\nv 1 0 0\nv 1 1 0\nv 0 1 0\n"
    "f 1 2 3 4\n");
  Mesh mesh;
  ObjParser parser;
  ASSERT_TRUE(parser.Parse(path, mesh));
  EXPECT_EQ(mesh.GetFaces()[0].vertex_indices.size(), 4u);
}

TEST(ObjParserTest, ParsesNormals) {
  auto path = WriteTempObj(
    "v 0 0 0\nv 1 0 0\nv 0 1 0\n"
    "vn 0 0 1\n"
    "f 1//1 2//1 3//1\n");
  Mesh mesh;
  ObjParser parser;
  ASSERT_TRUE(parser.Parse(path, mesh));
  EXPECT_GE(mesh.GetNormals().size(), 1u);
}

TEST(ObjParserTest, ParsesTexCoords) {
  auto path = WriteTempObj(
    "v 0 0 0\nv 1 0 0\nv 0 1 0\n"
    "vt 0.0 0.0\nvt 1.0 0.0\nvt 0.0 1.0\n"
    "f 1/1 2/2 3/3\n");
  Mesh mesh;
  ObjParser parser;
  ASSERT_TRUE(parser.Parse(path, mesh));
  EXPECT_EQ(mesh.GetTexCoords().size(), 3u);
}

TEST(ObjParserTest, FailsOnMissingFile) {
  Mesh mesh;
  ObjParser parser;
  EXPECT_FALSE(parser.Parse("/nonexistent/path.obj", mesh));
  EXPECT_FALSE(parser.GetLastError().empty());
}

TEST(ObjParserTest, IgnoresComments) {
  auto path = WriteTempObj(
    "# This is a comment\n"
    "v 0 0 0\nv 1 0 0\nv 0 1 0\n"
    "# another comment\n"
    "f 1 2 3\n");
  Mesh mesh;
  ObjParser parser;
  EXPECT_TRUE(parser.Parse(path, mesh));
  EXPECT_EQ(mesh.GetVertexCount(), 3u);
}

TEST(ObjParserTest, HandlesNegativeIndices) {
  auto path = WriteTempObj(
    "v 0 0 0\nv 1 0 0\nv 0 1 0\n"
    "f -3 -2 -1\n");
  Mesh mesh;
  ObjParser parser;
  EXPECT_TRUE(parser.Parse(path, mesh));
  EXPECT_EQ(mesh.GetFaces().size(), 1u);
}

TEST(ObjParserTest, NormalizesModel) {
  // After normalize, all coords should be in [-1, 1]
  auto path = WriteTempObj(
    "v 0 0 0\nv 100 0 0\nv 0 100 0\n"
    "f 1 2 3\n");
  Mesh mesh;
  ObjParser parser;
  ASSERT_TRUE(parser.Parse(path, mesh));
  for (const auto& v : mesh.GetVertices()) {
    EXPECT_LE(std::abs(v.x), 1.01f);
    EXPECT_LE(std::abs(v.y), 1.01f);
  }
}

TEST(ObjParserTest, ComputesVertexNormals) {
  auto path = WriteTempObj(
    "v 0 0 0\nv 1 0 0\nv 0 1 0\n"
    "f 1 2 3\n");
  Mesh mesh;
  ObjParser parser;
  ASSERT_TRUE(parser.Parse(path, mesh));
  // ComputeVertexNormals is called internally; no crash
  SUCCEED();
}

}  // namespace s21
