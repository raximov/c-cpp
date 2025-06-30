#include "s21_test.h"

START_TEST(test_memcmp_1) {
  char str1[] = "Hello world";
  char str2[] = "Hello world";
  s21_size_t n1 = 10;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_2) {
  char str1[] = "Hello world";
  char str2[] = "Hello World";
  s21_size_t n1 = 10;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_3) {
  char str1[] = "Hello world";
  char str2[] = "Hello";
  s21_size_t n1 = 5;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_4) {
  char str1[] = "Hello world";
  char str2[] = "Hello world!";
  s21_size_t n1 = 12;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_5) {
  char str1[] = "Hello world";
  char str2[] = "Hello world";
  s21_size_t n1 = 0;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_6) {
  char str1[] = "";
  char str2[] = "";
  s21_size_t n1 = 1;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_7) {
  char str1[] = "A";
  char str2[] = "B";
  s21_size_t n1 = 1;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_8) {
  char str1[] = "B";
  char str2[] = "A";
  s21_size_t n1 = 1;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_9) {
  char str1[] = "12345";
  char str2[] = "12345";
  s21_size_t n1 = 5;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_10) {
  char str1[] = "12345";
  char str2[] = "12346";
  s21_size_t n1 = 5;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_11) {
  char str1[] = "12345";
  char str2[] = "1234";
  s21_size_t n1 = 5;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_12) {
  char str1[] = "12345";
  char str2[] = "123456";
  s21_size_t n1 = 5;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_13) {
  char str1[] = "12345";
  char str2[] = "12345";
  s21_size_t n1 = 0;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_14) {
  char str1[] = "";
  char str2[] = "";
  s21_size_t n1 = 0;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_15) {
  char str1[] = "Hello world";
  char str2[] = "Hello world";
  s21_size_t n1 = 11;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_16) {
  char str1[] = "Hello world";
  char str2[] = "Hello world!";
  s21_size_t n1 = 11;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_17) {
  char str1[] = "Hello world";
  char str2[] = "Hello world";
  s21_size_t n1 = 12;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_18) {
  char str1[] = "Hello world";
  char str2[] = "Hello world!";
  s21_size_t n1 = 12;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_19) {
  char str1[] = "Hello world";
  char str2[] = "Hello world";
  s21_size_t n1 = 13;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_20) {
  char str1[] = "Hello world";
  char str2[] = "Hello world!";
  s21_size_t n1 = 13;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_21) {
  char str1[] = "Hello world";
  char str2[] = "Hello world";
  s21_size_t n1 = 10;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_22) {
  char str1[] = "Hello world";
  char str2[] = "Hell0 world";
  s21_size_t n1 = 10;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_23) {
  char str1[] = "Hello world";
  char str2[] = "Hell\0world";
  s21_size_t n1 = 10;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_24) {
  char str1[] = "1Hello world";
  char str2[] = "Hell\0world";
  s21_size_t n1 = 11;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_25) {
  char str1[] = "Hello world";
  char str2[] = "Hell\0world";
  s21_size_t n1 = 2;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

START_TEST(test_memcmp_26) {
  char str1[] = "Hello world";
  char str2[] = "Hellworld";
  s21_size_t n1 = 10;
  ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));
}
END_TEST

Suite *test_memcmp() {
  Suite *s = suite_create("s21_memcmp");
  TCase *tc = tcase_create("s21_memcmp");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_memcmp_1);
  tcase_add_test(tc, test_memcmp_2);
  tcase_add_test(tc, test_memcmp_3);
  tcase_add_test(tc, test_memcmp_4);
  tcase_add_test(tc, test_memcmp_5);
  tcase_add_test(tc, test_memcmp_6);
  tcase_add_test(tc, test_memcmp_7);
  tcase_add_test(tc, test_memcmp_8);
  tcase_add_test(tc, test_memcmp_9);
  tcase_add_test(tc, test_memcmp_10);
  tcase_add_test(tc, test_memcmp_11);
  tcase_add_test(tc, test_memcmp_12);
  tcase_add_test(tc, test_memcmp_13);
  tcase_add_test(tc, test_memcmp_14);
  tcase_add_test(tc, test_memcmp_15);
  tcase_add_test(tc, test_memcmp_16);
  tcase_add_test(tc, test_memcmp_17);
  tcase_add_test(tc, test_memcmp_18);
  tcase_add_test(tc, test_memcmp_19);
  tcase_add_test(tc, test_memcmp_20);
  tcase_add_test(tc, test_memcmp_21);
  tcase_add_test(tc, test_memcmp_22);
  tcase_add_test(tc, test_memcmp_23);
  tcase_add_test(tc, test_memcmp_24);
  tcase_add_test(tc, test_memcmp_25);
  tcase_add_test(tc, test_memcmp_26);

  suite_add_tcase(s, tc);
  return s;
}