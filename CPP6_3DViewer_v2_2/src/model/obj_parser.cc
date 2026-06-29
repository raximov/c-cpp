#include "obj_parser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_set>
#include <filesystem>

namespace s21 {

ModelData ObjParser::Parse(const std::string& file_path) {
  std::ifstream file(file_path);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file: " + file_path);
  }

  ModelData data;
  data.file_name = std::filesystem::path(file_path).filename().string();

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty() || line[0] == '#') continue;
    std::string prefix = line.substr(0, line.find(' '));
    if (prefix == "v") {
      ParseVertex(line, data);
    } else if (prefix == "vn") {
      ParseNormal(line, data);
    } else if (prefix == "vt") {
      ParseUV(line, data);
    } else if (prefix == "f") {
      ParseFace(line, data);
    }
  }

  data.vertex_count = static_cast<int>(data.vertices.size());
  ComputeEdgeCount(data);
  return data;
}

void ObjParser::ParseVertex(const std::string& line, ModelData& data) {
  std::istringstream ss(line.substr(2));
  Vec3 v;
  ss >> v.x >> v.y >> v.z;
  data.vertices.push_back(v);
}

void ObjParser::ParseNormal(const std::string& line, ModelData& data) {
  std::istringstream ss(line.substr(3));
  Vec3 n;
  ss >> n.x >> n.y >> n.z;
  data.normals.push_back(n);
}

void ObjParser::ParseUV(const std::string& line, ModelData& data) {
  std::istringstream ss(line.substr(3));
  Vec2 uv;
  ss >> uv.u >> uv.v;
  data.uv_coords.push_back(uv);
}

void ObjParser::ParseFace(const std::string& line, ModelData& data) {
  std::istringstream ss(line.substr(2));
  Face face;
  std::string token;

  while (ss >> token) {
    std::istringstream ts(token);
    std::string vi, ti, ni;
    std::getline(ts, vi, '/');
    std::getline(ts, ti, '/');
    std::getline(ts, ni, '/');

    if (!vi.empty()) face.vertex_indices.push_back(std::stoi(vi) - 1);
    if (!ti.empty()) face.uv_indices.push_back(std::stoi(ti) - 1);
    if (!ni.empty()) face.normal_indices.push_back(std::stoi(ni) - 1);
  }

  if (!face.vertex_indices.empty()) {
    data.faces.push_back(std::move(face));
  }
}

void ObjParser::ComputeEdgeCount(ModelData& data) {
  // Use set of ordered pairs to count unique edges
  struct PairHash {
    size_t operator()(const std::pair<int,int>& p) const {
      return std::hash<long long>()(((long long)p.first << 32) | (unsigned)p.second);
    }
  };
  std::unordered_set<std::pair<int,int>, PairHash> edges;
  for (const auto& face : data.faces) {
    int n = static_cast<int>(face.vertex_indices.size());
    for (int i = 0; i < n; ++i) {
      int a = face.vertex_indices[i];
      int b = face.vertex_indices[(i + 1) % n];
      if (a > b) std::swap(a, b);
      edges.insert({a, b});
    }
  }
  data.edge_count = static_cast<int>(edges.size());
}

}  // namespace s21
