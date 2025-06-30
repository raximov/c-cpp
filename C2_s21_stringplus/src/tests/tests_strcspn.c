#include "s21_test.h"

START_TEST(test_strcspn_1) {
  char str1[] = "I'm a string that's to be checked!";
  char str2[] = " ";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_2) {
  char str1[] = "I'm a string that's to be checked!";
  char str2[] = "";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_3) {
  char str1[] = "";
  char str2[] = "";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_4) {
  char str1[] = "\0";
  char str2[] = "";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_5) {
  char str1[] = "";
  char str2[] = "\0";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_6) {
  char str1[] = "abcdef";
  char str2[] = "g";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_7) {
  char str1[] = "abcdef";
  char str2[] = "d";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_8) {
  char str1[] = "abcdef";
  char str2[] = "\0d";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_9) {
  char str1[] = "abc\0def";
  char str2[] = "d";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_10) {
  char str1[] = "abc\0def";
  char str2[] = "\0d";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_11) {
  char str1[] = "abc\0def";
  char str2[] = "d\0";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_12) {
  char str1[] = "\0abcdef";
  char str2[] = "d";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_13) {
  char str1[] = "\0abcdef";
  char str2[] = "g";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_14) {
  char str1[] = "\0abcdef";
  char str2[] = "";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_15) {
  char str1[] = "\0abcdef";
  char str2[] = "\0";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_16) {
  char str1[] = "abcd\0ef";
  char str2[] = "d\0";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_17) {
  char str1[] = "abcd\0ef";
  char str2[] = "\0d";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_01) {
  char str1[] = "I'm a string that's to be checked!";
  char str2[] = " ";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_02) {
  char str1[] = "Hello, World!";
  char str2[] = "o";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_03) {
  char str1[] = "1234567890";
  char str2[] = "5";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_04) {
  char str1[] = "abcdefghijklmnopqrstuvwxyz";
  char str2[] = "z";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_05) {
  char str1[] = "No match here";
  char str2[] = "x";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_06) {
  char str1[] = "";
  char str2[] = "a";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_07) {
  char str1[] = "a";
  char str2[] = "";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_08) {
  char str1[] = "";
  char str2[] = "";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_09) {
  char str1[] = "abcdefghijklmnopqrstuvwxyz";
  char str2[] = "abcdefghijklmnopqrstuvwxyz";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_010) {
  char str1[] = "abcdefghijklmnopqrstuvwxyz";
  char str2[] = "abcdefghijklmnopqrstuvwxyz";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_011) {
  char str1[] = "abcdefghijklmnopqrstuvwxyz";
  char str2[] = "abcdefghijklmnopqrstuvwxyz";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_012) {
  char str1[] = "abcdefghijklmnopqrstuvwxyz";
  char str2[] = "abcdefghijklmnopqrstuvwxyz";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_013) {
  char str1[] = "abcdefghijklmnopqrstuvwxyz";
  char str2[] = "abcdefghijklmnopqrstuvwxyz";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_014) {
  char str1[] = "abcdefghijklmnopqrstuvwxyz";
  char str2[] = "abcdefghijklmnopqrstuvwxyz";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_015) {
  char str1[] = "abcdefghijklmnopqrstuvwxyz";
  char str2[] = "abcdefghijklmnopqrstuvwxyz";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_016) {
  char str1[] = "abcdefghijklmnopqrstuvwxyz";
  char str2[] = "abcdefghijklmnopqrstuvwxyz";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_017) {
  char str1[] = "abcdefghijklmnopqrstuvwxyz";
  char str2[] = "abcdefghijklmnopqrstuvwxyz";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_018) {
  char str1[] = "abcdefghijklmnopqrstuvwxyz";
  char str2[] = "abcdefghijklmnopqrstuvwxyz";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_019) {
  char str1[] = "abcdefghijklmnopqrstuvwxyz";
  char str2[] = "abcdefghijklmnopqrstuvwxyz";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

START_TEST(test_strcspn_020) {
  char str1[] = "abcdefghijklmnopqrstuvwxyz";
  char str2[] = "abcdefghijklmnopqrstuvwxyz";
  s21_size_t res = s21_strcspn(str1, str2);
  size_t orig = strcspn(str1, str2);
  ck_assert_uint_eq(res, orig);
}
END_TEST

Suite *test_strcspn() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strcspn");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strcspn_1);
  tcase_add_test(tc_core, test_strcspn_2);
  tcase_add_test(tc_core, test_strcspn_3);
  tcase_add_test(tc_core, test_strcspn_4);
  tcase_add_test(tc_core, test_strcspn_5);
  tcase_add_test(tc_core, test_strcspn_6);
  tcase_add_test(tc_core, test_strcspn_7);
  tcase_add_test(tc_core, test_strcspn_8);
  tcase_add_test(tc_core, test_strcspn_9);
  tcase_add_test(tc_core, test_strcspn_10);
  tcase_add_test(tc_core, test_strcspn_11);
  tcase_add_test(tc_core, test_strcspn_12);
  tcase_add_test(tc_core, test_strcspn_13);
  tcase_add_test(tc_core, test_strcspn_14);
  tcase_add_test(tc_core, test_strcspn_15);
  tcase_add_test(tc_core, test_strcspn_16);
  tcase_add_test(tc_core, test_strcspn_17);
  tcase_add_test(tc_core, test_strcspn_01);
  tcase_add_test(tc_core, test_strcspn_02);
  tcase_add_test(tc_core, test_strcspn_03);
  tcase_add_test(tc_core, test_strcspn_04);
  tcase_add_test(tc_core, test_strcspn_05);
  tcase_add_test(tc_core, test_strcspn_06);
  tcase_add_test(tc_core, test_strcspn_07);
  tcase_add_test(tc_core, test_strcspn_08);
  tcase_add_test(tc_core, test_strcspn_09);
  tcase_add_test(tc_core, test_strcspn_010);
  tcase_add_test(tc_core, test_strcspn_011);
  tcase_add_test(tc_core, test_strcspn_012);
  tcase_add_test(tc_core, test_strcspn_013);
  tcase_add_test(tc_core, test_strcspn_014);
  tcase_add_test(tc_core, test_strcspn_015);
  tcase_add_test(tc_core, test_strcspn_016);
  tcase_add_test(tc_core, test_strcspn_017);
  tcase_add_test(tc_core, test_strcspn_018);
  tcase_add_test(tc_core, test_strcspn_019);
  tcase_add_test(tc_core, test_strcspn_020);

  suite_add_tcase(s, tc_core);

  return s;
}
