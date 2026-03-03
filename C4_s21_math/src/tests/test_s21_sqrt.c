#include <float.h>

#include "s21_math_tests.h"

void test_sqrt(double num) {
  long double result = s21_sqrt(num);
  double origin = sqrt(num);
  s21_test_case(result, origin);
}

START_TEST(test_s21_sqrt_nan) {
  double x = NAN;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_inf) {
  double x = INFINITY;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_zero) {
  double x = 0.0;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_neg_inf) {
  double x = -INFINITY;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_normal1) {
  double x = 400.0;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_normal2) {
  double x = 49202.0;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_normal3) {
  double x = 429849.34;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_one) {
  double x = 1.0;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_neg1) {
  double x = -1323.0;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_neg2) {
  double x = -23144.214;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_minus_zero) {
  double x = -0.0;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_btw_zero_and_one) {
  double x = 0.5;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_btw_zero_and_one2) {
  double x = 0.23;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_near_one) {
  double x = 1.0 - DBL_EPSILON;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_near_one2) {
  double x = 1.0 + DBL_EPSILON;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_double_max) {
  double x = DBL_MAX;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_near_double_max) {
  double x = DBL_MAX - DBL_EPSILON;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_double_min) {
  double x = DBL_MIN;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_near_double_min) {
  double x = DBL_MIN + DBL_EPSILON;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_minus_nan) {
  double x = -NAN;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_min_denormalized) {
  double x = DBL_TRUE_MIN;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_near_min_denormalized) {
  double x = nextafter(DBL_MIN, 0.0);
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_small_range) {
  for (double x = DBL_MIN; x < 1; x *= 100.1) {
    test_sqrt(x);
  }
}
END_TEST

START_TEST(test_s21_sqrt_negative_range) {
  for (double x = -DBL_TRUE_MIN; x < -DBL_MAX; x *= -100.1) {
    test_sqrt(x);
  }
}
END_TEST

START_TEST(test_s21_sqrt_range_btw_zero_one) {
  for (double x = DBL_TRUE_MIN; x < 1; x *= 10.89) {
    test_sqrt(x);
  }
}
END_TEST

START_TEST(test_s21_sqrt_near_zero) {
  double x = 0.0 + DBL_EPSILON;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_next_double_min) {
  double x = DBL_MIN + 1;
  test_sqrt(x);
}
END_TEST

START_TEST(test_s21_sqrt_before_double_max) {
  double x = DBL_MAX - 1;
  test_sqrt(x);
}
END_TEST

Suite *test_s21_sqrt(void) {
  Suite *s = suite_create("\033[42m-=S21_sqrt=-\033[0m");
  ;
  TCase *tc_core = tcase_create("s21_sqrt_tc");

  tcase_add_test(tc_core, test_s21_sqrt_nan);
  tcase_add_test(tc_core, test_s21_sqrt_inf);
  tcase_add_test(tc_core, test_s21_sqrt_zero);
  tcase_add_test(tc_core, test_s21_sqrt_neg_inf);
  tcase_add_test(tc_core, test_s21_sqrt_normal3);
  tcase_add_test(tc_core, test_s21_sqrt_normal2);
  tcase_add_test(tc_core, test_s21_sqrt_normal1);
  tcase_add_test(tc_core, test_s21_sqrt_one);
  tcase_add_test(tc_core, test_s21_sqrt_neg1);
  tcase_add_test(tc_core, test_s21_sqrt_neg2);
  tcase_add_test(tc_core, test_s21_sqrt_minus_zero);
  tcase_add_test(tc_core, test_s21_sqrt_near_one);
  tcase_add_test(tc_core, test_s21_sqrt_near_one2);
  tcase_add_test(tc_core, test_s21_sqrt_btw_zero_and_one);
  tcase_add_test(tc_core, test_s21_sqrt_btw_zero_and_one2);
  tcase_add_test(tc_core, test_s21_sqrt_double_max);
  tcase_add_test(tc_core, test_s21_sqrt_near_double_max);
  tcase_add_test(tc_core, test_s21_sqrt_double_min);
  tcase_add_test(tc_core, test_s21_sqrt_near_double_min);
  tcase_add_test(tc_core, test_s21_sqrt_minus_nan);
  tcase_add_test(tc_core, test_s21_sqrt_min_denormalized);
  tcase_add_test(tc_core, test_s21_sqrt_near_min_denormalized);
  tcase_add_test(tc_core, test_s21_sqrt_small_range);
  tcase_add_test(tc_core, test_s21_sqrt_negative_range);
  tcase_add_test(tc_core, test_s21_sqrt_range_btw_zero_one);
  tcase_add_test(tc_core, test_s21_sqrt_near_zero);
  tcase_add_test(tc_core, test_s21_sqrt_next_double_min);
  tcase_add_test(tc_core, test_s21_sqrt_before_double_max);

  suite_add_tcase(s, tc_core);

  return s;
}
