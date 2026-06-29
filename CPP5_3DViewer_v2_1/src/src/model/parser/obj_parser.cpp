#include "obj_parser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace s21 {

bool ObjParser::Parse(const std::string& filepath, Mesh& mesh) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    last_error_ = "Cannot open file: " + filepath;
    return false;
  }

  mesh.Clear();
  mesh.SetFilename(filepath);

  std::string line;
  int line_num = 0;
  while (std::getline(file, line)) {
    ++line_num;
    if (line.empty() || line[0] == '#') continue;

    // Strip trailing CR for Windows files
    if (!line.empty() && line.back() == '\r') line.pop_back();

    if (line.size() >= 2 && line[0] == 'v' && line[1] == 'n') {
      ParseNormal(line.substr(3), mesh);
    } else if (line.size() >= 2 && line[0] == 'v' && line[1] == 't') {
      ParseTexCoord(line.substr(3), mesh);
    } else if (line[0] == 'v' && (line.size() == 1 || line[1] == ' ')) {
      ParseVertex(line.substr(2), mesh);
    } else if (line[0] == 'f' && (line.size() == 1 || line[1] == ' ')) {
      ParseFace(line.substr(2), mesh);
    }
    // 'o', 'g', 's', 'usemtl', 'mtllib' — ignored for now
  }

  if (mesh.GetVertexCount() == 0) {
    last_error_ = "No vertices found in file";
    return false;
  }

  mesh.Normalize();
  mesh.ComputeVertexNormals();

  last_error_.clear();
  return true;
}

void ObjParser::ParseVertex(const std::string& line, Mesh& mesh) {
  std::istringstream ss(line);
  Vertex v{};
  ss >> v.x >> v.y >> v.z;
  mesh.GetVertices().push_back(v);
}

void ObjParser::ParseNormal(const std::string& line, Mesh& mesh) {
  std::istringstream ss(line);
  Normal n{};
  ss >> n.nx >> n.ny >> n.nz;
  mesh.GetNormals().push_back(n);
}

void ObjParser::ParseTexCoord(const std::string& line, Mesh& mesh) {
  std::istringstream ss(line);
  TexCoord tc{};
  ss >> tc.u >> tc.v;
  mesh.GetTexCoords().push_back(tc);
}

void ObjParser::ParseFace(const std::string& line, Mesh& mesh) {
  std::istringstream ss(line);
  Face face;
  std::string token;

  while (ss >> token) {
    // Format: v, v/vt, v//vn, v/vt/vn (1-based indices)
    int vi = 0, ti = 0, ni = 0;
    char c1, c2;
    std::istringstream ts(token);

    ts >> vi;
    if (ts.peek() == '/') {
      ts >> c1;
      if (ts.peek() != '/') ts >> ti;
      if (ts.peek() == '/') {
        ts >> c2;
        ts >> ni;
      }
    }

    // Convert to 0-based; handle negative (relative) indices
    int vc = static_cast<int>(mesh.GetVertices().size());
    if (vi < 0) vi += vc + 1;
    if (vi < 1 || vi > vc) continue;

    face.vertex_indices.push_back(vi - 1);

    if (ti != 0) {
      int tc = static_cast<int>(mesh.GetTexCoords().size());
      if (ti < 0) ti += tc + 1;
      if (ti >= 1 && ti <= tc) face.texcoord_indices.push_back(ti - 1);
    }

    if (ni != 0) {
      int nc = static_cast<int>(mesh.GetNormals().size());
      if (ni < 0) ni += nc + 1;
      if (ni >= 1 && ni <= nc) face.normal_indices.push_back(ni - 1);
    }
  }

  if (face.vertex_indices.size() >= 3)
    mesh.GetFaces().push_back(std::move(face));
}

}  // namespace s21
