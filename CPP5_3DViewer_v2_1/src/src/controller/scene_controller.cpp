#include "scene_controller.h"
#include <QStandardPaths>

namespace s21 {

SceneController::SceneController(Scene& scene) : scene_(scene) {
  settings_path_ = QStandardPaths::writableLocation(
    QStandardPaths::AppDataLocation).toStdString() + "/settings.cfg";
}

bool SceneController::LoadModel(const std::string& filepath) {
  return scene_.LoadModel(filepath);
}

void SceneController::Translate(float x, float y, float z) {
  scene_.GetTransform().SetTranslation(x, y, z);
}

void SceneController::Rotate(float rx, float ry, float rz) {
  scene_.GetTransform().SetRotation(rx, ry, rz);
}

void SceneController::Scale(float s) {
  scene_.GetTransform().SetScale(s);
}

void SceneController::ResetTransform() {
  scene_.GetTransform().Reset();
}

void SceneController::SetRenderMode(RenderMode mode) {
  scene_.SetRenderMode(mode);
}

void SceneController::SetProjection(ProjectionType proj) {
  scene_.GetSettings().projection = proj;
}

void SceneController::SetLightPosition(float x, float y, float z) {
  scene_.GetLight().position = {x, y, z};
}

void SceneController::SetLightColor(float r, float g, float b) {
  scene_.GetLight().r = r;
  scene_.GetLight().g = g;
  scene_.GetLight().b = b;
}

void SceneController::SetAmbientStrength(float a) {
  scene_.GetLight().ambient_strength = a;
}

void SceneController::SetSpecularStrength(float s) {
  scene_.GetLight().specular_strength = s;
}

void SceneController::SetShininess(int shine) {
  scene_.GetLight().shininess = shine;
}

void SceneController::SetEdgeSettings(bool dashed, float r, float g, float b, float width) {
  auto& s = scene_.GetSettings();
  s.dashed_edges = dashed;
  s.edge_r = r; s.edge_g = g; s.edge_b = b;
  s.edge_width = width;
}

void SceneController::SetVertexSettings(int display, float r, float g, float b, float size) {
  auto& s = scene_.GetSettings();
  s.vertex_display = display;
  s.vertex_r = r; s.vertex_g = g; s.vertex_b = b;
  s.vertex_size = size;
}

void SceneController::SetObjectColor(float r, float g, float b) {
  auto& s = scene_.GetSettings();
  s.obj_r = r; s.obj_g = g; s.obj_b = b;
}

void SceneController::SetBackgroundColor(float r, float g, float b) {
  auto& s = scene_.GetSettings();
  s.bg_r = r; s.bg_g = g; s.bg_b = b;
}

void SceneController::SaveSettings() {
  scene_.SaveSettings(settings_path_);
}

void SceneController::LoadSettings() {
  scene_.LoadSettings(settings_path_);
}

}  // namespace s21
