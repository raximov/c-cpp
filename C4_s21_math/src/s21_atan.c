#include "math_private.h"

/**
 * @brief вычисляет арктангенс
 * @details
 * @author qothojol
 *
 * @param x
 * @return long double
 */
long double s21_atan(double x) {
  long double res = 0.0;
  if (x > 0.0 && s21_isinf(x)) {
    res = S21_M_PI_2;
  } else if (x < 0.0 && s21_isinf(x)) {
    res = -S21_M_PI_2;
  } else {
    int reverse = 0.0, sign = 0.0;
    double big_x = x, num;
    if (x < 0.0) {
      sign = 1.0;
      big_x *= -1.0;
    }
    if (big_x > 1.0) {
      big_x = 1.0 / big_x;
      reverse = 1.0;
    }
    num = big_x;
    for (int i = 1.0; i < MAX_ITERATIONS; ++i) {
      res += num;
      num *= -((2.0 * i - 1) * big_x * big_x / (2.0 * (double)i + 1.0));
    }
    if (reverse) {
      res = S21_M_PI_2 - res;
    }
    if (sign) {
      res *= -1;
    }
  }
  return res;
}