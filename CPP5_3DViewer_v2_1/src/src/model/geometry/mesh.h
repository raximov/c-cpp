#pragma once
#include <vector>
#include <array>
#include <string>

namespace s21 {

struct Vertex {
  float x, y, z;
};

struct Normal {
  float nx, ny, nz;
};

struct TexCoord {
  float u, v;
};

struct Face {
  std::vector<int> vertex_indices;
  std::vector<int> normal_indices;
  std::vector<int> texcoord_indices;
};

// Strategy pattern: rendering mode
enum class RenderMode {
  kWireframe,
  kFlatShading,
  kGouraudShading,
  kPhongShading
};

class Mesh {
 public:
  Mesh() = default;
  ~Mesh() = default;
  Mesh(const Mesh&) = default;
  Mesh(Mesh&&) = default;
  Mesh& operator=(const Mesh&) = default;
  Mesh& operator=(Mesh&&) = default;

  void Clear();
  void ComputeVertexNormals();
  void Normalize();  // centers and scales to unit box

  // Accessors
  const std::vector<Vertex>& GetVertices() const { return vertices_; }
  const std::vector<Normal>& GetNormals() const { return normals_; }
  const std::vector<TexCoord>& GetTexCoords() const { return tex_coords_; }
  const std::vector<Face>& GetFaces() const { return faces_; }
  std::vector<Vertex>& GetVertices() { return vertices_; }
  std::vector<Normal>& GetNormals() { return normals_; }
  std::vector<TexCoord>& GetTexCoords() { return tex_coords_; }
  std::vector<Face>& GetFaces() { return faces_; }

  size_t GetVertexCount() const { return vertices_.size(); }
  size_t GetEdgeCount() const;
  const std::string& GetFilename() const { return filename_; }
  void SetFilename(const std::string& name) { filename_ = name; }

  // Build GPU-ready flat arrays (interleaved: pos, normal, uv)
  std::vector<float> BuildVertexBuffer() const;
  std::vector<unsigned int> BuildIndexBuffer() const;
  std::vector<unsigned int> BuildWireframeIndexBuffer() const;

 private:
  std::vector<Vertex> vertices_;
  std::vector<Normal> normals_;
  std::vector<TexCoord> tex_coords_;
  std::vector<Face> faces_;
  std::string filename_;

  // computed per-vertex normals for Gouraud/Phong
  std::vector<Normal> computed_normals_;
};

}  // namespace s21
