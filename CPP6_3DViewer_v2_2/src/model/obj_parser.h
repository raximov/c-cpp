#pragma once
#include "model_data.h"
#include <string>

namespace s21 {

class ObjParser {
 public:
  // Returns parsed ModelData; throws std::runtime_error on failure.
  ModelData Parse(const std::string& file_path);

 private:
  void ParseVertex(const std::string& line, ModelData& data);
  void ParseNormal(const std::string& line, ModelData& data);
  void ParseUV(const std::string& line, ModelData& data);
  void ParseFace(const std::string& line, ModelData& data);
  void ComputeEdgeCount(ModelData& data);
};

}  // namespace s21
