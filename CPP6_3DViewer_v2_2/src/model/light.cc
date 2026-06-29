#include "light.h"

namespace s21 {

bool LightManager::AddPointLight(const PointLight& light) {
  if (static_cast<int>(point_lights_.size()) >= kMaxPointLights) return false;
  point_lights_.push_back(light);
  return true;
}

bool LightManager::RemovePointLight(int index) {
  if (index < 0 || index >= static_cast<int>(point_lights_.size())) return false;
  point_lights_.erase(point_lights_.begin() + index);
  return true;
}

void LightManager::UpdatePointLight(int index, const PointLight& light) {
  if (index >= 0 && index < static_cast<int>(point_lights_.size())) {
    point_lights_[index] = light;
  }
}

}  // namespace s21
