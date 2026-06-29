#pragma once
#include "../../utils/math_utils.h"

namespace s21 {

struct LightSource {
  Vec3 position{0.0f, 5.0f, 5.0f};
  float r{1.0f}, g{1.0f}, b{1.0f};  // base intensity color
  float ambient_strength{0.2f};
  float specular_strength{0.5f};
  int shininess{32};
};

}  // namespace s21
