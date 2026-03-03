#include "../math_private.h"

/**
 * @brief Вспомогательная функция для s21_pow для возведения числа в заданную
 * целую степень
 * @details
 * @author lambertm
 * @param double base, long long exp
 * @return long double
 */

long double s21_int_pow(double base, long long exp) {
  long double result = base;

  // Степень равна 0, результат равен 1
  if (exp == 0) {
    result = 1;
  }
  // Степень равна 1, результат равен базе
  else if (exp == 1) {
    result = base;
  }
  // Если степень нечетная, уменьшаем степень на 1 и умножаем на базу
  else if (exp % 2) {
    result = base * s21_int_pow(base, exp - 1);
  }
  // Если степень четная, уменьшаем степень вдвое и возводим квадрат базы в эту
  // степень
  else if (result != 0) {
    result = s21_int_pow(base * base, exp / 2);
  }

  return result;
}