#pragma once
#include "../model/scene.h"
#include <string>
#include <functional>

namespace s21 {

// Command pattern: encapsulates user actions
class SceneController {
 public:
  explicit SceneController(Scene& scene);

  // Model loading
  bool LoadModel(const std::string& filepath);

  // Transforms
  void Translate(float x, float y, float z);
  void Rotate(float rx, float ry, float rz);
  void Scale(float s);
  void ResetTransform();

  // Rendering mode
  void SetRenderMode(RenderMode mode);
  void SetProjection(ProjectionType proj);

  // Light
  void SetLightPosition(float x, float y, float z);
  void SetLightColor(float r, float g, float b);
  void SetAmbientStrength(float a);
  void SetSpecularStrength(float s);
  void SetShininess(int shine);

  // Settings
  void SetEdgeSettings(bool dashed, float r, float g, float b, float width);
  void SetVertexSettings(int display, float r, float g, float b, float size);
  void SetObjectColor(float r, float g, float b);
  void SetBackgroundColor(float r, float g, float b);
  void SaveSettings();
  void LoadSettings();

  Scene& GetScene() { return scene_; }
  const Scene& GetScene() const { return scene_; }

 private:
  Scene& scene_;
  std::string settings_path_;
};

}  // namespace s21
