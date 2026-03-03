#include "s21_math_tests.h"

void s21_test_case(double result, double expected) {
  if (isnan(expected)) {
    ck_assert_ldouble_nan(result);
  } else if (isinf(expected)) {
    ck_assert_ldouble_infinite(result);
    ck_assert(signbit(expected) == signbit(result));
  } else {
    // если в целой части 11 значащих цифр или больше
    if (fabs(result) >= 10000000000.0) {
      // считаем значимые цифры в целой части
      int numDigits = (int)log10(fabs(result)) + 1;

      // если 16 значащих цифр или больше, обрезаем до 16 цифр и сравниваем
      if (numDigits > 15) {
        result = s21_round_to_16_digits(result, numDigits);
        expected = s21_round_to_16_digits(expected, numDigits);
        ck_assert_double_eq(result, expected);
      }

      // если в целой части 15 значащих цифр, сравниваем до 1 знака после
      // запятой, если 14 -- до 2, если 13 -- до 3 и т.д.
      else {
        double tolerance = get_tolerance_based_on_digits(numDigits);
        ck_assert_double_eq_tol(result, expected, tolerance);
      }

      // если в целой части меньше 11 значащих цифр, сравниваем до 6 знака после
      // запятой
    } else {
      ck_assert_double_eq_tol(result, expected, 1e-6);
    }
    ck_assert(signbit(expected) == signbit(result));
  }
}

double s21_round_to_16_digits(double x, int numDigits) {
  // Считаем, на сколько порядков делить x
  int scaleFactor = numDigits - 16;
  // И делим
  x /= pow(10.0, scaleFactor);
  // Округляем, чтобы получить ровно 16 значащих цифр
  x = round(x);
  return x;
}

double get_tolerance_based_on_digits(int numDigits) {
  double tolerance = 0.0;
  switch (numDigits) {
    case 15:
      tolerance = 1e-1;
      break;

    case 14:
      tolerance = 1e-2;
      break;

    case 13:
      tolerance = 1e-3;
      break;

    case 12:
      tolerance = 1e-4;
      break;

    case 11:
      tolerance = 1e-5;
      break;

    default:
      break;
  }
  return tolerance;
}