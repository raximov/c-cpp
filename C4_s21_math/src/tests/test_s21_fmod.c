#include "s21_math_tests.h"

START_TEST(FMOD_TEST1) {
  double actual = s21_fmod(4, 0);
  double expected = fmod(4, 0);
  s21_test_case(actual, expected);
}
END_TEST

START_TEST(FMOD_TEST2) {
  double actual = s21_fmod(3, 2);
  double expected = fmod(3, 2);
  s21_test_case(actual, expected);
}
END_TEST

START_TEST(FMOD_TEST3) {
  double actual = s21_fmod(4, 2);
  double expected = fmod(4, 2);
  s21_test_case(actual, expected);
}
END_TEST

START_TEST(FMOD_TEST4) {
  double actual = s21_fmod(1.5, 5);
  double expected = fmod(1.5, 5);
  s21_test_case(actual, expected);
}
END_TEST

START_TEST(FMOD_TEST5) {
  double actual = s21_fmod(3.005, 0.5);
  double expected = fmod(3.005, 0.5);
  s21_test_case(actual, expected);
}
END_TEST

Suite *test_s21_fmod(void) {
  TCase *tc_core;

  Suite *s = suite_create("\033[42m-=S21_fmod=-\033[0m");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, FMOD_TEST1);
  tcase_add_test(tc_core, FMOD_TEST2);
  tcase_add_test(tc_core, FMOD_TEST3);
  tcase_add_test(tc_core, FMOD_TEST4);
  tcase_add_test(tc_core, FMOD_TEST5);
  suite_add_tcase(s, tc_core);

  return s;
}