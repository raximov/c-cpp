#include "s21_test.h"

START_TEST(test_to_upper_1) {
  char str[] = "hello world";
  ck_assert_str_eq(s21_to_upper(str), "HELLO WORLD");
}
END_TEST

START_TEST(test_to_upper_2) {
  char str[] = "HELLO WORLD";
  ck_assert_str_eq(s21_to_upper(str), "HELLO WORLD");
}
END_TEST

START_TEST(test_to_upper_3) {
  char str[] = "HeLlO WoRlD";
  ck_assert_str_eq(s21_to_upper(str), "HELLO WORLD");
}
END_TEST

START_TEST(test_to_upper_4) {
  char str[] = "";
  ck_assert_str_eq(s21_to_upper(str), "");
}
END_TEST

START_TEST(test_to_upper_5) {
  char str[] = "1234567890";
  ck_assert_str_eq(s21_to_upper(str), "1234567890");
}
END_TEST

START_TEST(test_to_upper_6) {
  char str[] = "!@#$%^&*()";
  ck_assert_str_eq(s21_to_upper(str), "!@#$%^&*()");
}
END_TEST

START_TEST(test_to_upper_7) {
  char str[] = "   ";
  ck_assert_str_eq(s21_to_upper(str), "   ");
}
END_TEST

START_TEST(test_to_upper_8) {
  char str[] = "HeLlO123!@#$";
  ck_assert_str_eq(s21_to_upper(str), "HELLO123!@#$");
}
END_TEST

START_TEST(test_to_upper_9) {
  char str[] = "Héllo Wörld";
  ck_assert_str_eq(s21_to_upper(str), "HéLLO WöRLD");
}
END_TEST

START_TEST(test_to_upper_10) {
  char str[] = "Hello\nWorld\t!";
  ck_assert_str_eq(s21_to_upper(str), "HELLO\nWORLD\t!");
}
END_TEST

Suite *test_to_upper() {
  Suite *s = suite_create("s21_to_upper");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_to_upper_1);
  tcase_add_test(tc_core, test_to_upper_2);
  tcase_add_test(tc_core, test_to_upper_3);
  tcase_add_test(tc_core, test_to_upper_4);
  tcase_add_test(tc_core, test_to_upper_5);
  tcase_add_test(tc_core, test_to_upper_6);
  tcase_add_test(tc_core, test_to_upper_7);
  tcase_add_test(tc_core, test_to_upper_8);
  tcase_add_test(tc_core, test_to_upper_9);
  tcase_add_test(tc_core, test_to_upper_10);
  suite_add_tcase(s, tc_core);

  return s;
}
