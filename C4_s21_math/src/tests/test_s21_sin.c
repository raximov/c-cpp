#include "s21_math_tests.h"

void test_sin(double input) {
  double result = s21_sin(input);
  double expected = sin(input);
  s21_test_case(result, expected);
}

START_TEST(test_sin_normal_value) { test_sin(1000000.0); }
END_TEST

START_TEST(test_sin_minus_value) { test_sin(-14.96); }
END_TEST

START_TEST(test_sin_infinity) { test_sin(INFINITY); }
END_TEST

START_TEST(test_sin_nan) { test_sin(NAN); }
END_TEST

START_TEST(test_sin_minus_infinity) { test_sin(-INFINITY); }
END_TEST

START_TEST(test_sin_pi) { test_sin(M_PI); }
END_TEST

START_TEST(test_sin_half_pi) { test_sin(S21_M_PI_2); }
END_TEST

START_TEST(test_sin_zero) { test_sin(0.0); }
END_TEST

START_TEST(test_sin_minus_pi) { test_sin(-M_PI); }
END_TEST

START_TEST(test_sin_one) { test_sin(1.0); }
END_TEST

START_TEST(test_sin_minus_one) { test_sin(-1.0); }
END_TEST

START_TEST(test_sin_edge_min) { test_sin(DBL_MIN); }
END_TEST

START_TEST(test_minus_sin_nan) { test_sin(-NAN); }
END_TEST

START_TEST(test_sin_below_minus_one) { test_sin(-1.1); }
END_TEST

START_TEST(test_sin_above_one) { test_sin(1.1); }
END_TEST

START_TEST(test_sin_mid_range_positive) { test_sin(0.5); }
END_TEST

START_TEST(test_sin_mid_range_negative) { test_sin(-0.5); }
END_TEST

START_TEST(test_sin_edge_near_one) { test_sin(1.0 - DBL_EPSILON); }
END_TEST

START_TEST(test_sin_edge_over_one) { test_sin(1.0 + DBL_EPSILON); }
END_TEST

START_TEST(test_sin_min_denormalized) { test_sin(DBL_TRUE_MIN); }
END_TEST

START_TEST(test_sin_max_denormalized) {
  double max_denormalized = nextafter(DBL_MIN, 0.0);
  test_sin(max_denormalized);
}
END_TEST

START_TEST(test_sin_min_minus_denormalized) { test_sin(-DBL_TRUE_MIN); }
END_TEST

START_TEST(test_sin_max_minus_denormalized) {
  double max_denormalized = -nextafter(DBL_MIN, 0.0);
  test_sin(max_denormalized);
}
END_TEST

START_TEST(test_sin_edge_minus_min) { test_sin(-DBL_MIN); }
END_TEST

START_TEST(test_sin_min_denormalized_close_above) {
  double input = DBL_TRUE_MIN * 2.0;
  test_sin(input);
}
END_TEST

START_TEST(test_sin_max_denormalized_close_below) {
  double max_denormalized = nextafter(DBL_MIN, 0.0);
  double input = max_denormalized - DBL_TRUE_MIN;
  test_sin(input);
}
END_TEST

START_TEST(test_sin_max_denormalized_close_above) {
  double max_denormalized = nextafter(DBL_MIN, 0.0);
  double input = max_denormalized + DBL_TRUE_MIN;
  test_sin(input);
}
END_TEST

START_TEST(test_sin_denormalized_range) {
  for (double x = DBL_TRUE_MIN; x < DBL_MIN; x *= 1.9187121) {
    test_sin(x);
  }
}
END_TEST

START_TEST(test_sin_negative_denormalized_range) {
  for (double x = -DBL_TRUE_MIN; x > -DBL_MIN; x *= 1.9987121) {
    test_sin(x);
  }
}
END_TEST

START_TEST(test_sin_min_positive_dbl) { test_sin(DBL_MIN - DBL_TRUE_MIN); }
END_TEST

START_TEST(test_sin_min_negative_dbl) { test_sin(-DBL_MIN + DBL_TRUE_MIN); }
END_TEST

START_TEST(test_sin_positive_above_dbl_min) { test_sin(DBL_MIN + DBL_EPSILON); }
END_TEST

START_TEST(test_sin_negative_below_dbl_min) {
  test_sin(-DBL_MIN - DBL_EPSILON);
}
END_TEST
START_TEST(test_sin_negative_edge_near_one) { test_sin(-1.0 - DBL_EPSILON); }
END_TEST

START_TEST(test_sin_negative_edge_over_one) { test_sin(-1.0 + DBL_EPSILON); }
END_TEST

START_TEST(test_sin_negative_half_pi) { test_sin(-S21_M_PI_2); }
END_TEST

START_TEST(test_sin_negative_normal_value) { test_sin(-1000000.0); }
END_TEST

START_TEST(test_sin_pisitive_normal_value) { test_sin(14.96); }
END_TEST

START_TEST(test_sin_above_zero) { test_sin(0.1); }
END_TEST

START_TEST(test_sin_negative_below_zero) { test_sin(-0.1); }
END_TEST

START_TEST(test_sin_edge_below_one_dbl) { test_sin(1.0 - DBL_MIN); }
END_TEST

START_TEST(test_sin_edge_above_one_dbl) { test_sin(1.0 + DBL_MIN); }
END_TEST

START_TEST(test_sin_negative_below_one_dbl) { test_sin(-1.0 - DBL_MIN); }
END_TEST

START_TEST(test_sin_negative_above_one_dbl) { test_sin(-1.0 + DBL_MIN); }
END_TEST

START_TEST(test_sin_3pi_2) { test_sin((M_PI * 3) / 2); }
END_TEST

START_TEST(test_sin_negative_3pi_2) { test_sin((-M_PI * 3) / 2); }
END_TEST

START_TEST(test_sin_below_pi) { test_sin(M_PI - DBL_EPSILON); }
END_TEST

START_TEST(test_sin_negative_below_pi) { test_sin(-M_PI + DBL_EPSILON); }
END_TEST

START_TEST(test_sin_above_pi) { test_sin(M_PI + DBL_EPSILON); }
END_TEST

START_TEST(test_sin_negative_above_pi) { test_sin(-M_PI - DBL_EPSILON); }
END_TEST

START_TEST(test_sin_near_above_one) {
  double my_target = nextafter(1.0, 0.0);
  test_sin(my_target);
}
END_TEST

START_TEST(test_sin_near_below_one) {
  double my_target = nextafter(1.0, 2.0);
  test_sin(my_target);
}
END_TEST

START_TEST(test_sin_negative_near_above_one) {
  double my_target = nextafter(-1.0, 0.0);
  test_sin(my_target);
}
END_TEST

START_TEST(test_sin_negative_near_below_one) {
  double my_target = nextafter(-1.0, -2.0);
  test_sin(my_target);
}
END_TEST

START_TEST(test_sin_1000pi) { test_sin(2000 * M_PI + S21_M_PI_2); }
END_TEST

START_TEST(test_sin_negative_1000pi) { test_sin(-2000 * M_PI - S21_M_PI_2); }
END_TEST

Suite *test_s21_sin(void) {
  Suite *s = suite_create("\033[42m-=S21_sin=-\033[0m");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_sin_normal_value);
  tcase_add_test(tc_core, test_sin_minus_value);
  tcase_add_test(tc_core, test_sin_infinity);
  tcase_add_test(tc_core, test_sin_nan);
  tcase_add_test(tc_core, test_sin_minus_infinity);
  tcase_add_test(tc_core, test_sin_pi);
  tcase_add_test(tc_core, test_sin_half_pi);
  tcase_add_test(tc_core, test_sin_zero);
  tcase_add_test(tc_core, test_sin_minus_pi);
  tcase_add_test(tc_core, test_sin_one);
  tcase_add_test(tc_core, test_sin_minus_one);
  tcase_add_test(tc_core, test_sin_edge_min);
  tcase_add_test(tc_core, test_minus_sin_nan);
  tcase_add_test(tc_core, test_sin_below_minus_one);
  tcase_add_test(tc_core, test_sin_above_one);
  tcase_add_test(tc_core, test_sin_mid_range_positive);
  tcase_add_test(tc_core, test_sin_mid_range_negative);
  tcase_add_test(tc_core, test_sin_edge_near_one);
  tcase_add_test(tc_core, test_sin_edge_over_one);
  tcase_add_test(tc_core, test_sin_min_denormalized);
  tcase_add_test(tc_core, test_sin_max_denormalized);
  tcase_add_test(tc_core, test_sin_min_minus_denormalized);
  tcase_add_test(tc_core, test_sin_max_minus_denormalized);
  tcase_add_test(tc_core, test_sin_edge_minus_min);
  tcase_add_test(tc_core, test_sin_min_denormalized_close_above);
  tcase_add_test(tc_core, test_sin_max_denormalized_close_below);
  tcase_add_test(tc_core, test_sin_max_denormalized_close_above);
  tcase_add_test(tc_core, test_sin_denormalized_range);
  tcase_add_test(tc_core, test_sin_negative_denormalized_range);
  tcase_add_test(tc_core, test_sin_min_positive_dbl);
  tcase_add_test(tc_core, test_sin_min_negative_dbl);
  tcase_add_test(tc_core, test_sin_positive_above_dbl_min);
  tcase_add_test(tc_core, test_sin_negative_below_dbl_min);
  tcase_add_test(tc_core, test_sin_negative_edge_near_one);
  tcase_add_test(tc_core, test_sin_negative_edge_over_one);
  tcase_add_test(tc_core, test_sin_negative_half_pi);
  tcase_add_test(tc_core, test_sin_negative_normal_value);
  tcase_add_test(tc_core, test_sin_pisitive_normal_value);
  tcase_add_test(tc_core, test_sin_above_zero);
  tcase_add_test(tc_core, test_sin_negative_below_zero);
  tcase_add_test(tc_core, test_sin_edge_below_one_dbl);
  tcase_add_test(tc_core, test_sin_edge_above_one_dbl);
  tcase_add_test(tc_core, test_sin_negative_below_one_dbl);
  tcase_add_test(tc_core, test_sin_negative_above_one_dbl);
  tcase_add_test(tc_core, test_sin_3pi_2);
  tcase_add_test(tc_core, test_sin_negative_3pi_2);
  tcase_add_test(tc_core, test_sin_below_pi);
  tcase_add_test(tc_core, test_sin_negative_below_pi);
  tcase_add_test(tc_core, test_sin_above_pi);
  tcase_add_test(tc_core, test_sin_negative_above_pi);
  tcase_add_test(tc_core, test_sin_near_above_one);
  tcase_add_test(tc_core, test_sin_near_below_one);
  tcase_add_test(tc_core, test_sin_negative_near_above_one);
  tcase_add_test(tc_core, test_sin_negative_near_below_one);
  tcase_add_test(tc_core, test_sin_1000pi);
  tcase_add_test(tc_core, test_sin_negative_1000pi);

  suite_add_tcase(s, tc_core);
  return s;
}