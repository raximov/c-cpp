#include "s21_test.h"

START_TEST(test_strlen_01) {
  char str[] = "I'm a string that's to be checked!";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_02) {
  char str[] = "I'm a string \0that's to be checked!";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_03) {
  char str[] = "\0";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_04) {
  char str[] = "\0\0\0\0\0";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_05) {
  char str[] = "abcdefghijklmnopqrstuvwxyz 0123456789 !@#$%^&*()_-+= ";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_06) {
  char str[] = "";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_1) {
  char str[] = "I'm a string that's to be checked!";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_2) {
  char str[] = "";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_3) {
  char str[] = "a";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_4) {
  char str[] = "abcdefghijklmnopqrstuvwxyz";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_5) {
  char str[] = "1234567890";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_6) {
  char str[] = " \t\n\r\v\f";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_7) {
  char str[] = "Hello, World!";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_8) {
  char str[] = "This is a test string.";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_9) {
  char str[] = "Special characters: !@#$%^&*()";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_10) {
  char str[] = "Mixed case: aBcDeFgHiJkLmNoPqRsTuVwXyZ";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_11) {
  char str[] = "Repeated characters: aaaaaaaa";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_12) {
  char str[] =
      "Long string with many words and characters to test the function.";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_13) {
  char str[] = "Edge case: single space ";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_14) {
  char str[] = "Edge case: multiple spaces   ";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_15) {
  char str[] = "Edge case: tab\tcharacter";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_16) {
  char str[] = "Edge case: newline\ncharacter";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_17) {
  char str[] = "Edge case: carriage return\rcharacter";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_18) {
  char str[] = "Edge case: vertical tab\vcharacter";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_19) {
  char str[] = "Edge case: form feed\fcharacter";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_20) {
  char str[] = "Edge case: backslash\\character";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_21) {
  char str[] = "Edge case: null character\0in the middle";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_22) {
  char str[] = "Edge case: null character at the end\0";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_23) {
  char str[] = "Edge case: null character at the beginning\0";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_24) {
  char str[] = "Edge case: null character in the middle\0with more characters";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strlen_25) {
  char str[] = "Edge case: null character at the end with more characters\0";
  size_t res = s21_strlen(str);
  size_t orig = strlen(str);
  ck_assert_uint_eq(res, orig);
}
END_TEST

Suite *test_strlen() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strlen");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strlen_01);
  tcase_add_test(tc_core, test_strlen_02);
  tcase_add_test(tc_core, test_strlen_03);
  tcase_add_test(tc_core, test_strlen_04);
  tcase_add_test(tc_core, test_strlen_05);
  tcase_add_test(tc_core, test_strlen_06);
  tcase_add_test(tc_core, test_strlen_1);
  tcase_add_test(tc_core, test_strlen_2);
  tcase_add_test(tc_core, test_strlen_3);
  tcase_add_test(tc_core, test_strlen_4);
  tcase_add_test(tc_core, test_strlen_5);
  tcase_add_test(tc_core, test_strlen_6);
  tcase_add_test(tc_core, test_strlen_7);
  tcase_add_test(tc_core, test_strlen_8);
  tcase_add_test(tc_core, test_strlen_9);
  tcase_add_test(tc_core, test_strlen_10);
  tcase_add_test(tc_core, test_strlen_11);
  tcase_add_test(tc_core, test_strlen_12);
  tcase_add_test(tc_core, test_strlen_13);
  tcase_add_test(tc_core, test_strlen_14);
  tcase_add_test(tc_core, test_strlen_15);
  tcase_add_test(tc_core, test_strlen_16);
  tcase_add_test(tc_core, test_strlen_17);
  tcase_add_test(tc_core, test_strlen_18);
  tcase_add_test(tc_core, test_strlen_19);
  tcase_add_test(tc_core, test_strlen_20);
  tcase_add_test(tc_core, test_strlen_21);
  tcase_add_test(tc_core, test_strlen_22);
  tcase_add_test(tc_core, test_strlen_23);
  tcase_add_test(tc_core, test_strlen_24);
  tcase_add_test(tc_core, test_strlen_25);

  suite_add_tcase(s, tc_core);

  return s;
}
