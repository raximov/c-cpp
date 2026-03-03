#include "math_private.h"

/**
 * @brief остаток операции деления с плавающей точкой
 * @details
 * @author
 *
 * @param x
 * @param y
 * @return long double
 */
long double s21_fmod(double x, double y) {
  long double result;
  if (y == 0) {
    result = S21_NAN;
  } else if (x == 0) {
    result = x;
  } else if (s21_isinf(x) && !s21_isnan(y)) {
    result = S21_NAN;
  } else if (s21_isinf(y) && !s21_isinf(x)) {
    result = x;
  } else if (s21_isnan(x) || s21_isnan(y)) {
    result = S21_NAN;
  } else {
    long double xc = x;
    long double yc = y;
    int sign = (xc < 0 || (xc == -0.0));
    if (sign) {
      xc = -xc;
    }
    if (yc < 0 || (yc == -0.0)) {
      yc = -yc;
    }
    long double left = -1;
    long double right = S21_FLT_MAX + 1000;
    int step = 0;

    while (step < S21_STEP) {
      long double mid = (left + right) / 2;
      if (mid * yc <= xc) {
        left = mid;
      } else {
        right = mid;
      }
      step++;
    }
    result = (left - s21_floor(left)) * yc;
    if (sign) {
      result *= -1;
    }
  }
  return result;
}