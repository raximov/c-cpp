#include "s21_test.h"

START_TEST(test_strstr_01) {
  char *res = s21_strstr("aaabbbccc", "aa");
  char *orig = strstr("aaabbbccc", "aa");

  ck_assert_str_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_02) {
  char *res = s21_strstr("aaabbbccc", "bb");
  char *orig = strstr("aaabbbccc", "bb");

  ck_assert_str_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_03) {
  char *res = s21_strstr("aaabbbccc", "cc");
  char *orig = strstr("aaabbbccc", "cc");

  ck_assert_str_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_04) {
  char *res = s21_strstr("aaabbbccc", "dd");
  char *orig = strstr("aaabbbccc", "dd");

  ck_assert_pstr_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_05) {
  char *res = s21_strstr("aaabbbccc", "");
  char *orig = strstr("aaabbbccc", "");

  ck_assert_pstr_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_06) {
  char *res = s21_strstr("aaabbbccc", "\0");
  char *orig = strstr("aaabbbccc", "\0");

  ck_assert_pstr_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_07) {
  char *res = s21_strstr("aaabcd", "abc");
  char *orig = strstr("aaabcd", "abc");

  ck_assert_str_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_08) {
  char *res = s21_strstr("aaabc", "abc");
  char *orig = strstr("aaabc", "abc");

  ck_assert_str_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_09) {
  char *res = s21_strstr("abc", "abcd");
  char *orig = strstr("abc", "abcd");

  ck_assert_pstr_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_010) {
  char *res = s21_strstr("aaabcad", "abcd");
  char *orig = strstr("aaabcad", "abcd");

  ck_assert_pstr_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_011) {
  char *res = s21_strstr("aaabaaabcdaaa", "abc");
  char *orig = strstr("aaabaaabcdaaa", "abc");

  ck_assert_pstr_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_012) {
  char *res = s21_strstr("", "abc");
  char *orig = strstr("", "abc");

  ck_assert_pstr_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_013) {
  char *res = s21_strstr("\0", "abc");
  char *orig = strstr("\0", "abc");

  ck_assert_pstr_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_014) {
  char *res = s21_strstr("aaa\0bbb", "aa");
  char *orig = strstr("aaa\0bbb", "aa");

  ck_assert_pstr_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_015) {
  char *res = s21_strstr("aaa\0bbb", "bb");
  char *orig = strstr("aaa\0bbb", "bb");

  ck_assert_pstr_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_016) {
  char *res = s21_strstr("aaabbb", "b\0");
  char *orig = strstr("aaabbb", "b\0");

  ck_assert_pstr_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_1) {
  char *res = s21_strstr("aaabbbccc", "aa");
  char *orig = strstr("aaabbbccc", "aa");

  ck_assert_str_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_2) {
  char *res = s21_strstr("aaabbbccc", "bbb");
  char *orig = strstr("aaabbbccc", "bbb");

  ck_assert_str_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_3) {
  char *res = s21_strstr("aaabbbccc", "ccc");
  char *orig = strstr("aaabbbccc", "ccc");

  ck_assert_str_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_4) {
  char *res = s21_strstr("aaabbbccc", "d");
  char *orig = strstr("aaabbbccc", "d");

  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_5) {
  char *res = s21_strstr("aaabbbccc", "");
  char *orig = strstr("aaabbbccc", "");

  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_6) {
  char *res = s21_strstr("", "aa");
  char *orig = strstr("", "aa");

  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_7) {
  char *res = s21_strstr("", "");
  char *orig = strstr("", "");

  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_8) {
  char *res = s21_strstr("aaabbbccc", "aaabbbccc");
  char *orig = strstr("aaabbbccc", "aaabbbccc");

  ck_assert_str_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_9) {
  char *res = s21_strstr("aaabbbccc", "aaabbbcccddd");
  char *orig = strstr("aaabbbccc", "aaabbbcccddd");

  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_10) {
  char *res = s21_strstr("aaabbbccc", "aaa");
  char *orig = strstr("aaabbbccc", "aaa");

  ck_assert_str_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_11) {
  char *res = s21_strstr("aaabbbccc", "bb");
  char *orig = strstr("aaabbbccc", "bb");

  ck_assert_str_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_12) {
  char *res = s21_strstr("aaabbbccc", "cc");
  char *orig = strstr("aaabbbccc", "cc");

  ck_assert_str_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_13) {
  char *res = s21_strstr("aaabbbccc", "aabbcc");
  char *orig = strstr("aaabbbccc", "aabbcc");

  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_14) {
  char *res = s21_strstr("aaabbbccc", "aaaabbbccc");
  char *orig = strstr("aaabbbccc", "aaaabbbccc");

  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_15) {
  char *res = s21_strstr("aaabbbccc", "aaabbbcc");
  char *orig = strstr("aaabbbccc", "aaabbbcc");

  ck_assert_str_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_16) {
  char *res = s21_strstr("aaabbbccc", "bbbccc");
  char *orig = strstr("aaabbbccc", "bbbccc");

  ck_assert_str_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_17) {
  char *res = s21_strstr("aaabbbccc", "ccc");
  char *orig = strstr("aaabbbccc", "ccc");

  ck_assert_str_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_18) {
  char *res = s21_strstr("aaabbbccc", "c");
  char *orig = strstr("aaabbbccc", "c");

  ck_assert_str_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_19) {
  char *res = s21_strstr("aaabbbccc", "b");
  char *orig = strstr("aaabbbccc", "b");

  ck_assert_str_eq(res, orig);
}
END_TEST

START_TEST(test_strstr_20) {
  char *res = s21_strstr("aaabbbccc", "a");
  char *orig = strstr("aaabbbccc", "a");

  ck_assert_str_eq(res, orig);
}
END_TEST

Suite *test_strstr() {
  Suite *s = suite_create("s21_strstr");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strstr_01);
  tcase_add_test(tc_core, test_strstr_02);
  tcase_add_test(tc_core, test_strstr_03);
  tcase_add_test(tc_core, test_strstr_04);
  tcase_add_test(tc_core, test_strstr_05);
  tcase_add_test(tc_core, test_strstr_06);
  tcase_add_test(tc_core, test_strstr_07);
  tcase_add_test(tc_core, test_strstr_08);
  tcase_add_test(tc_core, test_strstr_09);
  tcase_add_test(tc_core, test_strstr_010);
  tcase_add_test(tc_core, test_strstr_011);
  tcase_add_test(tc_core, test_strstr_012);
  tcase_add_test(tc_core, test_strstr_013);
  tcase_add_test(tc_core, test_strstr_014);
  tcase_add_test(tc_core, test_strstr_015);
  tcase_add_test(tc_core, test_strstr_016);
  tcase_add_test(tc_core, test_strstr_1);
  tcase_add_test(tc_core, test_strstr_2);
  tcase_add_test(tc_core, test_strstr_3);
  tcase_add_test(tc_core, test_strstr_4);
  tcase_add_test(tc_core, test_strstr_5);
  tcase_add_test(tc_core, test_strstr_6);
  tcase_add_test(tc_core, test_strstr_7);
  tcase_add_test(tc_core, test_strstr_8);
  tcase_add_test(tc_core, test_strstr_9);
  tcase_add_test(tc_core, test_strstr_10);
  tcase_add_test(tc_core, test_strstr_11);
  tcase_add_test(tc_core, test_strstr_12);
  tcase_add_test(tc_core, test_strstr_13);
  tcase_add_test(tc_core, test_strstr_14);
  tcase_add_test(tc_core, test_strstr_15);
  tcase_add_test(tc_core, test_strstr_16);
  tcase_add_test(tc_core, test_strstr_17);
  tcase_add_test(tc_core, test_strstr_18);
  tcase_add_test(tc_core, test_strstr_19);
  tcase_add_test(tc_core, test_strstr_20);

  suite_add_tcase(s, tc_core);

  return s;
}
