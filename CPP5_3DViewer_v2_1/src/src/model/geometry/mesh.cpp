#include "mesh.h"
#include <algorithm>
#include <cmath>
#include <unordered_set>

namespace s21 {

void Mesh::Clear() {
  vertices_.clear();
  normals_.clear();
  tex_coords_.clear();
  faces_.clear();
  computed_normals_.clear();
  filename_.clear();
}

void Mesh::ComputeVertexNormals() {
  computed_normals_.assign(vertices_.size(), {0.f, 0.f, 0.f});

  for (const auto& face : faces_) {
    if (face.vertex_indices.size() < 3) continue;
    // Compute face normal from first triangle
    int i0 = face.vertex_indices[0];
    int i1 = face.vertex_indices[1];
    int i2 = face.vertex_indices[2];
    const auto& v0 = vertices_[i0];
    const auto& v1 = vertices_[i1];
    const auto& v2 = vertices_[i2];

    float ax = v1.x - v0.x, ay = v1.y - v0.y, az = v1.z - v0.z;
    float bx = v2.x - v0.x, by = v2.y - v0.y, bz = v2.z - v0.z;
    float nx = ay * bz - az * by;
    float ny = az * bx - ax * bz;
    float nz = ax * by - ay * bx;

    for (int idx : face.vertex_indices) {
      computed_normals_[idx].nx += nx;
      computed_normals_[idx].ny += ny;
      computed_normals_[idx].nz += nz;
    }
  }

  for (auto& n : computed_normals_) {
    float len = std::sqrt(n.nx*n.nx + n.ny*n.ny + n.nz*n.nz);
    if (len > 1e-8f) { n.nx /= len; n.ny /= len; n.nz /= len; }
  }
}

void Mesh::Normalize() {
  if (vertices_.empty()) return;
  float min_x = vertices_[0].x, max_x = min_x;
  float min_y = vertices_[0].y, max_y = min_y;
  float min_z = vertices_[0].z, max_z = min_z;

  for (const auto& v : vertices_) {
    min_x = std::min(min_x, v.x); max_x = std::max(max_x, v.x);
    min_y = std::min(min_y, v.y); max_y = std::max(max_y, v.y);
    min_z = std::min(min_z, v.z); max_z = std::max(max_z, v.z);
  }

  float cx = (min_x + max_x) / 2, cy = (min_y + max_y) / 2, cz = (min_z + max_z) / 2;
  float scale = std::max({max_x - min_x, max_y - min_y, max_z - min_z});
  if (scale < 1e-8f) scale = 1.f;

  for (auto& v : vertices_) {
    v.x = (v.x - cx) / scale * 2.f;
    v.y = (v.y - cy) / scale * 2.f;
    v.z = (v.z - cz) / scale * 2.f;
  }
}

size_t Mesh::GetEdgeCount() const {
  // Count unique edges
  struct EdgeHash {
    size_t operator()(const std::pair<int,int>& e) const {
      return std::hash<long long>()((long long)e.first << 32 | e.second);
    }
  };
  std::unordered_set<std::pair<int,int>, EdgeHash> edges;
  for (const auto& face : faces_) {
    size_t n = face.vertex_indices.size();
    for (size_t i = 0; i < n; ++i) {
      int a = face.vertex_indices[i];
      int b = face.vertex_indices[(i + 1) % n];
      if (a > b) std::swap(a, b);
      edges.insert({a, b});
    }
  }
  return edges.size();
}

std::vector<float> Mesh::BuildVertexBuffer() const {
  // Flat: for each face triangle, emit vertices with pos(3) + normal(3) + uv(2)
  std::vector<float> buf;
  const bool has_normals = !normals_.empty();
  const bool has_cn = !computed_normals_.empty();
  const bool has_uv = !tex_coords_.empty();

  for (const auto& face : faces_) {
    size_t n = face.vertex_indices.size();
    // Fan triangulate
    for (size_t i = 1; i + 1 < n; ++i) {
      for (size_t k : {(size_t)0, i, i + 1}) {
        int vi = face.vertex_indices[k];
        const auto& v = vertices_[vi];
        buf.push_back(v.x); buf.push_back(v.y); buf.push_back(v.z);

        // normal
        if (has_normals && k < face.normal_indices.size()) {
          int ni = face.normal_indices[k];
          buf.push_back(normals_[ni].nx);
          buf.push_back(normals_[ni].ny);
          buf.push_back(normals_[ni].nz);
        } else if (has_cn) {
          buf.push_back(computed_normals_[vi].nx);
          buf.push_back(computed_normals_[vi].ny);
          buf.push_back(computed_normals_[vi].nz);
        } else {
          buf.push_back(0); buf.push_back(0); buf.push_back(1);
        }

        // uv
        if (has_uv && k < face.texcoord_indices.size()) {
          int ti = face.texcoord_indices[k];
          buf.push_back(tex_coords_[ti].u);
          buf.push_back(tex_coords_[ti].v);
        } else {
          buf.push_back(0); buf.push_back(0);
        }
      }
    }
  }
  return buf;
}

std::vector<unsigned int> Mesh::BuildWireframeIndexBuffer() const {
  std::vector<unsigned int> indices;
  unsigned int base = 0;
  for (const auto& face : faces_) {
    size_t n = face.vertex_indices.size();
    // line loop per face vertex
    for (size_t i = 0; i < n; ++i) {
      indices.push_back(face.vertex_indices[i]);
      indices.push_back(face.vertex_indices[(i + 1) % n]);
    }
    base += n;
  }
  return indices;
}

}  // namespace s21
