#include <limits.h>
#include <stdlib.h>
#include <time.h>

#include "s21_math_tests.h"

START_TEST(test_s21_abs_zero) {
  int x = 0;
  ck_assert_int_eq(s21_abs(x), abs(x));
}
END_TEST

START_TEST(test_s21_abs_one) {
  int x = 1;
  ck_assert_int_eq(s21_abs(x), abs(x));
}
END_TEST

START_TEST(test_s21_abs_two) {
  int x = 2;
  ck_assert_int_eq(s21_abs(x), abs(x));
}
END_TEST

START_TEST(test_s21_abs_max) {
  int x = INT_MAX;
  ck_assert_int_eq(s21_abs(x), abs(x));
}
END_TEST

START_TEST(test_s21_abs_almost_max) {
  int x = INT_MAX - 1;
  ck_assert_int_eq(s21_abs(x), abs(x));
}
END_TEST

START_TEST(test_s21_abs_mid) {
  int x = INT_MAX / 2;
  ck_assert_int_eq(s21_abs(x), abs(x));
}
END_TEST

START_TEST(test_s21_abs_range) {
  srand(time(NULL));
  const int num_tests = 1000;
  for (int i = 0; i < num_tests; i++) {
    int x = rand();
    ck_assert_int_eq(s21_abs(x), abs(x));
  }
}
END_TEST

START_TEST(test_s21_abs_minus_one) {
  int x = -1;
  ck_assert_int_eq(s21_abs(x), abs(x));
}
END_TEST

START_TEST(test_s21_abs_minus_two) {
  int x = -2;
  ck_assert_int_eq(s21_abs(x), abs(x));
}
END_TEST

START_TEST(test_s21_abs_minus_max) {
  int x = -INT_MAX;
  ck_assert_int_eq(s21_abs(x), abs(x));
}
END_TEST

START_TEST(test_s21_abs_almost_minus_max) {
  int x = -INT_MAX + 1;
  ck_assert_int_eq(s21_abs(x), abs(x));
}
END_TEST

START_TEST(test_s21_abs_minus_mid) {
  int x = -INT_MAX / 2;
  ck_assert_int_eq(s21_abs(x), abs(x));
}
END_TEST

START_TEST(test_s21_abs_minus_range) {
  srand(time(NULL));
  const int num_tests = 1000;
  for (int i = 0; i < num_tests; i++) {
    int x = -rand();
    ck_assert_int_eq(s21_abs(x), abs(x));
  }
}
END_TEST

Suite *test_s21_abs(void) {
  Suite *s = suite_create("\033[42m-=S21_abs=-\033[0m");
  TCase *tc = tcase_create("s21_abs_tc");

  tcase_add_test(tc, test_s21_abs_zero);
  tcase_add_test(tc, test_s21_abs_one);
  tcase_add_test(tc, test_s21_abs_two);
  tcase_add_test(tc, test_s21_abs_max);
  tcase_add_test(tc, test_s21_abs_almost_max);
  tcase_add_test(tc, test_s21_abs_mid);
  tcase_add_test(tc, test_s21_abs_range);
  tcase_add_test(tc, test_s21_abs_minus_one);
  tcase_add_test(tc, test_s21_abs_minus_two);
  tcase_add_test(tc, test_s21_abs_minus_max);
  tcase_add_test(tc, test_s21_abs_almost_minus_max);
  tcase_add_test(tc, test_s21_abs_minus_mid);
  tcase_add_test(tc, test_s21_abs_minus_range);

  suite_add_tcase(s, tc);
  return s;
}
