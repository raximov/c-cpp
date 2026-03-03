#include "s21_math_tests.h"

START_TEST(EXP_TEST1) {
  long double actual = s21_exp(8);
  long double expected = exp(8);
  s21_test_case(actual, expected);
}
END_TEST

START_TEST(EXP_TEST2) {
  long double actual = s21_exp(-5);
  long double expected = exp(-5);
  s21_test_case(actual, expected);
}
END_TEST

START_TEST(EXP_TEST3) {
  long double actual = s21_exp(0);
  long double expected = exp(0);
  s21_test_case(actual, expected);
}
END_TEST

START_TEST(EXP_TEST4) {
  long double actual = s21_exp(INFINITY);
  long double expected = exp(INFINITY);
  s21_test_case(actual, expected);
}
END_TEST

START_TEST(EXP_TEST5) {
  long double actual = s21_exp(-INFINITY);
  long double expected = exp(-INFINITY);
  s21_test_case(actual, expected);
}
END_TEST

START_TEST(EXP_TEST_POSITIVE) {
  long double actual = s21_exp(1);
  long double expected = exp(1);
  s21_test_case(actual, expected);
}
END_TEST

START_TEST(EXP_TEST_NEGATIVE) {
  long double actual = s21_exp(-1);
  long double expected = exp(-1);
  s21_test_case(actual, expected);
}
END_TEST

START_TEST(EXP_TEST_ZERO) {
  long double actual = s21_exp(0);
  long double expected = exp(0);
  s21_test_case(actual, expected);
}
END_TEST

Suite *test_s21_exp(void) {
  Suite *s = suite_create("\033[42m-=S21_exp=-\033[0m");

  TCase *tc_core = tcase_create("EXP");

  tcase_add_test(tc_core, EXP_TEST1);
  tcase_add_test(tc_core, EXP_TEST2);
  tcase_add_test(tc_core, EXP_TEST3);
  tcase_add_test(tc_core, EXP_TEST4);
  tcase_add_test(tc_core, EXP_TEST5);
  tcase_add_test(tc_core, EXP_TEST_POSITIVE);
  tcase_add_test(tc_core, EXP_TEST_NEGATIVE);
  tcase_add_test(tc_core, EXP_TEST_ZERO);

  suite_add_tcase(s, tc_core);

  return s;
}