#include "scene.h"
#include <fstream>
#include <sstream>

namespace s21 {

Scene::Scene() = default;

bool Scene::LoadModel(const std::string& filepath) {
  transform_.Reset();
  if (!parser_.Parse(filepath, mesh_)) {
    last_error_ = parser_.GetLastError();
    return false;
  }
  last_error_.clear();
  return true;
}

void Scene::SetRenderMode(RenderMode mode) {
  settings_.render_mode = mode;
  shading_model_.SetStrategy(mode);
}

void Scene::SaveSettings(const std::string& path) const {
  std::ofstream f(path);
  if (!f.is_open()) return;
  const auto& s = settings_;
  f << static_cast<int>(s.render_mode) << "\n"
    << static_cast<int>(s.projection) << "\n"
    << s.dashed_edges << "\n"
    << s.edge_r << " " << s.edge_g << " " << s.edge_b << "\n"
    << s.edge_width << "\n"
    << s.vertex_display << "\n"
    << s.vertex_r << " " << s.vertex_g << " " << s.vertex_b << "\n"
    << s.vertex_size << "\n"
    << s.obj_r << " " << s.obj_g << " " << s.obj_b << "\n"
    << s.bg_r << " " << s.bg_g << " " << s.bg_b << "\n";
}

bool Scene::LoadSettings(const std::string& path) {
  std::ifstream f(path);
  if (!f.is_open()) return false;
  auto& s = settings_;
  int rm, proj;
  f >> rm >> proj;
  s.render_mode = static_cast<RenderMode>(rm);
  s.projection = static_cast<ProjectionType>(proj);
  f >> s.dashed_edges
    >> s.edge_r >> s.edge_g >> s.edge_b
    >> s.edge_width
    >> s.vertex_display
    >> s.vertex_r >> s.vertex_g >> s.vertex_b
    >> s.vertex_size
    >> s.obj_r >> s.obj_g >> s.obj_b
    >> s.bg_r >> s.bg_g >> s.bg_b;
  shading_model_.SetStrategy(s.render_mode);
  return true;
}

}  // namespace s21
