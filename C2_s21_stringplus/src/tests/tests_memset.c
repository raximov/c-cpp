#include "s21_test.h"

START_TEST(test_memset_1) {
  char in[] = "abcdef";
  char *result = (char *)s21_memset(in, (int)'1', 2);
  char *result_etalon = (char *)memset(in, (int)'1', 2);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_memset_2) {
  char in[] = "abcdef";
  char *result = (char *)s21_memset(in, (int)'1', sizeof(in));
  char *result_etalon = (char *)memset(in, (int)'1', sizeof(in));

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_memset_3) {
  char in[] = "abcdef";
  for (size_t n = 1; n <= sizeof(in); n++) {
    char *result = (char *)s21_memset(in, (int)'1', n);
    char *result_etalon = (char *)memset(in, (int)'1', n);

    ck_assert_str_eq(result, result_etalon);
  }
}
END_TEST

START_TEST(test_memset_4) {
  char in[] = "abcdef";
  for (size_t n = 1; n <= sizeof(in); n++) {
    char *result = (char *)s21_memset(in, (int)'\0', n);
    char *result_etalon = (char *)memset(in, (int)'\0', n);

    ck_assert_str_eq(result, result_etalon);
  }
}
END_TEST

START_TEST(test_memset_5) {
  char in[] = "\0\0\0\0\0";
  for (size_t n = 1; n <= sizeof(in); n++) {
    char *result = (char *)s21_memset(in, (int)'a', n);
    char *result_etalon = (char *)memset(in, (int)'a', n);

    ck_assert_str_eq(result, result_etalon);
  }
}
END_TEST

START_TEST(test_memset_6) {
  char in[] = "abcdef";
  char *result = (char *)s21_memset(in, (int)'1', 2);
  char *result_etalon = (char *)memset(in, (int)'1', 2);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_memset_7) {
  char in[] = "abcdef";
  char *result = (char *)s21_memset(in, (int)'x', 4);
  char *result_etalon = (char *)memset(in, (int)'x', 4);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_memset_8) {
  char in[] = "abcdef";
  char *result = (char *)s21_memset(in, (int)'0', 6);
  char *result_etalon = (char *)memset(in, (int)'0', 6);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_memset_11) {
  char in[] = "abcdef";
  char *result = (char *)s21_memset(in, (int)' ', 3);
  char *result_etalon = (char *)memset(in, (int)' ', 3);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_memset_12) {
  char in[] = "abcdef";
  char *result = (char *)s21_memset(in, (int)'\0', 2);
  char *result_etalon = (char *)memset(in, (int)'\0', 2);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_memset_13) {
  char in[] = "abcdef";
  char *result = (char *)s21_memset(in, (int)'1', 7);
  char *result_etalon = (char *)memset(in, (int)'1', 7);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

Suite *test_memset() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_memset");
  tc_core = tcase_create("s21_memset");

  tcase_add_test(tc_core, test_memset_1);
  tcase_add_test(tc_core, test_memset_2);
  tcase_add_test(tc_core, test_memset_3);
  tcase_add_test(tc_core, test_memset_4);
  tcase_add_test(tc_core, test_memset_5);
  tcase_add_test(tc_core, test_memset_6);
  tcase_add_test(tc_core, test_memset_7);
  tcase_add_test(tc_core, test_memset_8);
  tcase_add_test(tc_core, test_memset_11);
  tcase_add_test(tc_core, test_memset_12);
  tcase_add_test(tc_core, test_memset_13);

  suite_add_tcase(s, tc_core);

  return s;
}