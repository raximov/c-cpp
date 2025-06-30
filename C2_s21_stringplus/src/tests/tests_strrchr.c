#include "s21_test.h"

START_TEST(test_strrchr_01) {
  char* res = s21_strrchr("abcdef", 'a');
  char* orig = strrchr("abcdef", 'a');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_02) {
  char* res = s21_strrchr("", 'a');
  char* orig = strrchr("", 'a');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_03) {
  char* res = s21_strrchr("abcdef", '\0');
  char* orig = strrchr("abcdef", '\0');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_04) {
  char* res = s21_strrchr("", '\0');
  char* orig = strrchr("", '\0');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_05) {
  char* res = s21_strrchr("abcdef", 'x');
  char* orig = strrchr("abcdef", 'x');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_06) {
  char* res = s21_strrchr("\0", 'x');
  char* orig = strrchr("\0", 'x');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_07) {
  char* res = s21_strrchr("abcabc", 'a');
  char* orig = strrchr("abcabc", 'a');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_08) {
  char* res = s21_strrchr("abcabc", 'b');
  char* orig = strrchr("abcabc", 'b');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_09) {
  char* res = s21_strrchr("abcabc", 'c');
  char* orig = strrchr("abcabc", 'c');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_010) {
  char* res = s21_strrchr("abcabc", -1);
  char* orig = strrchr("abcabc", -1);
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_011) {
  char* res = s21_strrchr("\0\0\0", 'a');
  char* orig = strrchr("\0\0\0", 'a');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_012) {
  char* res = s21_strrchr("a\0\0\0", 'a');
  char* orig = strrchr("a\0\0\0", 'a');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_013) {
  char* res = s21_strrchr("\0a\0\0", 'a');
  char* orig = strrchr("\0a\0\0", 'a');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_014) {
  char* res = s21_strrchr("\0a\0\0", '\0');
  char* orig = strrchr("\0a\0\0", '\0');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_015) {
  char* res = s21_strrchr("a\0\0\0", '\0');
  char* orig = strrchr("a\0\0\0", '\0');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_016) {
  char* res = s21_strrchr("\0\0\0", -2);
  char* orig = strrchr("\0\0\0", -2);
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_017) {
  char* res = s21_strrchr("abc\0def", 'c');
  char* orig = strrchr("abc\0def", 'c');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_018) {
  char* res = s21_strrchr("abc\0def", 'd');
  char* orig = strrchr("abc\0def", 'd');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_1) {
  char* res = s21_strrchr("abcdef", 'a');
  char* orig = strrchr("abcdef", 'a');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_2) {
  char* res = s21_strrchr("abcdef", 'f');
  char* orig = strrchr("abcdef", 'f');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_3) {
  char* res = s21_strrchr("abcdef", 'z');
  char* orig = strrchr("abcdef", 'z');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_4) {
  char* res = s21_strrchr("aaaaa", 'a');
  char* orig = strrchr("aaaaa", 'a');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_5) {
  char* res = s21_strrchr("", 'a');
  char* orig = strrchr("", 'a');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_6) {
  char* res = s21_strrchr("abcdef", '\0');
  char* orig = strrchr("abcdef", '\0');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_7) {
  char* res = s21_strrchr("abcdef", ' ');
  char* orig = strrchr("abcdef", ' ');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_8) {
  char* res = s21_strrchr("a b c d e f", ' ');
  char* orig = strrchr("a b c d e f", ' ');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_9) {
  char* res = s21_strrchr("a b c d e f", 'b');
  char* orig = strrchr("a b c d e f", 'b');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_10) {
  char* res = s21_strrchr("a b c d e f", 'z');
  char* orig = strrchr("a b c d e f", 'z');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_11) {
  char* res = s21_strrchr("a b c d e f", '\0');
  char* orig = strrchr("a b c d e f", '\0');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_12) {
  char* res = s21_strrchr("a b c d e f", ' ');
  char* orig = strrchr("a b c d e f", ' ');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_13) {
  char* res = s21_strrchr("a b c d e f", 'a');
  char* orig = strrchr("a b c d e f", 'a');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_14) {
  char* res = s21_strrchr("a b c d e f", 'f');
  char* orig = strrchr("a b c d e f", 'f');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strrchr_15) {
  char* res = s21_strrchr("a b c d e f", 'e');
  char* orig = strrchr("a b c d e f", 'e');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

Suite* test_strrchr() {
  Suite* s;
  TCase* tc_core;

  s = suite_create("s21_strrchr");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strrchr_01);
  tcase_add_test(tc_core, test_strrchr_02);
  tcase_add_test(tc_core, test_strrchr_03);
  tcase_add_test(tc_core, test_strrchr_04);
  tcase_add_test(tc_core, test_strrchr_05);
  tcase_add_test(tc_core, test_strrchr_06);
  tcase_add_test(tc_core, test_strrchr_07);
  tcase_add_test(tc_core, test_strrchr_08);
  tcase_add_test(tc_core, test_strrchr_09);
  tcase_add_test(tc_core, test_strrchr_010);
  tcase_add_test(tc_core, test_strrchr_011);
  tcase_add_test(tc_core, test_strrchr_012);
  tcase_add_test(tc_core, test_strrchr_013);
  tcase_add_test(tc_core, test_strrchr_014);
  tcase_add_test(tc_core, test_strrchr_015);
  tcase_add_test(tc_core, test_strrchr_016);
  tcase_add_test(tc_core, test_strrchr_017);
  tcase_add_test(tc_core, test_strrchr_018);
  tcase_add_test(tc_core, test_strrchr_1);
  tcase_add_test(tc_core, test_strrchr_2);
  tcase_add_test(tc_core, test_strrchr_3);
  tcase_add_test(tc_core, test_strrchr_4);
  tcase_add_test(tc_core, test_strrchr_5);
  tcase_add_test(tc_core, test_strrchr_6);
  tcase_add_test(tc_core, test_strrchr_7);
  tcase_add_test(tc_core, test_strrchr_8);
  tcase_add_test(tc_core, test_strrchr_9);
  tcase_add_test(tc_core, test_strrchr_10);
  tcase_add_test(tc_core, test_strrchr_11);
  tcase_add_test(tc_core, test_strrchr_12);
  tcase_add_test(tc_core, test_strrchr_13);
  tcase_add_test(tc_core, test_strrchr_14);
  tcase_add_test(tc_core, test_strrchr_15);

  suite_add_tcase(s, tc_core);

  return s;
}
