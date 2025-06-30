#include "s21_test.h"

START_TEST(test_memchr_1) {
  char str1[] = "Hello world";
  s21_size_t n1 = 10;
  int ch1 = 'e';
  ck_assert_ptr_eq(s21_memchr(str1, ch1, n1), memchr(str1, ch1, n1));
}
END_TEST

START_TEST(test_memchr_2) {
  char str2[] = "Hello world";
  s21_size_t n2 = 5;
  int ch2 = 'o';
  ck_assert_ptr_eq(s21_memchr(str2, ch2, n2), memchr(str2, ch2, n2));
}
END_TEST

START_TEST(test_memchr_3) {
  char str3[] = "Hello world";
  s21_size_t n3 = 15;
  int ch3 = 'w';
  ck_assert_ptr_eq(s21_memchr(str3, ch3, n3), memchr(str3, ch3, n3));
}
END_TEST

START_TEST(test_memchr_4) {
  char str4[] = "Hello world";
  s21_size_t n4 = 10;
  int ch4 = 'z';
  ck_assert_ptr_eq(s21_memchr(str4, ch4, n4), memchr(str4, ch4, n4));
}
END_TEST

START_TEST(test_memchr_5) {
  char str5[] = "";
  s21_size_t n5 = 0;
  int ch5 = 'a';
  ck_assert_ptr_eq(s21_memchr(str5, ch5, n5), memchr(str5, ch5, n5));
}
END_TEST

START_TEST(test_memchr_6) {
  char str6[] = "a";
  s21_size_t n6 = 1;
  int ch6 = 'a';
  ck_assert_ptr_eq(s21_memchr(str6, ch6, n6), memchr(str6, ch6, n6));
}
END_TEST

START_TEST(test_memchr_7) {
  char str7[] = "a";
  s21_size_t n7 = 1;
  int ch7 = 'b';
  ck_assert_ptr_eq(s21_memchr(str7, ch7, n7), memchr(str7, ch7, n7));
}
END_TEST

START_TEST(test_memchr_8) {
  char str8[] = "abcdefghijklmnopqrstuvwxyz";
  s21_size_t n8 = 26;
  int ch8 = 'z';
  ck_assert_ptr_eq(s21_memchr(str8, ch8, n8), memchr(str8, ch8, n8));
}
END_TEST

START_TEST(test_memchr_9) {
  char str9[] = "abcdefghijklmnopqrstuvwxyz";
  s21_size_t n9 = 26;
  int ch9 = 'A';
  ck_assert_ptr_eq(s21_memchr(str9, ch9, n9), memchr(str9, ch9, n9));
}
END_TEST

START_TEST(test_memchr_10) {
  char str10[] = "1234567890";
  s21_size_t n10 = 10;
  int ch10 = '5';
  ck_assert_ptr_eq(s21_memchr(str10, ch10, n10), memchr(str10, ch10, n10));
}
END_TEST

START_TEST(test_memchr_11) {
  char str11[] = "1234567890";
  s21_size_t n11 = 10;
  int ch11 = 'A';
  ck_assert_ptr_eq(s21_memchr(str11, ch11, n11), memchr(str11, ch11, n11));
}
END_TEST

START_TEST(test_memchr_12) {
  char str12[] = "abcdefghijklmnopqrstuvwxyz";
  s21_size_t n12 = 0;
  int ch12 = 'a';
  ck_assert_ptr_eq(s21_memchr(str12, ch12, n12), memchr(str12, ch12, n12));
}
END_TEST

START_TEST(test_memchr_13) {
  char str13[] = "abcdefghijklmnopqrstuvwxyz";
  s21_size_t n13 = 26;
  int ch13 = '\0';
  ck_assert_ptr_eq(s21_memchr(str13, ch13, n13), memchr(str13, ch13, n13));
}
END_TEST

START_TEST(test_memchr_14) {
  char str14[] = "abcdefghijklmnopqrstuvwxyz";
  s21_size_t n14 = 26;
  int ch14 = ' ';
  ck_assert_ptr_eq(s21_memchr(str14, ch14, n14), memchr(str14, ch14, n14));
}
END_TEST

START_TEST(test_memchr_15) {
  char str15[] = "abcdefghijklmnopqrstuvwxyz";
  s21_size_t n15 = 26;
  int ch15 = '\n';
  ck_assert_ptr_eq(s21_memchr(str15, ch15, n15), memchr(str15, ch15, n15));
}
END_TEST

START_TEST(test_memchr_16) {
  char str1[] = "Hello world";
  s21_size_t n1 = 10;
  int ch1 = 'e';
  ck_assert_ptr_eq(s21_memchr(str1, ch1, n1), memchr(str1, ch1, n1));
}
END_TEST

START_TEST(test_memchr_17) {
  char str2[] = "Hello world";
  s21_size_t n2 = 10;
  int ch2 = 'x';
  ck_assert_ptr_eq(s21_memchr(str2, ch2, n2), memchr(str2, ch2, n2));
}
END_TEST

START_TEST(test_memchr_18) {
  char str3[] = "Hello world";
  s21_size_t n3 = 12;
  int ch3 = 'x';
  ck_assert_ptr_eq(s21_memchr(str3, ch3, n3), memchr(str3, ch3, n3));
}
END_TEST

START_TEST(test_memchr_19) {
  char str4[] = "Hello\0world";
  s21_size_t n4 = 10;
  int ch4 = 'o';
  ck_assert_ptr_eq(s21_memchr(str4, ch4, n4), memchr(str4, ch4, n4));
}
END_TEST

START_TEST(test_memchr_20) {
  char str5[] = "Hello\0world";
  s21_size_t n5 = 10;
  int ch5 = 'w';
  ck_assert_ptr_eq(s21_memchr(str5, ch5, n5), memchr(str5, ch5, n5));
}
END_TEST

Suite *test_memchr() {
  Suite *s = suite_create("s21_memchr");
  TCase *tc = tcase_create("s21_memchr");

  tcase_add_test(tc, test_memchr_1);
  tcase_add_test(tc, test_memchr_2);
  tcase_add_test(tc, test_memchr_3);
  tcase_add_test(tc, test_memchr_4);
  tcase_add_test(tc, test_memchr_5);
  tcase_add_test(tc, test_memchr_6);
  tcase_add_test(tc, test_memchr_7);
  tcase_add_test(tc, test_memchr_8);
  tcase_add_test(tc, test_memchr_9);
  tcase_add_test(tc, test_memchr_10);
  tcase_add_test(tc, test_memchr_11);
  tcase_add_test(tc, test_memchr_12);
  tcase_add_test(tc, test_memchr_13);
  tcase_add_test(tc, test_memchr_14);
  tcase_add_test(tc, test_memchr_15);
  tcase_add_test(tc, test_memchr_16);
  tcase_add_test(tc, test_memchr_17);
  tcase_add_test(tc, test_memchr_18);
  tcase_add_test(tc, test_memchr_19);
  tcase_add_test(tc, test_memchr_20);
  suite_add_tcase(s, tc);
  return s;
}
