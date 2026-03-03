#include "math_private.h"

/**
 * @brief вычисляет арккосинус
 * @details информацию по обработке ошибок брад с сайта
 * https://en.cppreference.com/w/c/numeric/math/acos. Изначально делал через ряд
 * Тейлора, но страдала точность при значениях близких к 1 и -1. Насколько я
 * понимаю - арктангенс через Тейлора должен быть точнее, поэтому решил делать
 * через него
 * @author naillora
 *
 * @param double x
 * @return long double
 */
long double s21_acos(double x) {
  if (s21_fabs(x) > 1.0 || s21_isnan(x)) {
    return S21_NAN;
  }
  double y = s21_sqrt((1.0 - x) / (1.0 + x));
  return 2.0 * s21_atan(y);
}