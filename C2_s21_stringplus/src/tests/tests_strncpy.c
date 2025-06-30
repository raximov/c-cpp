#include "s21_test.h"

START_TEST(test_strncpy_01) {
  char dest1[10] = "abcde";
  char dest2[10] = "abcde";
  char src[10] = "55555";
  char *result = s21_strncpy(dest1, src, 2);
  char *result_etalon = strncpy(dest2, src, 2);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncpy_03) {
  char dest1[10] = "abcde";
  char dest2[10] = "abcde";
  char src[10] = "55555";
  char *result = s21_strncpy(dest1, src, strlen(dest1));
  char *result_etalon = strncpy(dest2, src, strlen(dest2));

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncpy_04) {
  char dest1[10] = "abcde";
  char dest2[10] = "abcde";
  char src[10] = "55555";
  for (size_t n = 0; n <= strlen(dest1); n++) {
    char *result = s21_strncpy(dest2, src, n);
    char *result_etalon = strncpy(dest2, src, n);

    ck_assert_str_eq(result, result_etalon);
  }
}
END_TEST

START_TEST(test_strncpy_05) {
  char dest1[10] = "abcde";
  char dest2[10] = "abcde";
  char src[10] = "333";
  char *result = s21_strncpy(dest1, src, 2);
  char *result_etalon = strncpy(dest2, src, 2);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncpy_06) {
  char dest1[10] = "abcde";
  char dest2[10] = "abcde";
  char src[10] = "333";
  char *result = s21_strncpy(dest1, src, 5);
  char *result_etalon = strncpy(dest2, src, 5);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncpy_07) {
  char dest1[10] = "abcde";
  char dest2[10] = "abcde";
  char src[10] = "333";
  char *result = s21_strncpy(dest1, src, strlen(dest1));
  char *result_etalon = strncpy(dest2, src, strlen(dest2));

  ck_assert_str_eq(result, result_etalon);
}

START_TEST(test_strncpy_08) {
  char dest1[10] = "abc";
  char dest2[10] = "abc";
  char src[10] = "55555";
  char *result = s21_strncpy(dest1, src, 2);
  char *result_etalon = strncpy(dest2, src, 2);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncpy_010) {
  char dest1[10] = "";
  char dest2[10] = "";
  char src[10] = "55555";
  char *result = s21_strncpy(dest1, src, 10);
  char *result_etalon = strncpy(dest2, src, 10);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncpy_011) {
  char dest1[10] = "abc";
  char dest2[10] = "abc";
  char src[10] = "";
  char *result = s21_strncpy(dest1, src, 10);
  char *result_etalon = strncpy(dest2, src, 10);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncpy_012) {
  char dest1[10] = "";
  char dest2[10] = "";
  char src[10] = "";
  char *result = s21_strncpy(dest1, src, 10);
  char *result_etalon = strncpy(dest2, src, 10);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncpy_013) {
  char dest1[10] = "\0\0\0";
  char dest2[10] = "\0\0\0";
  char src[10] = "4444";
  char *result = s21_strncpy(dest1, src, 10);
  char *result_etalon = strncpy(dest2, src, 10);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncpy_014) {
  char dest1[10] = "\0\0\0";
  char dest2[10] = "\0\0\0";
  char src[10] = "4444";
  char *result = s21_strncpy(dest1, src, 2);
  char *result_etalon = strncpy(dest2, src, 2);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncpy_015) {
  char dest1[10] = "123";
  char dest2[10] = "123";
  char src[10] = "\0\0\0\0";
  char *result = s21_strncpy(dest1, src, 2);
  char *result_etalon = strncpy(dest2, src, 2);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncpy_016) {
  char dest1[10] = "123";
  char dest2[10] = "123";
  char src[10] = "\0\0\0\0";
  char *result = s21_strncpy(dest1, src, 5);
  char *result_etalon = strncpy(dest2, src, 5);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncpy_017) {
  char dest1[10] = "12\045";
  char dest2[10] = "12\045";
  char src[10] = "a\0b\0";

  for (int n = 0; n <= 10; n++) {
    char *result = s21_strncpy(dest1, src, n);
    char *result_etalon = strncpy(dest2, src, n);

    ck_assert_str_eq(result, result_etalon);
  }
}
END_TEST

START_TEST(test_strncpy_1) {
  char dest1[10] = "abcde";
  char dest2[10] = "abcde";
  char src[10] = "55555";
  char *result = s21_strncpy(dest1, src, strlen(dest1));
  char *result_etalon = strncpy(dest2, src, strlen(dest2));

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncpy_2) {
  char dest1[10] = "abcde";
  char dest2[10] = "abcde";
  char src[10] = "123";
  char *result = s21_strncpy(dest1, src, 3);
  char *result_etalon = strncpy(dest2, src, 3);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncpy_3) {
  char dest1[10] = "abcde";
  char dest2[10] = "abcde";
  char src[10] = "123456789";
  char *result = s21_strncpy(dest1, src, 10);
  char *result_etalon = strncpy(dest2, src, 10);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncpy_4) {
  char dest1[10] = "abcde";
  char dest2[10] = "abcde";
  char src[10] = "123456789";
  char *result = s21_strncpy(dest1, src, 5);
  char *result_etalon = strncpy(dest2, src, 5);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncpy_5) {
  char dest1[10] = "abcde";
  char dest2[10] = "abcde";
  char src[10] = "";
  char *result = s21_strncpy(dest1, src, 5);
  char *result_etalon = strncpy(dest2, src, 5);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncpy_8) {
  char dest1[10] = "abcde";
  char dest2[10] = "abcde";
  char src[10] = "123456789";
  char *result = s21_strncpy(dest1, src, 9);
  char *result_etalon = strncpy(dest2, src, 9);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncpy_9) {
  char dest1[10] = "abcde";
  char dest2[10] = "abcde";
  char src[10] = "123456789";
  char *result = s21_strncpy(dest1, src, 10);
  char *result_etalon = strncpy(dest2, src, 10);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncpy_10) {
  char dest1[10] = "abcde";
  char dest2[10] = "abcde";
  char src[10] = "123456789";
  char *result = s21_strncpy(dest1, src, 11);
  char *result_etalon = strncpy(dest2, src, 11);

  ck_assert_str_eq(result, result_etalon);
}
END_TEST

Suite *test_strncpy() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strncpy");
  tc_core = tcase_create("s21_strncpy");

  tcase_add_test(tc_core, test_strncpy_01);
  tcase_add_test(tc_core, test_strncpy_03);
  tcase_add_test(tc_core, test_strncpy_04);
  tcase_add_test(tc_core, test_strncpy_05);
  tcase_add_test(tc_core, test_strncpy_06);
  tcase_add_test(tc_core, test_strncpy_07);
  tcase_add_test(tc_core, test_strncpy_08);
  tcase_add_test(tc_core, test_strncpy_010);
  tcase_add_test(tc_core, test_strncpy_011);
  tcase_add_test(tc_core, test_strncpy_012);
  tcase_add_test(tc_core, test_strncpy_013);
  tcase_add_test(tc_core, test_strncpy_014);
  tcase_add_test(tc_core, test_strncpy_015);
  tcase_add_test(tc_core, test_strncpy_016);
  tcase_add_test(tc_core, test_strncpy_017);
  tcase_add_test(tc_core, test_strncpy_1);
  tcase_add_test(tc_core, test_strncpy_2);
  tcase_add_test(tc_core, test_strncpy_3);
  tcase_add_test(tc_core, test_strncpy_4);
  tcase_add_test(tc_core, test_strncpy_5);
  tcase_add_test(tc_core, test_strncpy_8);
  tcase_add_test(tc_core, test_strncpy_9);
  tcase_add_test(tc_core, test_strncpy_10);

  suite_add_tcase(s, tc_core);

  return s;
}
