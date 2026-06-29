#pragma once
#include <array>
#include <string>
#include <vector>

namespace s21 {

struct Vec3 {
  double x = 0.0, y = 0.0, z = 0.0;
  Vec3() = default;
  Vec3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
  Vec3 operator+(const Vec3& o) const { return {x + o.x, y + o.y, z + o.z}; }
  Vec3 operator-(const Vec3& o) const { return {x - o.x, y - o.y, z - o.z}; }
  Vec3 operator*(double t) const { return {x * t, y * t, z * t}; }
  Vec3 operator/(double t) const { return {x / t, y / t, z / t}; }
  Vec3& operator+=(const Vec3& o) { x+=o.x; y+=o.y; z+=o.z; return *this; }
  double dot(const Vec3& o) const { return x*o.x + y*o.y + z*o.z; }
  Vec3 cross(const Vec3& o) const {
    return {y*o.z - z*o.y, z*o.x - x*o.z, x*o.y - y*o.x};
  }
  double length() const;
  Vec3 normalized() const;
  bool operator==(const Vec3& o) const {
    return x == o.x && y == o.y && z == o.z;
  }
};

struct Vec2 {
  double u = 0.0, v = 0.0;
};

struct Color {
  float r = 1.0f, g = 1.0f, b = 1.0f, a = 1.0f;
};

struct Vertex {
  Vec3 position;
  Vec3 normal;
  Vec2 uv;
};

struct Face {
  std::vector<int> vertex_indices;
  std::vector<int> normal_indices;
  std::vector<int> uv_indices;
};

struct MaterialProperties {
  Color base_color{1.0f, 1.0f, 1.0f, 1.0f};
  float transparency = 0.0f;
  float refraction_index = 1.0f;
  float reflectivity = 0.0f;
  float roughness = 0.5f;
};

enum class DisplayMode {
  kWireframe,
  kFlatShading,
  kGouraudShading,
  kPhongShading
};

enum class ProjectionType {
  kParallel,
  kCentral
};

struct ModelData {
  std::vector<Vec3> vertices;
  std::vector<Vec3> normals;
  std::vector<Vec2> uv_coords;
  std::vector<Face> faces;
  std::string file_name;
  int vertex_count = 0;
  int edge_count = 0;
};

struct EdgeStyle {
  Color color{0.8f, 0.8f, 0.8f, 1.0f};
  float thickness = 1.0f;
  bool dashed = false;
};

struct VertexStyle {
  enum class Shape { kNone, kCircle, kSquare };
  Shape shape = Shape::kNone;
  Color color{1.0f, 1.0f, 1.0f, 1.0f};
  float size = 3.0f;
};

struct SceneSettings {
  Color background_color{0.1f, 0.1f, 0.1f, 1.0f};
  EdgeStyle edge_style;
  VertexStyle vertex_style;
  ProjectionType projection = ProjectionType::kCentral;
  bool show_floor = true;
};

}  // namespace s21
