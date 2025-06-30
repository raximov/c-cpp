#include "s21_test.h"

START_TEST(test_strncmp_1) {
  char str1[] = "I'm a string that's to be checked!";
  char str2[] = "I'm a string that's to be checked!";
  size_t n = 10;
  int res = s21_strncmp(str1, str2, n);
  int orig = strncmp(str1, str2, n);
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(test_strncmp_2) {
  char str1[] = "I'm a string that's to be checked!";
  char str2[] = "I'm a string that's to be checked!";
  size_t n = 35;
  int res = s21_strncmp(str1, str2, n);
  int orig = strncmp(str1, str2, n);
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(test_strncmp_3) {
  char str1[] = "I'm a string that's to be checked!";
  char str2[] = "I'm a different string.";
  size_t n = 10;
  int res = s21_strncmp(str1, str2, n);
  int orig = strncmp(str1, str2, n);
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(test_strncmp_4) {
  char str2[] = "I'm a different string.";
  char str1[] = "I'm a string that's to be checked!";
  size_t n = 35;
  int res = s21_strncmp(str1, str2, n);
  int orig = strncmp(str1, str2, n);
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(test_strncmp_5) {
  char str1[] = "";
  char str2[] = "";
  size_t n = 1;
  int res = s21_strncmp(str1, str2, n);
  int orig = strncmp(str1, str2, n);
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(test_strncmp_6) {
  char str1[] = "I'm a string that's to be checked!";
  char str2[] = "I'm a string \0that's to be checked!";
  size_t n = 20;
  int res = s21_strncmp(str1, str2, n);
  int orig = strncmp(str1, str2, n);
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(test_strncmp_7) {
  char str1[] = "I'm a \0string that's to be checked!";
  char str2[] = "I'm a \0different string.";
  size_t n = 20;
  int res = s21_strncmp(str1, str2, n);
  int orig = strncmp(str1, str2, n);
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(test_strncmp_8) {
  char str1[] = "I'm a string that's to be checked!";
  char str2[] = "I'm a string that's to be checked!";
  size_t n = 0;
  int res = s21_strncmp(str1, str2, n);
  int orig = strncmp(str1, str2, n);
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(test_strncmp_9) {
  char str1[] = "I'm a string that's to be checked!";
  char str2[] = "I'm a different string.";
  size_t n = 0;
  int res = s21_strncmp(str1, str2, n);
  int orig = strncmp(str1, str2, n);
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(test_strncmp_10) {
  char str1[] = "";
  char str2[] = "";
  size_t n = 0;
  int res = s21_strncmp(str1, str2, n);
  int orig = strncmp(str1, str2, n);
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(test_strncmp_100) {
  char str1[] = "I'm a string that's to be checked!";
  char str2[] = "I'm a string that's to be checked!";
  size_t n = 10;
  int res = s21_strncmp(str1, str2, n);
  int orig = strncmp(str1, str2, n);
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(test_strncmp_101) {
  char str1[] = "I'm a string that's to be checked!";
  char str2[] = "I'm a different string!";
  size_t n = 10;
  int res = s21_strncmp(str1, str2, n);
  int orig = strncmp(str1, str2, n);
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(test_strncmp_102) {
  char str1[] = "I'm a string that's to be checked!";
  char str2[] = "I'm a string that's to be checked!";
  size_t n = 0;
  int res = s21_strncmp(str1, str2, n);
  int orig = strncmp(str1, str2, n);
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(test_strncmp_103) {
  char str1[] = "I'm a string that's to be checked!";
  char str2[] = "I'm a string that's to be checked!";
  size_t n = 35;
  int res = s21_strncmp(str1, str2, n);
  int orig = strncmp(str1, str2, n);
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(test_strncmp_104) {
  char str1[] = "I'm a string that's to be checked!";
  char str2[] = "I'm a different string!";
  size_t n = 35;
  int res = s21_strncmp(str1, str2, n);
  int orig = strncmp(str1, str2, n);
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(test_strncmp_105) {
  char str1[] = "";
  char str2[] = "";
  size_t n = 10;
  int res = s21_strncmp(str1, str2, n);
  int orig = strncmp(str1, str2, n);
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(test_strncmp_106) {
  char str1[] = "a";
  char str2[] = "b";
  size_t n = 1;
  int res = s21_strncmp(str1, str2, n);
  int orig = strncmp(str1, str2, n);
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(test_strncmp_107) {
  char str1[] = "a";
  char str2[] = "a";
  size_t n = 1;
  int res = s21_strncmp(str1, str2, n);
  int orig = strncmp(str1, str2, n);
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(test_strncmp_108) {
  char str1[] = "abcdef";
  char str2[] = "abcxyz";
  size_t n = 3;
  int res = s21_strncmp(str1, str2, n);
  int orig = strncmp(str1, str2, n);
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(test_strncmp_109) {
  char str1[] = "abcdef";
  char str2[] = "abcxyz";
  size_t n = 4;
  int res = s21_strncmp(str1, str2, n);
  int orig = strncmp(str1, str2, n);
  ck_assert_int_eq(res, orig);
}
END_TEST

Suite *test_strncmp() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strncmp");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strncmp_1);
  tcase_add_test(tc_core, test_strncmp_2);
  tcase_add_test(tc_core, test_strncmp_3);
  tcase_add_test(tc_core, test_strncmp_4);
  tcase_add_test(tc_core, test_strncmp_5);
  tcase_add_test(tc_core, test_strncmp_6);
  tcase_add_test(tc_core, test_strncmp_7);
  tcase_add_test(tc_core, test_strncmp_8);
  tcase_add_test(tc_core, test_strncmp_9);
  tcase_add_test(tc_core, test_strncmp_10);
  tcase_add_test(tc_core, test_strncmp_100);
  tcase_add_test(tc_core, test_strncmp_101);
  tcase_add_test(tc_core, test_strncmp_102);
  tcase_add_test(tc_core, test_strncmp_103);
  tcase_add_test(tc_core, test_strncmp_104);
  tcase_add_test(tc_core, test_strncmp_105);
  tcase_add_test(tc_core, test_strncmp_106);
  tcase_add_test(tc_core, test_strncmp_107);
  tcase_add_test(tc_core, test_strncmp_108);
  tcase_add_test(tc_core, test_strncmp_109);

  suite_add_tcase(s, tc_core);

  return s;
}
