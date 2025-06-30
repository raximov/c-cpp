#include "s21_test.h"

START_TEST(test_strchr_1) {
  char* res = s21_strchr("abcdef", 'a');
  char* orig = strchr("abcdef", 'a');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_2) {
  char* res = s21_strchr("", 'a');
  char* orig = strchr("", 'a');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_3) {
  char* res = s21_strchr("abcdef", '\0');
  char* orig = strchr("abcdef", '\0');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_4) {
  char* res = s21_strchr("", '\0');
  char* orig = strchr("", '\0');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_5) {
  char* res = s21_strchr("abcdef", 'x');
  char* orig = strchr("abcdef", 'x');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_6) {
  char* res = s21_strchr("\0", 'x');
  char* orig = strchr("\0", 'x');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_7) {
  char* res = s21_strchr("abcabc", 'a');
  char* orig = strchr("abcabc", 'a');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_8) {
  char* res = s21_strchr("abcabc", 'b');
  char* orig = strchr("abcabc", 'b');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_9) {
  char* res = s21_strchr("abcabc", 'c');
  char* orig = strchr("abcabc", 'c');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_10) {
  char* res = s21_strchr("abcabc", -1);
  char* orig = strchr("abcabc", -1);
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_11) {
  char* res = s21_strchr("\0\0\0", 'a');
  char* orig = strchr("\0\0\0", 'a');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_12) {
  char* res = s21_strchr("a\0\0\0", 'a');
  char* orig = strchr("a\0\0\0", 'a');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_13) {
  char* res = s21_strchr("\0a\0\0", 'a');
  char* orig = strchr("\0a\0\0", 'a');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_14) {
  char* res = s21_strchr("\0a\0\0", '\0');
  char* orig = strchr("\0a\0\0", '\0');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_15) {
  char* res = s21_strchr("a\0\0\0", '\0');
  char* orig = strchr("a\0\0\0", '\0');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_16) {
  char* res = s21_strchr("\0\0\0", -2);
  char* orig = strchr("\0\0\0", -2);
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_c) {
  char* res = s21_strchr("abc", 'c');
  char* orig = strchr("abc", 'c');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_d) {
  char* res = s21_strchr("123", '2');
  char* orig = strchr("123", '2');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_f) {
  char* res = s21_strchr("123.456", '.');
  char* orig = strchr("123.456", '.');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_s) {
  char* res = s21_strchr("hello world", ' ');
  char* orig = strchr("hello world", ' ');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_u) {
  char* res = s21_strchr("123", '2');
  char* orig = strchr("123", '2');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_percent) {
  char* res = s21_strchr("%", '%');
  char* orig = strchr("%", '%');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_g) {
  char* res = s21_strchr("123.456g", 'g');
  char* orig = strchr("123.456g", 'g');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_G) {
  char* res = s21_strchr("123.456G", 'G');
  char* orig = strchr("123.456G", 'G');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_e) {
  char* res = s21_strchr("123.456e10", 'e');
  char* orig = strchr("123.456e10", 'e');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_E) {
  char* res = s21_strchr("123.456E10", 'E');
  char* orig = strchr("123.456E10", 'E');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_x) {
  char* res = s21_strchr("1a2b3c", 'a');
  char* orig = strchr("1a2b3c", 'a');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_X) {
  char* res = s21_strchr("1A2B3C", 'A');
  char* orig = strchr("1A2B3C", 'A');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_o) {
  char* res = s21_strchr("12345670", '0');
  char* orig = strchr("12345670", '0');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_p) {
  char* res = s21_strchr("pointer", 'p');
  char* orig = strchr("pointer", 'p');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_empty_string) {
  char* res = s21_strchr("", '\0');
  char* orig = strchr("", '\0');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_null_char) {
  char* res = s21_strchr("abc", '\0');
  char* orig = strchr("abc", '\0');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_not_found) {
  char* res = s21_strchr("abc", 'z');
  char* orig = strchr("abc", 'z');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

START_TEST(test_strchr_multiple_occurrences) {
  char* res = s21_strchr("ababab", 'b');
  char* orig = strchr("ababab", 'b');
  ck_assert_ptr_eq(res, orig);
}
END_TEST

Suite* test_strchr() {
  Suite* s;
  TCase* tc_core;

  s = suite_create("s21_strchr");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strchr_1);
  tcase_add_test(tc_core, test_strchr_2);
  tcase_add_test(tc_core, test_strchr_3);
  tcase_add_test(tc_core, test_strchr_4);
  tcase_add_test(tc_core, test_strchr_5);
  tcase_add_test(tc_core, test_strchr_6);
  tcase_add_test(tc_core, test_strchr_7);
  tcase_add_test(tc_core, test_strchr_8);
  tcase_add_test(tc_core, test_strchr_9);
  tcase_add_test(tc_core, test_strchr_10);
  tcase_add_test(tc_core, test_strchr_11);
  tcase_add_test(tc_core, test_strchr_12);
  tcase_add_test(tc_core, test_strchr_13);
  tcase_add_test(tc_core, test_strchr_14);
  tcase_add_test(tc_core, test_strchr_15);
  tcase_add_test(tc_core, test_strchr_16);
  tcase_add_test(tc_core, test_strchr_c);
  tcase_add_test(tc_core, test_strchr_d);
  tcase_add_test(tc_core, test_strchr_f);
  tcase_add_test(tc_core, test_strchr_s);
  tcase_add_test(tc_core, test_strchr_u);
  tcase_add_test(tc_core, test_strchr_percent);
  tcase_add_test(tc_core, test_strchr_g);
  tcase_add_test(tc_core, test_strchr_G);
  tcase_add_test(tc_core, test_strchr_e);
  tcase_add_test(tc_core, test_strchr_E);
  tcase_add_test(tc_core, test_strchr_x);
  tcase_add_test(tc_core, test_strchr_X);
  tcase_add_test(tc_core, test_strchr_o);
  tcase_add_test(tc_core, test_strchr_p);
  tcase_add_test(tc_core, test_strchr_empty_string);
  tcase_add_test(tc_core, test_strchr_null_char);
  tcase_add_test(tc_core, test_strchr_not_found);
  tcase_add_test(tc_core, test_strchr_multiple_occurrences);

  suite_add_tcase(s, tc_core);

  return s;
}
