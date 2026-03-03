#include "math_private.h"

/**
 * @brief вычисляет тангенс
 * @details
 * @author lambertm
 *
 * @param x
 * @return long double
 */
long double s21_tan(double x) {
  long double result = 0.0;
  if (s21_isnan(x) || s21_isinf(x)) {
    result = S21_NAN;
  } else if (x == 0) {
    result = 0;
  } else {
    result = s21_sin(x) / s21_cos(x);
  }
  return result;
}