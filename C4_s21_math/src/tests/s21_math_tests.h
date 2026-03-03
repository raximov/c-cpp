#ifndef S21_MATH_TESTS_H
#define S21_MATH_TESTS_H

#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_math.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846264338328 /* pi */
#endif

Suite *test_s21_abs(void);
Suite *test_s21_acos(void);
Suite *test_s21_asin(void);
Suite *test_s21_atan(void);
Suite *test_s21_ceil(void);
Suite *test_s21_cos(void);
Suite *test_s21_log(void);
Suite *test_s21_exp(void);
Suite *test_s21_fabs(void);
Suite *test_s21_floor(void);
Suite *test_s21_fmod(void);
Suite *test_s21_pow(void);
Suite *test_s21_sin(void);
Suite *test_s21_sqrt(void);
Suite *test_s21_tan(void);

void test_sqrt(double input);
void test_asin(double input);
void test_log(double input);
void test_atan(double input);
void test_acos(double input);
void s21_test_case(double result, double expected);
void test_cos(double input);
void test_ceil(double input);
void test_fabs(double input);
double s21_round_to_16_digits(double x, int numDigits);
double get_tolerance_based_on_digits(int numDigits);
void test_floor(double input);

#endif  // S21_MATH_TESTS_H