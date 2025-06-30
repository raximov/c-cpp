#include "s21_test.h"

START_TEST(test_strncat_01) {
  char src[] =
      "This function appends not more than n characters from the string "
      "pointed to..";
  char dest[100] = "There is a destination string for checking!!!!";
  char dest_etalon[100] = "There is a destination string for checking!!!!";
  s21_size_t n = 10;
  char *result = (char *)s21_strncat(dest, src, n);
  char *result_etalon = (char *)strncat(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncat_02) {
  char src[] =
      "This function appends not more than n characters from the string "
      "pointed to..";
  char dest[100] = "There is a destination string for checking!!!!";
  char dest_etalon[100] = "There is a destination string for checking!!!!";
  s21_size_t n = 0;
  char *result = (char *)s21_strncat(dest, src, n);
  char *result_etalon = (char *)strncat(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncat_03) {
  char src[] =
      "This function appends not more than n characters from the string "
      "pointed to..";
  char dest[150] = "There is a destination string for checking!";
  char dest_etalon[150] = "There is a destination string for checking!";
  s21_size_t n = 100;
  char *result = (char *)s21_strncat(dest, src, n);
  char *result_etalon = (char *)strncat(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncat_04) {
  char src[] =
      "This function appends not \0 more than n characters \t from the string "
      "pointed to..";
  char dest[150] = "There is a destination string for checking!";
  char dest_etalon[150] = "There is a destination string for checking!";
  s21_size_t n = 100;
  char *result = (char *)s21_strncat(dest, src, n);
  char *result_etalon = (char *)strncat(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncat_05) {
  char src[] = "";
  char dest[150] = "There is a destination string for checking!";
  char dest_etalon[150] = "There is a destination string for checking!";
  s21_size_t n = 100;
  char *result = (char *)s21_strncat(dest, src, n);
  char *result_etalon = (char *)strncat(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncat_06) {
  char src[] = "";
  char dest[150] = "";
  char dest_etalon[150] = "";
  s21_size_t n = 10;
  char *result = (char *)s21_strncat(dest, src, n);
  char *result_etalon = (char *)strncat(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncat_07) {
  char src[] =
      "This function appends not \0 more than n characters \t from the string "
      "pointed to..";
  char dest[150] = "";
  char dest_etalon[150] = "";
  s21_size_t n = 100;
  char *result = (char *)s21_strncat(dest, src, n);
  char *result_etalon = (char *)strncat(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncat_08) {
  char src[] = "!@#$%$#&%&^*&()_12335467689UYFGIUYEGMNDCRERFaes4534545";
  char dest[250] = "There is a destination string for checking!";
  char dest_etalon[250] = "There is a destination string for checking!";
  s21_size_t n = 100;
  char *result = (char *)s21_strncat(dest, src, n);
  char *result_etalon = (char *)strncat(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncat_1) {
  char src[] =
      "This function appends not more than n characters from the string "
      "pointed to..";
  char dest[100] = "There is a destination string for checking!!!!";
  char dest_etalon[100] = "There is a destination string for checking!!!!";
  s21_size_t n = 10;
  char *result = (char *)s21_strncat(dest, src, n);
  char *result_etalon = (char *)strncat(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncat_2) {
  char src[] = "Hello";
  char dest[100] = "World";
  char dest_etalon[100] = "World";
  s21_size_t n = 3;
  char *result = (char *)s21_strncat(dest, src, n);
  char *result_etalon = (char *)strncat(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncat_3) {
  char src[] = "12345";
  char dest[100] = "67890";
  char dest_etalon[100] = "67890";
  s21_size_t n = 5;
  char *result = (char *)s21_strncat(dest, src, n);
  char *result_etalon = (char *)strncat(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncat_4) {
  char src[] = "abcdef";
  char dest[100] = "ghijkl";
  char dest_etalon[100] = "ghijkl";
  s21_size_t n = 0;
  char *result = (char *)s21_strncat(dest, src, n);
  char *result_etalon = (char *)strncat(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncat_5) {
  char src[] = "";
  char dest[100] = "Test";
  char dest_etalon[100] = "Test";
  s21_size_t n = 5;
  char *result = (char *)s21_strncat(dest, src, n);
  char *result_etalon = (char *)strncat(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncat_6) {
  char src[] = "abcdef";
  char dest[100] = "";
  char dest_etalon[100] = "";
  s21_size_t n = 3;
  char *result = (char *)s21_strncat(dest, src, n);
  char *result_etalon = (char *)strncat(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncat_7) {
  char src[] = "abcdef";
  char dest[100] = "ghijkl";
  char dest_etalon[100] = "ghijkl";
  s21_size_t n = 10;
  char *result = (char *)s21_strncat(dest, src, n);
  char *result_etalon = (char *)strncat(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncat_8) {
  char src[] = "abcdef";
  char dest[100] = "ghijkl";
  char dest_etalon[100] = "ghijkl";
  s21_size_t n = 20;
  char *result = (char *)s21_strncat(dest, src, n);
  char *result_etalon = (char *)strncat(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncat_9) {
  char src[] = "abcdef";
  char dest[100] = "ghijkl";
  char dest_etalon[100] = "ghijkl";
  s21_size_t n = 1;
  char *result = (char *)s21_strncat(dest, src, n);
  char *result_etalon = (char *)strncat(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_strncat_10) {
  char src[] = "abcdef";
  char dest[100] = "ghijkl";
  char dest_etalon[100] = "ghijkl";
  s21_size_t n = 6;
  char *result = (char *)s21_strncat(dest, src, n);
  char *result_etalon = (char *)strncat(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

Suite *test_strncat() {
  Suite *s = suite_create("s21_strncat");
  TCase *tc = tcase_create("s21_strncat");

  tcase_add_test(tc, test_strncat_01);
  tcase_add_test(tc, test_strncat_02);
  tcase_add_test(tc, test_strncat_03);
  tcase_add_test(tc, test_strncat_04);
  tcase_add_test(tc, test_strncat_05);
  tcase_add_test(tc, test_strncat_06);
  tcase_add_test(tc, test_strncat_07);
  tcase_add_test(tc, test_strncat_08);
  tcase_add_test(tc, test_strncat_1);
  tcase_add_test(tc, test_strncat_2);
  tcase_add_test(tc, test_strncat_3);
  tcase_add_test(tc, test_strncat_4);
  tcase_add_test(tc, test_strncat_5);
  tcase_add_test(tc, test_strncat_6);
  tcase_add_test(tc, test_strncat_7);
  tcase_add_test(tc, test_strncat_8);
  tcase_add_test(tc, test_strncat_9);
  tcase_add_test(tc, test_strncat_10);

  suite_add_tcase(s, tc);
  return s;
}