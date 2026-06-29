#pragma once
#include <string>
#include "../geometry/mesh.h"

namespace s21 {

// Facade pattern: hides parsing complexity
class ObjParser {
 public:
  ObjParser() = default;

  // Returns true on success; populates mesh
  bool Parse(const std::string& filepath, Mesh& mesh);

  const std::string& GetLastError() const { return last_error_; }

 private:
  std::string last_error_;

  void ParseVertex(const std::string& line, Mesh& mesh);
  void ParseNormal(const std::string& line, Mesh& mesh);
  void ParseTexCoord(const std::string& line, Mesh& mesh);
  void ParseFace(const std::string& line, Mesh& mesh);
};

}  // namespace s21
