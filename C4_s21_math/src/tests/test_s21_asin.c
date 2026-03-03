#include <stdlib.h>
#include <time.h>

#include "s21_math_tests.h"

void test_asin(double input) {
  double result = s21_asin(input);
  double expected = asin(input);
  s21_test_case(result, expected);
}

START_TEST(test_asin_zero) { test_asin(0.0); }
END_TEST

START_TEST(test_asin_minus_zero) { test_asin(-0.0); }
END_TEST

START_TEST(test_asin_nan) { test_asin(NAN); }
END_TEST

START_TEST(test_asin_minus_nan) { test_asin(-NAN); }
END_TEST

START_TEST(test_asin_one) { test_asin(1.0); }
END_TEST

START_TEST(test_asin_minus_one) { test_asin(-1.0); }
END_TEST

START_TEST(test_asin_below_minus_one) { test_asin(-1.1); }
END_TEST

START_TEST(test_asin_above_one) { test_asin(1.1); }
END_TEST

START_TEST(test_asin_mid_range_positive) { test_asin(0.5); }
END_TEST

START_TEST(test_asin_mid_range_negative) { test_asin(-0.5); }
END_TEST

START_TEST(test_asin_infinity) { test_asin(INFINITY); }
END_TEST

START_TEST(test_asin_negative_infinity) { test_asin(-INFINITY); }
END_TEST

START_TEST(test_asin_edge_max) { test_asin(DBL_MAX); }
END_TEST

START_TEST(test_asin_edge_minus_max) { test_asin(-DBL_MAX); }
END_TEST

START_TEST(test_asin_edge_min) { test_asin(DBL_MIN); }
END_TEST

START_TEST(test_asin_edge_minus_min) { test_asin(-DBL_MIN); }
END_TEST

START_TEST(test_asin_edge_near_one) { test_asin(1.0 - DBL_EPSILON); }
END_TEST

START_TEST(test_asin_edge_over_one) { test_asin(1.0 + DBL_EPSILON); }
END_TEST

START_TEST(test_asin_min_denormalized) { test_asin(DBL_TRUE_MIN); }
END_TEST

START_TEST(test_asin_min_denormalized_close_above) {
  double input = DBL_TRUE_MIN * 2.0;
  test_asin(input);
}
END_TEST

START_TEST(test_asin_max_denormalized) {
  double max_denormalized = nextafter(DBL_MIN, 0.0);
  test_asin(max_denormalized);
}
END_TEST

START_TEST(test_asin_min_minus_denormalized) { test_asin(-DBL_TRUE_MIN); }
END_TEST

START_TEST(test_asin_max_minus_denormalized) {
  double max_denormalized = -nextafter(DBL_MIN, 0.0);
  test_asin(max_denormalized);
}
END_TEST

START_TEST(test_asin_max_denormalized_close_below) {
  double max_denormalized = nextafter(DBL_MIN, 0.0);
  double input = max_denormalized - DBL_TRUE_MIN;
  test_asin(input);
}
END_TEST

START_TEST(test_asin_max_denormalized_close_above) {
  double max_denormalized = nextafter(DBL_MIN, 0.0);
  double input = max_denormalized + DBL_TRUE_MIN;
  test_asin(input);
}
END_TEST

START_TEST(test_asin_range) {
  srand(time(NULL));
  const int num_tests = 1000;
  for (int i = 0; i < num_tests; i++) {
    double x = (double)rand() / RAND_MAX * (DBL_MAX - DBL_MIN) + DBL_MIN;
    test_asin(x);
  }
}
END_TEST

START_TEST(test_asin_minus_range) {
  srand(time(NULL));
  const int num_tests = 1000;
  for (int i = 0; i < num_tests; i++) {
    double x = (double)rand() / RAND_MAX * (DBL_MAX - DBL_MIN) - DBL_MAX;
    test_asin(x);
  }
}
END_TEST

START_TEST(test_asin_denormalized_range) {
  srand(time(NULL));
  const int num_tests = 1000;
  for (int i = 0; i < num_tests; i++) {
    double x =
        (double)rand() / RAND_MAX * (DBL_MIN - DBL_TRUE_MIN) + DBL_TRUE_MIN;
    test_asin(x);
  }
}
END_TEST

START_TEST(test_asin_negative_denormalized_range) {
  srand(time(NULL));
  const int num_tests = 1000;
  for (int i = 0; i < num_tests; i++) {
    double x = (double)rand() / RAND_MAX * (DBL_MIN - DBL_TRUE_MIN) - DBL_MIN;
    test_asin(x);
  }
}
END_TEST

Suite *test_s21_asin(void) {
  Suite *s = suite_create("\033[42m-=S21_asin=-\033[0m");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_asin_zero);
  tcase_add_test(tc_core, test_asin_minus_zero);
  tcase_add_test(tc_core, test_asin_nan);
  tcase_add_test(tc_core, test_asin_minus_nan);
  tcase_add_test(tc_core, test_asin_one);
  tcase_add_test(tc_core, test_asin_minus_one);
  tcase_add_test(tc_core, test_asin_below_minus_one);
  tcase_add_test(tc_core, test_asin_above_one);
  tcase_add_test(tc_core, test_asin_mid_range_positive);
  tcase_add_test(tc_core, test_asin_mid_range_negative);
  tcase_add_test(tc_core, test_asin_infinity);
  tcase_add_test(tc_core, test_asin_negative_infinity);
  tcase_add_test(tc_core, test_asin_edge_max);
  tcase_add_test(tc_core, test_asin_edge_minus_max);
  tcase_add_test(tc_core, test_asin_edge_min);
  tcase_add_test(tc_core, test_asin_edge_minus_min);
  tcase_add_test(tc_core, test_asin_edge_near_one);
  tcase_add_test(tc_core, test_asin_edge_over_one);
  tcase_add_test(tc_core, test_asin_min_denormalized);
  tcase_add_test(tc_core, test_asin_min_denormalized_close_above);
  tcase_add_test(tc_core, test_asin_max_denormalized);
  tcase_add_test(tc_core, test_asin_min_minus_denormalized);
  tcase_add_test(tc_core, test_asin_max_minus_denormalized);
  tcase_add_test(tc_core, test_asin_max_denormalized_close_below);
  tcase_add_test(tc_core, test_asin_max_denormalized_close_above);
  tcase_add_test(tc_core, test_asin_range);
  tcase_add_test(tc_core, test_asin_minus_range);
  tcase_add_test(tc_core, test_asin_denormalized_range);
  tcase_add_test(tc_core, test_asin_negative_denormalized_range);

  suite_add_tcase(s, tc_core);
  return s;
}