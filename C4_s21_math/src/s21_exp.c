#include "math_private.h"

/**
 * @brief возвращает значение e, возведенное в заданную степень
 * @details
 * @author naillora
 *
 * @param double x
 * @return long double
 */
long double s21_exp(double x) {
  long double result;
  if (s21_isnan(x)) {
    result = S21_NAN;
  } else if (s21_isinf(x) && !s21_signbit(x)) {
    result = S21_INFINITY;
  } else if (s21_isinf(x) && s21_signbit(x)) {
    result = 0;
  } else if (x == 0) {
    result = 1;
  } else {
    long double left = 0;
    long double right = S21_FLT_MAX + 1000;
    result = (left + right) / 2;
    int step = 0;
    while (step++ < S21_STEP && (right - left) > 1e-8) {
      long double curr_y = s21_log(result);
      if (curr_y < x) {
        left = result;
        result = (left + right) / 2;
      } else {
        right = result;
        result = (left + right) / 2;
      }
    }
  }
  return result;
}