#include "math_private.h"

/**
 * @brief возводит число в заданную степень
 * @details
 * @author lambertm
 *
 * @param base
 * @param exp
 * @return long double
 */
long double s21_pow(double base, double exp) {
  long double res = 0;
  // Округляем exp до целого числа
  long double int_exp = s21_floor(exp);

  // Если exp равен 0 или base равен 1, результат равен 1
  if (exp == 0 || base == 1) {
    res = 1;
  }
  // Прооверка на нан
  else if (s21_isnan(exp) || s21_isnan(base)) {
    res = S21_NAN;
  } else if (exp == S21_INFINITY) {
    // Если exp равен бесконечности
    if (s21_fabs(base) == 1) {
      res = 1;
    }
    // Если base равен 1, результат равен 1
    else if (s21_fabs(base) > 1) {
      res = S21_INFINITY;
    }
    // Если base больше 1, результат бесконечность
    else {
      res = 0;
    }
    // Иначе результат равен 0
  } else if (base == -S21_INFINITY && exp != -S21_INFINITY) {
    // Если base равен отрицательной бесконечности и exp не равен отрицательной
    // бесконечности
    if (exp < 0) {
      res = 0;
    }
    // Если exp отрицательно, результат равен 0
    else {
      res = s21_int_pow(-1, s21_fabs(exp)) * S21_INFINITY;
    }
    // Иначе результат определяется как (-1)^|exp| *
    // бесконечность
  } else if (base < 0 && s21_floor(exp) != exp) {
    res = S21_NAN;
    // Если base отрицательное и exp не является целым числом,
    // результат NaN
  } else if (exp < 0) {
    // Если exp отрицательно
    if (base == 0) {
      res = S21_INFINITY;
    }
    // Если base равен 0, результат бесконечность
    else {
      res = 1 / s21_pow(base, -1 * exp);
    }
    // Иначе результат равен 1 / base^(-exp)
  } else if (exp > S21_FLT_MAX || exp == int_exp) {
    res = s21_int_pow(base, (long long)exp);
    // Если exp больше максимального значения или равен
    // целому числу, используется целочисленная степень
  } else {
    // В остальных случаях используется формула a^b = exp(ln(a) * (b - int(b)))
    // * a^int(b)
    res = s21_exp(s21_log(base) * (exp - int_exp)) * s21_int_pow(base, int_exp);
  }
  return res;
}