#include "math_private.h"

/**
 * @brief вычисляет абсолютное значение числа с плавающей точкой
 * @details
 * @author pirzadsh
 *
 * @param x
 * @return long double
 */

long double s21_fabs(double x) {
  double result = 0.0;
  if (x != -0.0) {
    result = (x < 0) ? (-x) : x;
  }
  return (long double)result;
}
