#include <float.h>

#include "s21_math_tests.h"

void test_log(double num) {
  long double result = s21_log(num);
  double origin = log(num);
  s21_test_case(result, origin);
}

START_TEST(test_s21_log_nan) {
  double x = NAN;
  test_log(x);
}
END_TEST

START_TEST(test_s21_log_inf) {
  double x = INFINITY;
  test_log(x);
}
END_TEST

START_TEST(test_s21_log_zero) {
  double x = 0.0;
  test_log(x);
}
END_TEST

START_TEST(test_s21_log_neg_inf) {
  double x = -INFINITY;
  test_log(x);
}
END_TEST

START_TEST(test_s21_log_neg1) {
  double x = -1323.0;
  test_log(x);
}
END_TEST

START_TEST(test_s21_log_neg2) {
  double x = -23144.214;
  test_log(x);
}
END_TEST

START_TEST(test_s21_log_btw_zero_and_one) {
  double x = 0.5;
  test_log(x);
}
END_TEST

START_TEST(test_s21_log_btw_zero_and_one2) {
  double x = 0.23;
  test_log(x);
}
END_TEST

START_TEST(test_s21_log_near_one) {
  double x = 1.0 - DBL_EPSILON;
  test_log(x);
}
END_TEST

START_TEST(test_s21_log_near_one2) {
  double x = 1.0 + DBL_EPSILON;
  test_log(x);
}
END_TEST

START_TEST(test_s21_log_double_max) {
  double x = DBL_MAX;
  test_log(x);
}
END_TEST

START_TEST(test_s21_log_near_double_max) {
  double x = DBL_MAX - DBL_EPSILON;
  test_log(x);
}
END_TEST

START_TEST(test_s21_log_double_min) {
  double x = DBL_MIN;
  test_log(x);
}
END_TEST

START_TEST(test_s21_log_near_double_min) {
  double x = DBL_MIN + DBL_EPSILON;
  test_log(x);
}
END_TEST

START_TEST(test_s21_log_near_min_denormalized) {
  double x = nextafter(DBL_MIN, 0.0);
  test_log(x);
}
END_TEST

START_TEST(test_s21_log_small_range) {
  for (double x = DBL_MIN; x < 1; x *= 100.1) {
    test_log(x);
  }
}
END_TEST

START_TEST(test_s21_log_negative_range) {
  for (double x = -DBL_TRUE_MIN; x < -DBL_MAX; x *= -100.1) {
    test_log(x);
  }
}
END_TEST

START_TEST(test_s21_log_near_zero) {
  double x = 0.0 + DBL_EPSILON;
  test_log(x);
}
END_TEST

START_TEST(test_s21_log_next_double_min) {
  double x = DBL_MIN + 1;
  test_log(x);
}
END_TEST

START_TEST(test_s21_log_before_double_max) {
  double x = DBL_MAX - 1;
  test_log(x);
}
END_TEST

// START_TEST(test_s21_log_neg_near_double_max) {
//   double x = -DBL_MAX + DBL_EPSILON;
//   test_log(x);
// }
// END_TEST

START_TEST(test_s21_log_neg_double_min) {
  double x = -DBL_MIN;
  test_log(x);
}
END_TEST

Suite *test_s21_log(void) {
  Suite *s = suite_create("\033[42m-=S21_log=-\033[0m");
  TCase *tc_core = tcase_create("s21_log_tc");

  tcase_add_test(tc_core, test_s21_log_nan);
  tcase_add_test(tc_core, test_s21_log_inf);
  tcase_add_test(tc_core, test_s21_log_zero);
  tcase_add_test(tc_core, test_s21_log_neg_inf);
  tcase_add_test(tc_core, test_s21_log_neg1);
  tcase_add_test(tc_core, test_s21_log_neg2);
  tcase_add_test(tc_core, test_s21_log_near_one);
  tcase_add_test(tc_core, test_s21_log_near_one2);
  tcase_add_test(tc_core, test_s21_log_btw_zero_and_one);
  tcase_add_test(tc_core, test_s21_log_btw_zero_and_one2);
  tcase_add_test(tc_core, test_s21_log_double_max);
  tcase_add_test(tc_core, test_s21_log_near_double_max);
  tcase_add_test(tc_core, test_s21_log_double_min);
  tcase_add_test(tc_core, test_s21_log_near_double_min);
  tcase_add_test(tc_core, test_s21_log_near_min_denormalized);
  tcase_add_test(tc_core, test_s21_log_small_range);
  tcase_add_test(tc_core, test_s21_log_negative_range);
  tcase_add_test(tc_core, test_s21_log_near_zero);
  tcase_add_test(tc_core, test_s21_log_next_double_min);
  tcase_add_test(tc_core, test_s21_log_before_double_max);
  tcase_add_test(tc_core, test_s21_log_neg_double_min);

  suite_add_tcase(s, tc_core);

  return s;
}