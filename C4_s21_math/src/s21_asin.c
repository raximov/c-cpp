#include "math_private.h"

/**
 * @brief вычисляет арксинус
 * @details
 * @author
 *
 * @param x
 * @return long double
 */
/* @details Через ряды Тейлора страдала точность - реализовал с помощью других
 * функций, ошибки учтены с соответствии с документацией с сайта
 * https://en.cppreference.com/w/c/numeric/math/asin.
 * @author naillora
 * @param double x
 * @return long double
 */
long double s21_asin(double x) {
  if (s21_fabs(x) > 1.0 || s21_isnan(x)) {
    return S21_NAN;
  }
  if (x == 0.0) {
    return x;
  }

  double y = x / s21_sqrt(1.0 - x * x);
  return s21_atan(y);
}