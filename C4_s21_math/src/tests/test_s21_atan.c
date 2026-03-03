#include <float.h>

#include "s21_math_tests.h"

void test_atan(double num) {
  long double result = s21_atan(num);
  double origin = atan(num);
  s21_test_case(result, origin);
}

START_TEST(test_s21_atan_nan) {
  double x = NAN;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_inf) {
  double x = INFINITY;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_zero) {
  double x = 0.0;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_neg_inf) {
  double x = -INFINITY;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_normal_1) {
  double x = 1.0;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_normal_2) {
  double x = sqrt(3.0);
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_normal_3) {
  double x = sqrt(3.0) / 3.0;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_normal_neg_1) {
  double x = -1.0;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_normal_neg_2) {
  double x = -sqrt(3.0);
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_normal_neg_3) {
  double x = -sqrt(3.0) / 3.0;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_neg1) {
  double x = -1323.0;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_neg2) {
  double x = -23144.214;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_btw_zero_and_one) {
  double x = 0.5;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_neg_btw_zero_and_one) {
  double x = -0.5;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_btw_zero_and_one2) {
  double x = 0.23;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_neg_btw_zero_and_one2) {
  double x = 0.23;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_near_one) {
  double x = 1.0 - DBL_EPSILON;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_near_one2) {
  double x = 1.0 + DBL_EPSILON;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_double_max) {
  double x = DBL_MAX;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_near_double_max) {
  double x = DBL_MAX - DBL_EPSILON;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_double_min) {
  double x = DBL_MIN;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_near_double_min) {
  double x = DBL_MIN + DBL_EPSILON;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_min_denormalized) {
  double x = DBL_TRUE_MIN;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_near_min_denormalized) {
  double x = nextafter(DBL_MIN, 0.0);
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_small_range) {
  for (double x = DBL_MIN; x < 1; x *= 100.1) {
    test_atan(x);
  }
}
END_TEST

START_TEST(test_s21_atan_negative_range) {
  for (double x = -DBL_TRUE_MIN; x < -DBL_MAX; x *= -100.1) {
    test_atan(x);
  }
}
END_TEST

START_TEST(test_s21_atan_range_btw_zero_one) {
  for (double x = DBL_TRUE_MIN; x < 1; x *= 10.89) {
    test_atan(x);
  }
}
END_TEST

START_TEST(test_s21_atan_near_zero) {
  double x = 0.0 + DBL_EPSILON;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_next_double_min) {
  double x = DBL_MIN + 1;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_before_double_max) {
  double x = DBL_MAX - 1;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_neg_near_one) {
  double x = -1.0 - DBL_EPSILON;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_neg_near_one2) {
  double x = -1.0 + DBL_EPSILON;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_neg_double_max) {
  double x = -DBL_MAX;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_neg_near_double_max) {
  double x = -DBL_MAX + DBL_EPSILON;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_neg_double_min) {
  double x = -DBL_MIN;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_neg_near_double_min) {
  double x = -DBL_MIN + DBL_EPSILON;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_neg_min_denormalized) {
  double x = -DBL_TRUE_MIN;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_neg_near_min_denormalized) {
  double x = nextafter(-DBL_MIN, 0.0);
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_neg_small_range) {
  for (double x = -DBL_MIN; x > -1; x *= -100.1) {
    test_atan(x);
  }
}
END_TEST

START_TEST(test_s21_atan_neg_range_btw_zero_one) {
  for (double x = -DBL_TRUE_MIN; x > -1; x *= -10.89) {
    test_atan(x);
  }
}
END_TEST

START_TEST(test_s21_atan_neg_next_double_min) {
  double x = -DBL_MIN + 1;
  test_atan(x);
}
END_TEST

START_TEST(test_s21_atan_neg_before_double_max) {
  double x = -DBL_MAX + 1;
  test_atan(x);
}
END_TEST

Suite *test_s21_atan(void) {
  Suite *s = suite_create("\033[42m-=S21_atan=-\033[0m");
  ;
  TCase *tc_core = tcase_create("s21_atan_tc");

  tcase_add_test(tc_core, test_s21_atan_nan);
  tcase_add_test(tc_core, test_s21_atan_inf);
  tcase_add_test(tc_core, test_s21_atan_zero);
  tcase_add_test(tc_core, test_s21_atan_neg_inf);
  tcase_add_test(tc_core, test_s21_atan_normal_3);
  tcase_add_test(tc_core, test_s21_atan_normal_2);
  tcase_add_test(tc_core, test_s21_atan_normal_1);
  tcase_add_test(tc_core, test_s21_atan_normal_neg_1);
  tcase_add_test(tc_core, test_s21_atan_normal_neg_2);
  tcase_add_test(tc_core, test_s21_atan_normal_neg_3);
  tcase_add_test(tc_core, test_s21_atan_neg1);
  tcase_add_test(tc_core, test_s21_atan_neg2);
  tcase_add_test(tc_core, test_s21_atan_near_one);
  tcase_add_test(tc_core, test_s21_atan_near_one2);
  tcase_add_test(tc_core, test_s21_atan_neg_near_one);
  tcase_add_test(tc_core, test_s21_atan_neg_near_one2);
  tcase_add_test(tc_core, test_s21_atan_btw_zero_and_one);
  tcase_add_test(tc_core, test_s21_atan_neg_btw_zero_and_one);
  tcase_add_test(tc_core, test_s21_atan_btw_zero_and_one2);
  tcase_add_test(tc_core, test_s21_atan_double_max);
  tcase_add_test(tc_core, test_s21_atan_near_double_max);
  tcase_add_test(tc_core, test_s21_atan_double_min);
  tcase_add_test(tc_core, test_s21_atan_near_double_min);
  tcase_add_test(tc_core, test_s21_atan_min_denormalized);
  tcase_add_test(tc_core, test_s21_atan_near_min_denormalized);
  tcase_add_test(tc_core, test_s21_atan_small_range);
  tcase_add_test(tc_core, test_s21_atan_negative_range);
  tcase_add_test(tc_core, test_s21_atan_range_btw_zero_one);
  tcase_add_test(tc_core, test_s21_atan_near_zero);
  tcase_add_test(tc_core, test_s21_atan_next_double_min);
  tcase_add_test(tc_core, test_s21_atan_before_double_max);
  tcase_add_test(tc_core, test_s21_atan_neg_btw_zero_and_one2);
  tcase_add_test(tc_core, test_s21_atan_neg_double_max);
  tcase_add_test(tc_core, test_s21_atan_neg_near_double_max);
  tcase_add_test(tc_core, test_s21_atan_neg_double_min);
  tcase_add_test(tc_core, test_s21_atan_neg_near_double_min);
  tcase_add_test(tc_core, test_s21_atan_neg_min_denormalized);
  tcase_add_test(tc_core, test_s21_atan_neg_near_min_denormalized);
  tcase_add_test(tc_core, test_s21_atan_neg_small_range);
  tcase_add_test(tc_core, test_s21_atan_neg_range_btw_zero_one);
  tcase_add_test(tc_core, test_s21_atan_neg_next_double_min);
  tcase_add_test(tc_core, test_s21_atan_neg_before_double_max);

  suite_add_tcase(s, tc_core);

  return s;
}
