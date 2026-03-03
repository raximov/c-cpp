#ifndef C4_S21_MATH_S21_MATH_MATH_PRIVATE_H_
#define C4_S21_MATH_S21_MATH_MATH_PRIVATE_H_

#include <stdbool.h>
#include <stdint.h>

#include "s21_math.h"

bool s21_isnan(double x);
bool s21_isinf(double x);
long double s21_int_pow(double base, long long exp);
int s21_signbit(double x);

#endif  // C4_S21_MATH_S21_MATH_MATH_PRIVATE_H_