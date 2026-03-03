#include "math_private.h"

/**
 * @brief вычисляет натуральный логарифм
 * @details
 * @author qothojol
 *
 * @param x
 * @return long double
 */
long double s21_log(double x) {
  long double result;
  if (x < 0) {
    result = S21_NAN;
  } else if (x == 0) {
    result = -S21_INFINITY;
  } else if (x == 1.0) {
    result = 0.0;
  } else if (s21_isinf(x)) {
    result = S21_INFINITY;
  } else if (s21_isnan(x)) {
    result = S21_NAN;
  } else {
    int i = 0;

    while (x > 1.5) {
      x /= S21_EXP;
      i++;
    }
    while (x < 0.5) {
      x *= S21_EXP;
      i--;
    }

    x -= 1.0;
    long double t = 0.0, z = x;
    for (int k = 1; k <= TAYLOR_ROW_LOG; k++) {
      t += z / k;
      z *= (-x);
    }
    result = t + i;
  }
  return result;
}