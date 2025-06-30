#include "s21_test.h"

START_TEST(test_strpbrk_01) {
  char *result = s21_strpbrk("0123456789", "369");
  char *result_etalon = strpbrk("0123456789", "369");

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_02) {
  char *result = s21_strpbrk("0123456789", "654");
  char *result_etalon = strpbrk("0123456789", "654");

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_03) {
  char *result = s21_strpbrk("0123456789", "abc");
  const char *result_etalon = strpbrk("0123456789", "abc");

  ck_assert_pstr_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_04) {
  char *result = s21_strpbrk("", "abc");
  const char *result_etalon = strpbrk("", "abc");

  ck_assert_pstr_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_05) {
  char *result = s21_strpbrk("", "");
  const char *result_etalon = strpbrk("", "");

  ck_assert_pstr_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_06) {
  char *result = s21_strpbrk("\0", "");
  const char *result_etalon = strpbrk("\0", "");

  ck_assert_pstr_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_07) {
  char *result = s21_strpbrk("\0", "\0");
  const char *result_etalon = strpbrk("\0", "\0");

  ck_assert_pstr_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_08) {
  char *result = s21_strpbrk("\0\0", "\0");
  const char *result_etalon = strpbrk("\0\0", "\0");

  ck_assert_pstr_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_09) {
  char *result = s21_strpbrk("aaa", "\0");
  const char *result_etalon = strpbrk("aaa", "\0");

  ck_assert_pstr_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_010) {
  char *result = s21_strpbrk("aaa333", "a");
  char *result_etalon = strpbrk("aaa333", "a");

  ck_assert_pstr_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_011) {
  char *result = s21_strpbrk("aaa333", "3b");
  char *result_etalon = strpbrk("aaa333", "3b");

  ck_assert_pstr_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_012) {
  char *result = s21_strpbrk("aa\0a333", "3b");
  const char *result_etalon = strpbrk("aa\0a333", "3b");

  ck_assert_pstr_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_013) {
  char *result = s21_strpbrk("aaa\0333", "3b");
  char *result_etalon = strpbrk("aaa\0333", "3b");

  ck_assert_pstr_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_014) {
  char *result = s21_strpbrk("aaa3\033", "3b");
  char *result_etalon = strpbrk("aaa3\033", "3b");

  ck_assert_pstr_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_015) {
  char *result = s21_strpbrk("aaa33\03", "3b");
  char *result_etalon = strpbrk("aaa33\03", "3b");

  ck_assert_pstr_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_016) {
  char *result = s21_strpbrk("aaac33\03", "3b\0c");
  char *result_etalon = strpbrk("aaac33\03", "3b\0c");

  ck_assert_pstr_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_017) {
  char *result = s21_strpbrk("abc", "B");
  const char *result_etalon = strpbrk("abc", "B");

  ck_assert_pstr_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_018) {
  char *result = s21_strpbrk("ab\nc", "b");
  char *result_etalon = strpbrk("ab\nc", "b");

  ck_assert_pstr_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_019) {
  char *result = s21_strpbrk("ab\nc", "\n");
  char *result_etalon = strpbrk("ab\nc", "\n");

  ck_assert_pstr_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_1) {
  char *result = s21_strpbrk("0123456789", "369");
  char *result_etalon = strpbrk("0123456789", "369");

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_2) {
  char *result = s21_strpbrk("hello world", "w");
  char *result_etalon = strpbrk("hello world", "w");

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_7) {
  char *result =
      s21_strpbrk("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz");
  char *result_etalon =
      strpbrk("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz");

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_8) {
  char *result = s21_strpbrk("abcdefghijklmnopqrstuvwxyz", "z");
  char *result_etalon = strpbrk("abcdefghijklmnopqrstuvwxyz", "z");

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_9) {
  char *result = s21_strpbrk("abcdefghijklmnopqrstuvwxyz", "a");
  char *result_etalon = strpbrk("abcdefghijklmnopqrstuvwxyz", "a");

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_10) {
  char *result = s21_strpbrk("abcdefghijklmnopqrstuvwxyz", "m");
  char *result_etalon = strpbrk("abcdefghijklmnopqrstuvwxyz", "m");

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_11) {
  char *result = s21_strpbrk("abcdefghijklmnopqrstuvwxyz", "xyz");
  char *result_etalon = strpbrk("abcdefghijklmnopqrstuvwxyz", "xyz");

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_12) {
  char *result = s21_strpbrk("abcdefghijklmnopqrstuvwxyz", "abc");
  char *result_etalon = strpbrk("abcdefghijklmnopqrstuvwxyz", "abc");

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_13) {
  char *result = s21_strpbrk("abcdefghijklmnopqrstuvwxyz", "mno");
  char *result_etalon = strpbrk("abcdefghijklmnopqrstuvwxyz", "mno");

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_14) {
  char *result = s21_strpbrk("abcdefghijklmnopqrstuvwxyz", "xyzabc");
  char *result_etalon = strpbrk("abcdefghijklmnopqrstuvwxyz", "xyzabc");

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strpbrk_15) {
  char *result = s21_strpbrk("abcdefghijklmnopqrstuvwxyz", "abcxyz");
  char *result_etalon = strpbrk("abcdefghijklmnopqrstuvwxyz", "abcxyz");

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

Suite *test_strpbrk() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_strpbrk");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strpbrk_01);
  tcase_add_test(tc_core, test_strpbrk_02);
  tcase_add_test(tc_core, test_strpbrk_03);
  tcase_add_test(tc_core, test_strpbrk_04);
  tcase_add_test(tc_core, test_strpbrk_05);
  tcase_add_test(tc_core, test_strpbrk_06);
  tcase_add_test(tc_core, test_strpbrk_07);
  tcase_add_test(tc_core, test_strpbrk_08);
  tcase_add_test(tc_core, test_strpbrk_09);
  tcase_add_test(tc_core, test_strpbrk_010);
  tcase_add_test(tc_core, test_strpbrk_011);
  tcase_add_test(tc_core, test_strpbrk_012);
  tcase_add_test(tc_core, test_strpbrk_013);
  tcase_add_test(tc_core, test_strpbrk_014);
  tcase_add_test(tc_core, test_strpbrk_015);
  tcase_add_test(tc_core, test_strpbrk_016);
  tcase_add_test(tc_core, test_strpbrk_017);
  tcase_add_test(tc_core, test_strpbrk_018);
  tcase_add_test(tc_core, test_strpbrk_019);
  tcase_add_test(tc_core, test_strpbrk_1);
  tcase_add_test(tc_core, test_strpbrk_2);
  tcase_add_test(tc_core, test_strpbrk_7);
  tcase_add_test(tc_core, test_strpbrk_8);
  tcase_add_test(tc_core, test_strpbrk_9);
  tcase_add_test(tc_core, test_strpbrk_10);
  tcase_add_test(tc_core, test_strpbrk_11);
  tcase_add_test(tc_core, test_strpbrk_12);
  tcase_add_test(tc_core, test_strpbrk_13);
  tcase_add_test(tc_core, test_strpbrk_14);
  tcase_add_test(tc_core, test_strpbrk_15);

  suite_add_tcase(s, tc_core);

  return s;
}