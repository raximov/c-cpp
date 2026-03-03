#include "math_private.h"

/**
 * @brief вычисляет квадратный корень
 * @details на каждой итерации сужаем диапазон поиска квадратного корня до тех
 * пор пока разница между текущим приближением и результатом не станет
 * достаточно мала
 * @author qothojol
 * @param x
 * @return long double
 */

long double s21_sqrt(double x) {
  double res = 1.0;

  if (x < 0.0) {
    res = -S21_NAN;
  } else if (s21_isinf(x) || s21_isnan(x) || x == -0.0) {
    res = x;
  } else {
    double begin = 0.0;
    while ((begin - res) >= S21_EPSILON || (res - begin) >= S21_EPSILON) {
      begin = res;
      res = ((x / res) + res) / 2;
    }
  }
  return res;
}