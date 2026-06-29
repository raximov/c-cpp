#include "model_data.h"
#include <cmath>

namespace s21 {

double Vec3::length() const {
  return std::sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::normalized() const {
  double len = length();
  if (len < 1e-12) return {0, 0, 0};
  return {x / len, y / len, z / len};
}

}  // namespace s21
