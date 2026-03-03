#include "math_private.h"

/**
 * @brief возвращает ближайшее целое число, не превышающее заданное значение
 * @details при значениях больше 9223372036854775807 числа double уже не имеют
 * дробной части, поэтому можно просто вернуть это же число
 * @author pirzadsh
 *
 * @param x
 * @return long double
 */

long double s21_ceil(double x) {
  // проверка на бесконечность, Nan, -0.0 и максимальное значение long long int
  if (s21_fabs(x) == S21_INFINITY || x != x || x == -0.0 ||
      s21_fabs(x) > 9223372036854775807.0) {
    return (long double)x;
  } else {
    long long int int_x = (long long int)x;
    if (x > 0 && (x - (double)int_x) != 0.0) {
      int_x += 1;
    }
    long double double_x = (long double)int_x;
    if (x < 0.0 && double_x == 0.0) {
      double_x = -0.0;
    }
    return double_x;
  }
}
