#include "s21_test.h"

START_TEST(test_memcpy_1) {
  char src[] =
      "The memcpy function copies N bytes/characters from a memory "
      "location/block pointed to by source, to a memory area pointed to by "
      "destination. N = -1893476183746!";
  s21_size_t n = 161;
  char dest[n];
  char dest_etalon[n];
  char *result = (char *)s21_memcpy(dest, src, n);
  char *result_etalon = (char *)memcpy(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_memcpy_2) {
  char src[] =
      "The memcpy function copies N bytes/characters from a memory "
      "location/block pointed to by source, to a memory area pointed to by "
      "destination. N = -1893476183746!";
  s21_size_t n = 0;
  char dest[n];
  char dest_etalon[n];
  char *result = (char *)s21_memcpy(dest, src, n);
  char *result_etalon = (char *)memcpy(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_memcpy_3) {
  char src[] = "";
  s21_size_t n = 0;
  char dest[n];
  char dest_etalon[n];
  char *result = (char *)s21_memcpy(dest, src, n);
  char *result_etalon = (char *)memcpy(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_memcpy_4) {
  char src[] = "\0\0\0\0\0\t\t\t\t\t";
  s21_size_t n = 7;
  char dest[n];
  char dest_etalon[n];
  char *result = (char *)s21_memcpy(dest, src, n);
  char *result_etalon = (char *)memcpy(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_memcpy_5) {
  char src[] = "!#$$%&*())_+";
  s21_size_t n = 13;
  char dest[n];
  char dest_etalon[n];
  char *result = (char *)s21_memcpy(dest, src, n);
  char *result_etalon = (char *)memcpy(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_memcpy_7) {
  char src[] = "Test";
  s21_size_t n = 10;
  char dest[10];
  char dest_etalon[10];
  char *result = (char *)s21_memcpy(dest, src, n - 1);
  char *result_etalon = (char *)memcpy(dest_etalon, src, n - 1);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_memcpy_10) {
  char src[] =
      "The memcpy function copies N bytes/characters from a memory "
      "location/block pointed to by source, to a memory area pointed to by "
      "destination. N = -1893476183746!";
  s21_size_t n = 161;
  char dest[n];
  char dest_etalon[n];
  char *result = (char *)s21_memcpy(dest, src, n);
  char *result_etalon = (char *)memcpy(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_memcpy_11) {
  char src[] = "Hello, World!";
  s21_size_t n = 5;
  char dest[n];
  char dest_etalon[n];
  char *result = (char *)s21_memcpy(dest, src, n);
  char *result_etalon = (char *)memcpy(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_memcpy_12) {
  char src[] = "1234567890";
  s21_size_t n = 10;
  char dest[n];
  char dest_etalon[n];

  s21_memset(dest, 0, n);
  s21_memset(dest_etalon, 0, n);

  char *result = (char *)s21_memcpy(dest, src, n);
  char *result_etalon = (char *)memcpy(dest_etalon, src, n);

  // Подавляем предупреждения о неиспользуемых переменных
  (void)result;
  (void)result_etalon;

  for (s21_size_t i = 0; i < n; i++) {
    ck_assert_int_eq(dest[i], dest_etalon[i]);
  }
}
END_TEST

START_TEST(test_memcpy_13) {
  char src[] = "Test";
  s21_size_t n = 0;
  char dest[n];
  char dest_etalon[n];
  char *result = (char *)s21_memcpy(dest, src, n);
  char *result_etalon = (char *)memcpy(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_memcpy_14) {
  char src[] = "Test";
  s21_size_t n = 10;
  char dest[n];
  char dest_etalon[n];
  char *result = (char *)s21_memcpy(dest, src, n);
  char *result_etalon = (char *)memcpy(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_memcpy_15) {
  char src[] = "Test";
  s21_size_t n = 1;
  char dest[n];
  char dest_etalon[n];
  char *result = (char *)s21_memcpy(dest, src, n);
  char *result_etalon = (char *)memcpy(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_memcpy_16) {
  char src[] = "";
  s21_size_t n = 1;
  char dest[n];
  char dest_etalon[n];
  char *result = (char *)s21_memcpy(dest, src, n);
  char *result_etalon = (char *)memcpy(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_memcpy_17) {
  char src[] = "Test";
  s21_size_t n = 5;
  char dest[n];
  char dest_etalon[n];
  char *result = (char *)s21_memcpy(dest, src, n);
  char *result_etalon = (char *)memcpy(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_memcpy_18) {
  char src[] = "Test";
  s21_size_t n = 100;
  char dest[n];
  char dest_etalon[n];
  char *result = (char *)s21_memcpy(dest, src, n);
  char *result_etalon = (char *)memcpy(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

START_TEST(test_memcpy_19) {
  char src[] = "Test";
  s21_size_t n = 1000;
  char dest[n];
  char dest_etalon[n];
  char *result = (char *)s21_memcpy(dest, src, n);
  char *result_etalon = (char *)memcpy(dest_etalon, src, n);
  ck_assert_str_eq(dest, dest_etalon);
  ck_assert_str_eq(result, result_etalon);
}
END_TEST

Suite *test_memcpy() {
  Suite *s = suite_create("s21_memcpy");
  TCase *tc = tcase_create("s21_memcpy");

  tcase_add_test(tc, test_memcpy_1);
  tcase_add_test(tc, test_memcpy_2);
  tcase_add_test(tc, test_memcpy_3);
  tcase_add_test(tc, test_memcpy_4);
  tcase_add_test(tc, test_memcpy_5);
  tcase_add_test(tc, test_memcpy_7);
  tcase_add_test(tc, test_memcpy_10);
  tcase_add_test(tc, test_memcpy_11);
  tcase_add_test(tc, test_memcpy_12);
  tcase_add_test(tc, test_memcpy_13);
  tcase_add_test(tc, test_memcpy_14);
  tcase_add_test(tc, test_memcpy_15);
  tcase_add_test(tc, test_memcpy_16);
  tcase_add_test(tc, test_memcpy_17);
  tcase_add_test(tc, test_memcpy_18);
  tcase_add_test(tc, test_memcpy_19);

  suite_add_tcase(s, tc);
  return s;
}
