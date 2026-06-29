#pragma once
#include "geometry/mesh.h"
#include "geometry/transform.h"
#include "lighting/light_source.h"
#include "shading/shading_model.h"
#include "parser/obj_parser.h"
#include <array>
#include <string>

namespace s21 {

// Settings that persist between restarts
struct AppSettings {
  RenderMode render_mode{RenderMode::kWireframe};
  ProjectionType projection{ProjectionType::kPerspective};
  // Edge settings
  bool dashed_edges{false};
  float edge_r{1}, edge_g{1}, edge_b{1};
  float edge_width{1.0f};
  // Vertex settings
  int vertex_display{0};  // 0=none, 1=circle, 2=square
  float vertex_r{1}, vertex_g{0}, vertex_b{0};
  float vertex_size{5.0f};
  // Object color
  float obj_r{0.6f}, obj_g{0.6f}, obj_b{0.9f};
  // Background color
  float bg_r{0.1f}, bg_g{0.1f}, bg_b{0.15f};
};

// Facade pattern: Scene is the main entry point for the model layer
class Scene {
 public:
  Scene();

  bool LoadModel(const std::string& filepath);
  bool HasModel() const { return !mesh_.GetVertices().empty(); }

  Mesh& GetMesh() { return mesh_; }
  const Mesh& GetMesh() const { return mesh_; }
  Transform& GetTransform() { return transform_; }
  const Transform& GetTransform() const { return transform_; }
  LightSource& GetLight() { return light_; }
  const LightSource& GetLight() const { return light_; }
  ShadingModel& GetShadingModel() { return shading_model_; }
  const ShadingModel& GetShadingModel() const { return shading_model_; }
  AppSettings& GetSettings() { return settings_; }
  const AppSettings& GetSettings() const { return settings_; }

  void SetRenderMode(RenderMode mode);
  const std::string& GetLastError() const { return last_error_; }

  // Settings persistence
  void SaveSettings(const std::string& path) const;
  bool LoadSettings(const std::string& path);

 private:
  Mesh mesh_;
  Transform transform_;
  LightSource light_;
  ShadingModel shading_model_;
  AppSettings settings_;
  ObjParser parser_;
  std::string last_error_;
};

}  // namespace s21
