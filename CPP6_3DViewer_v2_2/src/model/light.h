#pragma once
#include "model_data.h"
#include <vector>

namespace s21 {

struct DirectionalLight {
  Vec3 position{0.0, 10.0, 10.0};
  Color color{1.0f, 1.0f, 1.0f, 1.0f};
  float intensity = 1.0f;
};

struct PointLight {
  Vec3 position{0.0, 5.0, 0.0};
  Color color{1.0f, 1.0f, 1.0f, 1.0f};
  float intensity = 1.0f;
};

struct AmbientLight {
  Color color{0.2f, 0.2f, 0.2f, 1.0f};
  float intensity = 0.2f;
};

class LightManager {
 public:
  static constexpr int kMaxPointLights = 5;

  void SetDirectional(const DirectionalLight& light) { directional_ = light; }
  void SetAmbient(const AmbientLight& ambient) { ambient_ = ambient; }
  bool AddPointLight(const PointLight& light);
  bool RemovePointLight(int index);
  void UpdatePointLight(int index, const PointLight& light);

  const DirectionalLight& GetDirectional() const { return directional_; }
  const AmbientLight& GetAmbient() const { return ambient_; }
  const std::vector<PointLight>& GetPointLights() const { return point_lights_; }

 private:
  DirectionalLight directional_;
  AmbientLight ambient_;
  std::vector<PointLight> point_lights_;
};

}  // namespace s21
