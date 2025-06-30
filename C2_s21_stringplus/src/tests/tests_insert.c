#include "s21_test.h"

START_TEST(test_insert_1) {
  int size1 = 0;
  char *src = "hello";
  char *str = "world";
  char *new = s21_insert(src, str, size1);

  ck_assert_str_eq(new, "worldhello");
}
END_TEST

START_TEST(test_insert_2) {
  int size1 = 2;
  char *src = "hello";
  char *str = "world";
  char *new = s21_insert(src, str, size1);

  ck_assert_str_eq(new, "heworldllo");
}
END_TEST

START_TEST(test_insert_3) {
  int size1 = 5;
  char *src = "hello";
  char *str = "world";
  char *new = s21_insert(src, str, size1);

  ck_assert_str_eq(new, "helloworld");
}
END_TEST

START_TEST(test_insert_4) {
  int size1 = 0;
  char *src = "";
  char *str = "world";
  char *new = s21_insert(src, str, size1);

  ck_assert_str_eq(new, "world");
}
END_TEST

START_TEST(test_insert_5) {
  int size1 = 2;
  char *src = "hello";
  char *str = "";
  char *new = s21_insert(src, str, size1);

  ck_assert_str_eq(new, "hello");
}
END_TEST

Suite *test_insert() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_insert");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_insert_1);
  tcase_add_test(tc_core, test_insert_2);
  tcase_add_test(tc_core, test_insert_3);
  tcase_add_test(tc_core, test_insert_4);
  tcase_add_test(tc_core, test_insert_5);
  suite_add_tcase(s, tc_core);

  return s;
}