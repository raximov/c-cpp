#include "s21_test.h"

START_TEST(test_to_lower_1) {
  char str[] = "HELLO WORLD";
  ck_assert_str_eq(s21_to_lower(str), "hello world");
}
END_TEST

START_TEST(test_to_lower_2) {
  char str[] = "hello world";
  ck_assert_str_eq(s21_to_lower(str), "hello world");
}
END_TEST

START_TEST(test_to_lower_3) {
  char str[] = "HeLlO WoRlD";
  ck_assert_str_eq(s21_to_lower(str), "hello world");
}
END_TEST

START_TEST(test_to_lower_4) {
  char str[] = "";
  ck_assert_str_eq(s21_to_lower(str), "");
}
END_TEST

START_TEST(test_to_lower_5) {
  char str[] = "1234567890";
  ck_assert_str_eq(s21_to_lower(str), "1234567890");
}
END_TEST

START_TEST(test_to_lower_6) {
  char str[] = "!@#$%^&*()";
  ck_assert_str_eq(s21_to_lower(str), "!@#$%^&*()");
}
END_TEST

START_TEST(test_to_lower_7) {
  char str[] = "   ";
  ck_assert_str_eq(s21_to_lower(str), "   ");
}
END_TEST

START_TEST(test_to_lower_8) {
  char str[] = "HeLlO123!@#$";
  ck_assert_str_eq(s21_to_lower(str), "hello123!@#$");
}
END_TEST

START_TEST(test_to_lower_9) {
  char str[] = "Héllo Wörld";
  ck_assert_str_eq(s21_to_lower(str), "héllo wörld");
}
END_TEST

START_TEST(test_to_lower_10) {
  char str[] = "Hello\nWorld\t!";
  ck_assert_str_eq(s21_to_lower(str), "hello\nworld\t!");
}
END_TEST

Suite *test_to_lower() {
  Suite *s = suite_create("s21_to_lower");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_to_lower_1);
  tcase_add_test(tc_core, test_to_lower_2);
  tcase_add_test(tc_core, test_to_lower_3);
  tcase_add_test(tc_core, test_to_lower_4);
  tcase_add_test(tc_core, test_to_lower_5);
  tcase_add_test(tc_core, test_to_lower_6);
  tcase_add_test(tc_core, test_to_lower_7);
  tcase_add_test(tc_core, test_to_lower_8);
  tcase_add_test(tc_core, test_to_lower_9);
  tcase_add_test(tc_core, test_to_lower_10);
  suite_add_tcase(s, tc_core);

  return s;
}
