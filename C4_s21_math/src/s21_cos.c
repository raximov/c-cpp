#include "math_private.h"

/**
 * @brief вычисляет косинус
 * @details вычисляет косинус путем вычисления sin(π/2 - x) с использованием
 * ряда Тейлора для синуса.
 * @author lambertm
 *
 * @param x
 * @return long double
 */
long double s21_cos(double x) {
  long double result = 0.0;
  x = s21_fmod(x, 2 * S21_M_PI);
  // Проверка на неопределенное число
  if (s21_isnan(x) || s21_isinf(x)) {
    result = S21_NAN;
    // cos(0) == 1
  } else if (x == 0) {
    result = 1.0;
  } else {
    result = s21_sin(S21_M_PI / 2.0 - x);
  }

  return result;
}