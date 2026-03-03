#include "s21_math_tests.h"

void test_tan(double input) {
  double result = s21_tan(input);
  double expected = tan(input);
  s21_test_case(result, expected);
}

START_TEST(test_tan_normal_value) { test_tan(1000000.0); }
END_TEST

START_TEST(test_tan_minus_value) { test_tan(-14.96); }
END_TEST

START_TEST(test_tan_infinity) { test_tan(INFINITY); }
END_TEST

START_TEST(test_tan_nan) { test_tan(NAN); }
END_TEST

START_TEST(test_tan_minus_infinity) { test_tan(-INFINITY); }
END_TEST

START_TEST(test_tan_pi) { test_tan(M_PI); }
END_TEST

START_TEST(test_tan_zero) { test_tan(0.0); }
END_TEST

START_TEST(test_tan_minus_pi) { test_tan(-M_PI); }
END_TEST

START_TEST(test_tan_one) { test_tan(1.0); }
END_TEST

START_TEST(test_tan_minus_one) { test_tan(-1.0); }
END_TEST

START_TEST(test_tan_edge_min) { test_tan(DBL_MIN); }
END_TEST

START_TEST(test_minus_tan_nan) { test_tan(-NAN); }
END_TEST

START_TEST(test_tan_below_minus_one) { test_tan(-1.1); }
END_TEST

START_TEST(test_tan_above_one) { test_tan(1.1); }
END_TEST

START_TEST(test_tan_mid_range_positive) { test_tan(0.5); }
END_TEST

START_TEST(test_tan_mid_range_negative) { test_tan(-0.5); }
END_TEST

START_TEST(test_tan_edge_near_one) { test_tan(1.0 - DBL_EPSILON); }
END_TEST

START_TEST(test_tan_edge_over_one) { test_tan(1.0 + DBL_EPSILON); }
END_TEST

START_TEST(test_tan_min_denormalized) { test_tan(DBL_TRUE_MIN); }
END_TEST

START_TEST(test_tan_max_denormalized) {
  double max_denormalized = nextafter(DBL_MIN, 0.0);
  test_tan(max_denormalized);
}
END_TEST

START_TEST(test_tan_min_minus_denormalized) { test_tan(-DBL_TRUE_MIN); }
END_TEST

START_TEST(test_tan_max_minus_denormalized) {
  double max_denormalized = -nextafter(DBL_MIN, 0.0);
  test_tan(max_denormalized);
}
END_TEST

START_TEST(test_tan_edge_minus_min) { test_tan(-DBL_MIN); }
END_TEST

START_TEST(test_tan_min_denormalized_close_above) {
  double input = DBL_TRUE_MIN * 2.0;
  test_tan(input);
}
END_TEST

START_TEST(test_tan_max_denormalized_close_below) {
  double max_denormalized = nextafter(DBL_MIN, 0.0);
  double input = max_denormalized - DBL_TRUE_MIN;
  test_tan(input);
}
END_TEST

START_TEST(test_tan_max_denormalized_close_above) {
  double max_denormalized = nextafter(DBL_MIN, 0.0);
  double input = max_denormalized + DBL_TRUE_MIN;
  test_tan(input);
}
END_TEST

START_TEST(test_tan_denormalized_range) {
  for (double x = DBL_TRUE_MIN; x < DBL_MIN; x *= 1.9187121) {
    test_tan(x);
  }
}
END_TEST

START_TEST(test_tan_negative_denormalized_range) {
  for (double x = -DBL_TRUE_MIN; x > -DBL_MIN; x *= 1.9987121) {
    test_tan(x);
  }
}
END_TEST

START_TEST(test_tan_min_positive_dbl) { test_tan(DBL_MIN - DBL_TRUE_MIN); }
END_TEST

START_TEST(test_tan_min_negative_dbl) { test_tan(-DBL_MIN + DBL_TRUE_MIN); }
END_TEST

START_TEST(test_tan_positive_above_dbl_min) { test_tan(DBL_MIN + DBL_EPSILON); }
END_TEST

START_TEST(test_tan_negative_below_dbl_min) {
  test_tan(-DBL_MIN - DBL_EPSILON);
}
END_TEST

START_TEST(test_tan_negative_edge_near_one) { test_tan(-1.0 - DBL_EPSILON); }
END_TEST

START_TEST(test_tan_negative_edge_over_one) { test_tan(-1.0 + DBL_EPSILON); }
END_TEST

START_TEST(test_tan_negative_normal_value) { test_tan(-1000000.0); }
END_TEST

START_TEST(test_tan_pisitive_normal_value) { test_tan(14.96); }
END_TEST

START_TEST(test_tan_above_zero) { test_tan(0.1); }
END_TEST

START_TEST(test_tan_negative_below_zero) { test_tan(-0.1); }
END_TEST

START_TEST(test_tan_edge_below_one_dbl) { test_tan(1.0 - DBL_MIN); }
END_TEST

START_TEST(test_tan_edge_above_one_dbl) { test_tan(1.0 + DBL_MIN); }
END_TEST

START_TEST(test_tan_negative_below_one_dbl) { test_tan(-1.0 - DBL_MIN); }
END_TEST

START_TEST(test_tan_negative_above_one_dbl) { test_tan(-1.0 + DBL_MIN); }
END_TEST

START_TEST(test_tan_below_pi) { test_tan(M_PI - DBL_EPSILON); }
END_TEST

START_TEST(test_tan_negative_below_pi) { test_tan(-M_PI + DBL_EPSILON); }
END_TEST

START_TEST(test_tan_above_pi) { test_tan(M_PI + DBL_EPSILON); }
END_TEST

START_TEST(test_tan_negative_above_pi) { test_tan(-M_PI - DBL_EPSILON); }
END_TEST

START_TEST(test_tan_near_above_one) {
  double my_target = nextafter(1.0, 0.0);
  test_tan(my_target);
}
END_TEST

START_TEST(test_tan_near_below_one) {
  double my_target = nextafter(1.0, 2.0);
  test_tan(my_target);
}
END_TEST

START_TEST(test_tan_negative_near_above_one) {
  double my_target = nextafter(-1.0, 0.0);
  test_tan(my_target);
}
END_TEST

START_TEST(test_tan_negative_near_below_one) {
  double my_target = nextafter(-1.0, -2.0);
  test_tan(my_target);
}
END_TEST

Suite *test_s21_tan(void) {
  Suite *s = suite_create("\033[42m-=S21_tan=-\033[0m");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_tan_normal_value);
  tcase_add_test(tc_core, test_tan_minus_value);
  tcase_add_test(tc_core, test_tan_infinity);
  tcase_add_test(tc_core, test_tan_nan);
  tcase_add_test(tc_core, test_tan_minus_infinity);
  tcase_add_test(tc_core, test_tan_pi);
  tcase_add_test(tc_core, test_tan_zero);
  tcase_add_test(tc_core, test_tan_minus_pi);
  tcase_add_test(tc_core, test_tan_one);
  tcase_add_test(tc_core, test_tan_minus_one);
  tcase_add_test(tc_core, test_tan_edge_min);
  tcase_add_test(tc_core, test_minus_tan_nan);
  tcase_add_test(tc_core, test_tan_below_minus_one);
  tcase_add_test(tc_core, test_tan_above_one);
  tcase_add_test(tc_core, test_tan_mid_range_positive);
  tcase_add_test(tc_core, test_tan_mid_range_negative);
  tcase_add_test(tc_core, test_tan_edge_near_one);
  tcase_add_test(tc_core, test_tan_edge_over_one);
  tcase_add_test(tc_core, test_tan_min_denormalized);
  tcase_add_test(tc_core, test_tan_max_denormalized);
  tcase_add_test(tc_core, test_tan_min_minus_denormalized);
  tcase_add_test(tc_core, test_tan_max_minus_denormalized);
  tcase_add_test(tc_core, test_tan_edge_minus_min);
  tcase_add_test(tc_core, test_tan_min_denormalized_close_above);
  tcase_add_test(tc_core, test_tan_max_denormalized_close_below);
  tcase_add_test(tc_core, test_tan_max_denormalized_close_above);
  tcase_add_test(tc_core, test_tan_denormalized_range);
  tcase_add_test(tc_core, test_tan_negative_denormalized_range);
  tcase_add_test(tc_core, test_tan_min_positive_dbl);
  tcase_add_test(tc_core, test_tan_min_negative_dbl);
  tcase_add_test(tc_core, test_tan_positive_above_dbl_min);
  tcase_add_test(tc_core, test_tan_negative_below_dbl_min);
  tcase_add_test(tc_core, test_tan_negative_edge_near_one);
  tcase_add_test(tc_core, test_tan_negative_edge_over_one);
  tcase_add_test(tc_core, test_tan_negative_normal_value);
  tcase_add_test(tc_core, test_tan_pisitive_normal_value);
  tcase_add_test(tc_core, test_tan_above_zero);
  tcase_add_test(tc_core, test_tan_negative_below_zero);
  tcase_add_test(tc_core, test_tan_edge_below_one_dbl);
  tcase_add_test(tc_core, test_tan_edge_above_one_dbl);
  tcase_add_test(tc_core, test_tan_negative_below_one_dbl);
  tcase_add_test(tc_core, test_tan_negative_above_one_dbl);
  tcase_add_test(tc_core, test_tan_below_pi);
  tcase_add_test(tc_core, test_tan_negative_below_pi);
  tcase_add_test(tc_core, test_tan_above_pi);
  tcase_add_test(tc_core, test_tan_negative_above_pi);
  tcase_add_test(tc_core, test_tan_near_above_one);
  tcase_add_test(tc_core, test_tan_near_below_one);
  tcase_add_test(tc_core, test_tan_negative_near_above_one);
  tcase_add_test(tc_core, test_tan_negative_near_below_one);

  suite_add_tcase(s, tc_core);
  return s;
}