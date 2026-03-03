#include <stdlib.h>
#include <time.h>

#include "s21_math_tests.h"

void test_acos(double input) {
  double result = s21_acos(input);
  double expected = acos(input);
  s21_test_case(result, expected);
}

START_TEST(test_acos_zero) { test_acos(0.0); }
END_TEST

START_TEST(test_acos_minus_zero) { test_acos(-0.0); }
END_TEST

START_TEST(test_acos_nan) { test_acos(NAN); }
END_TEST

START_TEST(test_acos_minus_nan) { test_acos(-NAN); }
END_TEST

START_TEST(test_acos_one) { test_acos(1.0); }
END_TEST

START_TEST(test_acos_minus_one) { test_acos(-1.0); }
END_TEST

START_TEST(test_acos_below_minus_one) { test_acos(-1.1); }
END_TEST

START_TEST(test_acos_above_one) { test_acos(1.1); }
END_TEST

START_TEST(test_acos_mid_range_positive) { test_acos(0.5); }
END_TEST

START_TEST(test_acos_mid_range_negative) { test_acos(-0.5); }
END_TEST

START_TEST(test_acos_infinity) { test_acos(INFINITY); }
END_TEST

START_TEST(test_acos_negative_infinity) { test_acos(-INFINITY); }
END_TEST

START_TEST(test_acos_edge_max) { test_acos(DBL_MAX); }
END_TEST

START_TEST(test_acos_edge_minus_max) { test_acos(-DBL_MAX); }
END_TEST

START_TEST(test_acos_edge_min) { test_acos(DBL_MIN); }
END_TEST

START_TEST(test_acos_edge_minus_min) { test_acos(-DBL_MIN); }
END_TEST

START_TEST(test_acos_edge_near_one) { test_acos(1.0 - DBL_EPSILON); }
END_TEST

START_TEST(test_acos_edge_over_one) { test_acos(1.0 + DBL_EPSILON); }
END_TEST

START_TEST(test_acos_min_denormalized) { test_acos(DBL_TRUE_MIN); }
END_TEST

START_TEST(test_acos_min_denormalized_close_above) {
  double input = DBL_TRUE_MIN * 2.0;
  test_acos(input);
}
END_TEST

START_TEST(test_acos_max_denormalized) {
  double max_denormalized = nextafter(DBL_MIN, 0.0);
  test_acos(max_denormalized);
}
END_TEST

START_TEST(test_acos_min_minus_denormalized) { test_acos(-DBL_TRUE_MIN); }
END_TEST

START_TEST(test_acos_max_minus_denormalized) {
  double max_denormalized = -nextafter(DBL_MIN, 0.0);
  test_acos(max_denormalized);
}
END_TEST

START_TEST(test_acos_max_denormalized_close_below) {
  double max_denormalized = nextafter(DBL_MIN, 0.0);
  double input = max_denormalized - DBL_TRUE_MIN;
  test_acos(input);
}
END_TEST

START_TEST(test_acos_max_denormalized_close_above) {
  double max_denormalized = nextafter(DBL_MIN, 0.0);
  double input = max_denormalized + DBL_TRUE_MIN;
  test_acos(input);
}
END_TEST

START_TEST(test_acos_range) {
  srand(time(NULL));
  const int num_tests = 1000;
  for (int i = 0; i < num_tests; i++) {
    double x = (double)rand() / RAND_MAX * (DBL_MAX - DBL_MIN) + DBL_MIN;
    test_acos(x);
  }
}
END_TEST

START_TEST(test_acos_minus_range) {
  srand(time(NULL));
  const int num_tests = 1000;
  for (int i = 0; i < num_tests; i++) {
    double x = (double)rand() / RAND_MAX * (DBL_MAX - DBL_MIN) - DBL_MAX;
    test_acos(x);
  }
}
END_TEST

START_TEST(test_acos_denormalized_range) {
  srand(time(NULL));
  const int num_tests = 1000;
  for (int i = 0; i < num_tests; i++) {
    double x =
        (double)rand() / RAND_MAX * (DBL_MIN - DBL_TRUE_MIN) + DBL_TRUE_MIN;
    test_acos(x);
  }
}
END_TEST

START_TEST(test_acos_negative_denormalized_range) {
  srand(time(NULL));
  const int num_tests = 1000;
  for (int i = 0; i < num_tests; i++) {
    double x = (double)rand() / RAND_MAX * (DBL_MIN - DBL_TRUE_MIN) - DBL_MIN;
    test_acos(x);
  }
}
END_TEST

Suite *test_s21_acos(void) {
  Suite *s = suite_create("\033[42m-=S21_acos=-\033[0m");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_acos_zero);
  tcase_add_test(tc_core, test_acos_minus_zero);
  tcase_add_test(tc_core, test_acos_nan);
  tcase_add_test(tc_core, test_acos_minus_nan);
  tcase_add_test(tc_core, test_acos_one);
  tcase_add_test(tc_core, test_acos_minus_one);
  tcase_add_test(tc_core, test_acos_below_minus_one);
  tcase_add_test(tc_core, test_acos_above_one);
  tcase_add_test(tc_core, test_acos_mid_range_positive);
  tcase_add_test(tc_core, test_acos_mid_range_negative);
  tcase_add_test(tc_core, test_acos_infinity);
  tcase_add_test(tc_core, test_acos_negative_infinity);
  tcase_add_test(tc_core, test_acos_edge_max);
  tcase_add_test(tc_core, test_acos_edge_minus_max);
  tcase_add_test(tc_core, test_acos_edge_min);
  tcase_add_test(tc_core, test_acos_edge_minus_min);
  tcase_add_test(tc_core, test_acos_edge_near_one);
  tcase_add_test(tc_core, test_acos_edge_over_one);
  tcase_add_test(tc_core, test_acos_min_denormalized);
  tcase_add_test(tc_core, test_acos_min_denormalized_close_above);
  tcase_add_test(tc_core, test_acos_max_denormalized);
  tcase_add_test(tc_core, test_acos_min_minus_denormalized);
  tcase_add_test(tc_core, test_acos_max_minus_denormalized);
  tcase_add_test(tc_core, test_acos_max_denormalized_close_below);
  tcase_add_test(tc_core, test_acos_max_denormalized_close_above);
  tcase_add_test(tc_core, test_acos_range);
  tcase_add_test(tc_core, test_acos_minus_range);
  tcase_add_test(tc_core, test_acos_denormalized_range);
  tcase_add_test(tc_core, test_acos_negative_denormalized_range);

  suite_add_tcase(s, tc_core);
  return s;
}