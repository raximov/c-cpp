#include "s21_test.h"

START_TEST(test_trim_1) {
  char *src = "  hello  ";
  char *str = " ";
  char *new = s21_trim(src, str);

  ck_assert_str_eq(new, "hello");
}
END_TEST

START_TEST(test_trim_2) {
  char *src = "***hello***";
  char *str = "*";
  char *new = s21_trim(src, str);

  ck_assert_str_eq(new, "hello");
}
END_TEST

START_TEST(test_trim_3) {
  char *src = "";
  char *str = " ";
  char *new = s21_trim(src, str);

  ck_assert_str_eq(new, "");
}
END_TEST

START_TEST(test_trim_4) {
  char *src = "*****";
  char *str = "*";
  char *new = s21_trim(src, str);

  ck_assert_str_eq(new, "");
}
END_TEST

START_TEST(test_trim_5) {
  char *src = "hello world";
  char *str = " ";
  char *new = s21_trim(src, str);

  ck_assert_str_eq(new, "hello world");
}
END_TEST

Suite *test_trim() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_trim");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_trim_1);
  tcase_add_test(tc_core, test_trim_2);
  tcase_add_test(tc_core, test_trim_3);
  tcase_add_test(tc_core, test_trim_4);
  tcase_add_test(tc_core, test_trim_5);
  suite_add_tcase(s, tc_core);

  return s;
}