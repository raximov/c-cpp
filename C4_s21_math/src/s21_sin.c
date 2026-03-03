#include "math_private.h"

/**
 * @brief вычисляет синус
 * @details функция реализована с помощью ряда тейлора
 * @author lambertm
 *
 * @param double x
 * @return long double
 */
long double s21_sin(double x) {
  long double result = 0.0;
  // Проверка на неопределенное число
  if (s21_isnan(x) || s21_isinf(x)) {
    result = S21_NAN;
    // sin(0) == 0
  } else if (x == 0) {
    result = 0;
    // Если x отрицательно, возвращается синус отрицательного значения x.
  } else if (x < 0) {
    result = -1 * s21_sin(-1 * x);
    // Если x больше 2π, возвращается синус остатка от деления x на 2π
  } else if (x > S21_M_PI * 2) {
    result = s21_sin(s21_fmod(x, 2 * S21_M_PI));
  } else {
    result = 1.0;
    long double mul = (x - S21_M_PI / 2);
    mul *= -mul;
    long double teilor = 1;
    for (int i = 1; i < 20; i++) {
      // Вычисляем следующий член ряда
      teilor = teilor * mul / (2 * i * (2 * i - 1));
      result += teilor;
    }
  }
  return result;
}