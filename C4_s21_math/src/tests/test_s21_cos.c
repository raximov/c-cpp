#include "s21_math_tests.h"

void test_cos(double input) {
  double result = s21_cos(input);
  double expected = cos(input);
  s21_test_case(result, expected);
}

START_TEST(test_cos_normal_value) { test_cos(1000000); }
END_TEST

START_TEST(test_cos_minus_value) { test_cos(-14.96); }
END_TEST

START_TEST(test_cos_infinity) { test_cos(INFINITY); }
END_TEST

START_TEST(test_cos_nan) { test_cos(NAN); }
END_TEST

START_TEST(test_cos_minus_infinity) { test_cos(-INFINITY); }
END_TEST

START_TEST(test_cos_pi) { test_cos(M_PI); }
END_TEST

START_TEST(test_cos_half_pi) { test_cos(M_PI / 2.0); }
END_TEST

START_TEST(test_cos_zero) { test_cos(0.0); }
END_TEST

START_TEST(test_cos_minus_pi) { test_cos(-M_PI); }
END_TEST

START_TEST(test_cos_one) { test_cos(1.0); }
END_TEST

START_TEST(test_cos_minus_one) { test_cos(-1.0); }
END_TEST

START_TEST(test_cos_edge_min) { test_cos(DBL_MIN); }
END_TEST

START_TEST(test_cos_minus_zero) { test_cos(-0.0); }
END_TEST

START_TEST(test_minus_cos_nan) { test_cos(-NAN); }
END_TEST

START_TEST(test_cos_below_minus_one) { test_cos(-1.1); }
END_TEST

START_TEST(test_cos_above_one) { test_cos(1.1); }
END_TEST

START_TEST(test_cos_mid_range_positive) { test_cos(0.5); }
END_TEST

START_TEST(test_cos_mid_range_negative) { test_cos(-0.5); }
END_TEST

START_TEST(test_cos_edge_near_one) { test_cos(1.0 - DBL_EPSILON); }
END_TEST

START_TEST(test_cos_edge_over_one) { test_cos(1.0 + DBL_EPSILON); }
END_TEST

START_TEST(test_cos_min_denormalized) { test_cos(DBL_TRUE_MIN); }
END_TEST

START_TEST(test_cos_max_denormalized) {
  double max_denormalized = nextafter(DBL_MIN, 0.0);
  test_cos(max_denormalized);
}
END_TEST

START_TEST(test_cos_min_minus_denormalized) { test_cos(-DBL_TRUE_MIN); }
END_TEST

START_TEST(test_cos_max_minus_denormalized) {
  double max_denormalized = -nextafter(DBL_MIN, 0.0);
  test_cos(max_denormalized);
}
END_TEST

START_TEST(test_cos_edge_minus_min) { test_cos(-DBL_MIN); }
END_TEST

START_TEST(test_cos_min_denormalized_close_above) {
  double input = DBL_TRUE_MIN * 2.0;
  test_cos(input);
}
END_TEST

START_TEST(test_cos_max_denormalized_close_below) {
  double max_denormalized = nextafter(DBL_MIN, 0.0);
  double input = max_denormalized - DBL_TRUE_MIN;
  test_cos(input);
}
END_TEST

START_TEST(test_cos_max_denormalized_close_above) {
  double max_denormalized = nextafter(DBL_MIN, 0.0);
  double input = max_denormalized + DBL_TRUE_MIN;
  test_cos(input);
}
END_TEST

START_TEST(test_cos_minus_range) {
  for (double x = -DBL_MAX; x > DBL_MIN; x *= 2.1987121) {
    test_cos(x);
  }
}
END_TEST

START_TEST(test_cos_denormalized_range) {
  for (double x = DBL_TRUE_MIN; x < DBL_MIN; x *= 2.1987121) {
    test_cos(x);
  }
}
END_TEST

START_TEST(test_cos_negative_denormalized_range) {
  for (double x = -DBL_TRUE_MIN; x > -DBL_MIN; x *= 2.1987121) {
    test_cos(x);
  }
}
END_TEST

START_TEST(test_cos_min_positive_dbl) { test_cos(DBL_MIN - DBL_TRUE_MIN); }
END_TEST

START_TEST(test_cos_min_negative_dbl) { test_cos(-DBL_MIN + DBL_TRUE_MIN); }
END_TEST
START_TEST(test_cos_positive_above_dbl_min) { test_cos(DBL_MIN + DBL_EPSILON); }
END_TEST

START_TEST(test_cos_negative_below_dbl_min) {
  test_cos(-DBL_MIN - DBL_EPSILON);
}
END_TEST

START_TEST(test_cos_negative_edge_near_one) { test_cos(-1.0 - DBL_EPSILON); }
END_TEST

START_TEST(test_cos_negative_edge_over_one) { test_cos(-1.0 + DBL_EPSILON); }
END_TEST

START_TEST(test_cos_negative_half_pi) { test_cos(-S21_M_PI_2); }
END_TEST

START_TEST(test_cos_negative_normal_value) { test_cos(-1000000.0); }
END_TEST

START_TEST(test_cos_pisitive_normal_value) { test_cos(14.96); }
END_TEST

START_TEST(test_cos_above_zero) { test_cos(0.1); }
END_TEST

START_TEST(test_cos_negative_below_zero) { test_cos(-0.1); }
END_TEST

START_TEST(test_cos_edge_below_one_dbl) { test_cos(1.0 - DBL_MIN); }
END_TEST

START_TEST(test_cos_edge_above_one_dbl) { test_cos(1.0 + DBL_MIN); }
END_TEST

START_TEST(test_cos_negative_below_one_dbl) { test_cos(-1.0 - DBL_MIN); }
END_TEST

START_TEST(test_cos_negative_above_one_dbl) { test_cos(-1.0 + DBL_MIN); }
END_TEST

START_TEST(test_cos_3pi_2) { test_cos((M_PI * 3) / 2); }
END_TEST

/*START_TEST(test_cos_negative_3pi_2) { test_cos((-M_PI * 3) / 2); }
END_TEST*/

START_TEST(test_cos_below_pi) { test_cos(M_PI - DBL_EPSILON); }
END_TEST

START_TEST(test_cos_negative_below_pi) { test_cos(-M_PI + DBL_EPSILON); }
END_TEST

START_TEST(test_cos_above_pi) { test_cos(M_PI + DBL_EPSILON); }
END_TEST

START_TEST(test_cos_negative_above_pi) { test_cos(-M_PI - DBL_EPSILON); }
END_TEST

START_TEST(test_cos_near_above_one) {
  double my_target = nextafter(1.0, 0.0);
  test_cos(my_target);
}
END_TEST

START_TEST(test_cos_near_below_one) {
  double my_target = nextafter(1.0, 2.0);
  test_cos(my_target);
}
END_TEST

START_TEST(test_cos_negative_near_above_one) {
  double my_target = nextafter(-1.0, 0.0);
  test_cos(my_target);
}
END_TEST

START_TEST(test_cos_negative_near_below_one) {
  double my_target = nextafter(-1.0, -2.0);
  test_cos(my_target);
}
END_TEST

START_TEST(test_cos_1000pi) { test_cos(2000 * M_PI + S21_M_PI_2); }
END_TEST

START_TEST(test_cos_negative_1000pi) { test_cos(-2000 * M_PI - S21_M_PI_2); }
END_TEST

Suite *test_s21_cos(void) {
  Suite *s = suite_create("\033[42m-=S21_cos=-\033[0m");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_cos_normal_value);
  tcase_add_test(tc_core, test_cos_minus_value);
  tcase_add_test(tc_core, test_cos_infinity);
  tcase_add_test(tc_core, test_cos_nan);
  tcase_add_test(tc_core, test_cos_minus_infinity);
  tcase_add_test(tc_core, test_cos_pi);
  tcase_add_test(tc_core, test_cos_half_pi);
  tcase_add_test(tc_core, test_cos_zero);
  tcase_add_test(tc_core, test_cos_minus_pi);
  tcase_add_test(tc_core, test_cos_one);
  tcase_add_test(tc_core, test_cos_minus_one);
  tcase_add_test(tc_core, test_cos_edge_min);
  tcase_add_test(tc_core, test_cos_minus_zero);
  tcase_add_test(tc_core, test_minus_cos_nan);
  tcase_add_test(tc_core, test_cos_below_minus_one);
  tcase_add_test(tc_core, test_cos_above_one);
  tcase_add_test(tc_core, test_cos_mid_range_positive);
  tcase_add_test(tc_core, test_cos_mid_range_negative);
  tcase_add_test(tc_core, test_cos_edge_near_one);
  tcase_add_test(tc_core, test_cos_edge_over_one);
  tcase_add_test(tc_core, test_cos_min_denormalized);
  tcase_add_test(tc_core, test_cos_max_denormalized);
  tcase_add_test(tc_core, test_cos_min_minus_denormalized);
  tcase_add_test(tc_core, test_cos_max_minus_denormalized);
  tcase_add_test(tc_core, test_cos_edge_minus_min);
  tcase_add_test(tc_core, test_cos_min_denormalized_close_above);
  tcase_add_test(tc_core, test_cos_max_denormalized_close_below);
  tcase_add_test(tc_core, test_cos_max_denormalized_close_above);
  tcase_add_test(tc_core, test_cos_minus_range);
  tcase_add_test(tc_core, test_cos_denormalized_range);
  tcase_add_test(tc_core, test_cos_negative_denormalized_range);
  tcase_add_test(tc_core, test_cos_min_positive_dbl);
  tcase_add_test(tc_core, test_cos_min_negative_dbl);
  tcase_add_test(tc_core, test_cos_positive_above_dbl_min);
  tcase_add_test(tc_core, test_cos_negative_below_dbl_min);
  tcase_add_test(tc_core, test_cos_negative_edge_near_one);
  tcase_add_test(tc_core, test_cos_negative_edge_over_one);
  tcase_add_test(tc_core, test_cos_negative_half_pi);
  tcase_add_test(tc_core, test_cos_negative_normal_value);
  tcase_add_test(tc_core, test_cos_pisitive_normal_value);
  tcase_add_test(tc_core, test_cos_above_zero);
  tcase_add_test(tc_core, test_cos_negative_below_zero);
  tcase_add_test(tc_core, test_cos_edge_below_one_dbl);
  tcase_add_test(tc_core, test_cos_edge_above_one_dbl);
  tcase_add_test(tc_core, test_cos_negative_below_one_dbl);
  tcase_add_test(tc_core, test_cos_negative_above_one_dbl);
  tcase_add_test(tc_core, test_cos_3pi_2);
  // tcase_add_test(tc_core, test_cos_negative_3pi_2);
  tcase_add_test(tc_core, test_cos_below_pi);
  tcase_add_test(tc_core, test_cos_negative_below_pi);
  tcase_add_test(tc_core, test_cos_above_pi);
  tcase_add_test(tc_core, test_cos_negative_above_pi);
  tcase_add_test(tc_core, test_cos_near_above_one);
  tcase_add_test(tc_core, test_cos_near_below_one);
  tcase_add_test(tc_core, test_cos_negative_near_above_one);
  tcase_add_test(tc_core, test_cos_negative_near_below_one);
  tcase_add_test(tc_core, test_cos_1000pi);
  tcase_add_test(tc_core, test_cos_negative_1000pi);

  suite_add_tcase(s, tc_core);
  return s;
}