#include "s21_math_tests.h"

START_TEST(pow_zero) {
  double base = 0;
  double exp = 0;
  ck_assert_ldouble_eq(pow(base, exp), s21_pow(base, exp));
}
END_TEST

START_TEST(pow_base_minus) {
  double base = -2;
  double exp = 0.3;
  ck_assert_ldouble_nan(pow(base, exp));
  ck_assert_ldouble_nan(s21_pow(base, exp));
}
END_TEST

START_TEST(pow_base_zero) {
  double base = 0;
  double exp = -123;
  ck_assert_ldouble_infinite(pow(base, exp));
  ck_assert_ldouble_infinite(s21_pow(base, exp));
}
END_TEST

START_TEST(pow_base_nan) {
  double base = S21_NAN;
  double exp = -123;
  ck_assert_ldouble_nan(pow(base, exp));
  ck_assert_ldouble_nan(s21_pow(base, exp));
}
END_TEST

START_TEST(pow_exp_nan) {
  double base = 12;
  double exp = S21_NAN;
  ck_assert_ldouble_nan(pow(base, exp));
  ck_assert_ldouble_nan(s21_pow(base, exp));
}
END_TEST

START_TEST(pow_base_inf) {
  double base = S21_INFINITY;
  double exp = 20000;
  ck_assert_ldouble_infinite(pow(base, exp));
  ck_assert_ldouble_infinite(s21_pow(base, exp));
}
END_TEST

START_TEST(pow_exp_inf) {
  double base = 12;
  double exp = -S21_INFINITY;
  ck_assert_ldouble_eq(pow(base, exp), s21_pow(base, exp));
}
END_TEST

START_TEST(pow_int_exp) {
  double base = 12;
  int exp = 10;
  ck_assert_ldouble_eq_tol(pow(base, exp), s21_pow(base, exp), 1e-6);
}
END_TEST

START_TEST(pow_int_base) {
  double base = 12;
  double exp = 1.1;
  ck_assert_ldouble_eq_tol(pow(base, exp), s21_pow(base, exp), 1e-6);
}
END_TEST

START_TEST(pow_exp_dbl_max) {
  double base = 0.9;
  double exp = DBL_MAX - 1;
  ck_assert_ldouble_eq_tol(pow(base, exp), s21_pow(base, exp), 1e-6);
}
END_TEST

START_TEST(pow_double_all) {
  double base = 25.25;
  double exp = 0.5;
  ck_assert_ldouble_eq_tol(pow(base, exp), s21_pow(base, exp), 1e-6);
}
END_TEST

START_TEST(pow_inf_minus) {
  double base = -S21_INFINITY;
  double exp = -4;
  ck_assert_ldouble_eq_tol(pow(base, exp), s21_pow(base, exp), 1e-6);
}
END_TEST

Suite *test_s21_pow(void) {
  Suite *s = suite_create("\033[42m-=S21_pow=-\033[0m");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, pow_zero);
  tcase_add_test(tc_core, pow_base_minus);
  tcase_add_test(tc_core, pow_base_zero);
  tcase_add_test(tc_core, pow_base_nan);
  tcase_add_test(tc_core, pow_exp_nan);
  tcase_add_test(tc_core, pow_base_inf);
  tcase_add_test(tc_core, pow_exp_inf);
  tcase_add_test(tc_core, pow_int_exp);
  tcase_add_test(tc_core, pow_int_base);
  tcase_add_test(tc_core, pow_exp_dbl_max);
  tcase_add_test(tc_core, pow_double_all);
  tcase_add_test(tc_core, pow_inf_minus);

  suite_add_tcase(s, tc_core);
  return s;
}