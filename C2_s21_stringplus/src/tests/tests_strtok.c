#include "s21_test.h"

START_TEST(test_strtok_01) {
  int n = 4;
  char str1[] = "_afga ___aers@asr___sweer__";
  char str2[] = "_afga ___aers@asr___sweer__";
  const char vp[] = " _!@";

  char *res = s21_strtok(str1, vp);
  char *orig = strtok(str2, vp);
  ck_assert_pstr_eq(res, orig);

  for (int i = 0; i < n; i++) {
    res = s21_strtok(s21_NULL, vp);
    orig = strtok(s21_NULL, vp);
  }
}
END_TEST

START_TEST(test_strtok_02) {
  int n = 4;
  char str1[] = "_afga ___ae\0s@asr___sweer__";
  char str2[] = "_afga ___ae\0s@asr___sweer__";
  const char vp[] = " _!@";

  char *res = s21_strtok(str1, vp);
  char *orig = strtok(str2, vp);
  ck_assert_pstr_eq(res, orig);

  for (int i = 0; i < n; i++) {
    res = s21_strtok(s21_NULL, vp);
    orig = strtok(s21_NULL, vp);
  }
}
END_TEST

START_TEST(test_strtok_03) {
  int n = 4;
  char str1[] = "_afga ___ae\0s@asr___sweer__";
  char str2[] = "_afga ___ae\0s@asr___sweer__";
  const char vp[] = "?";

  char *res = s21_strtok(str1, vp);
  char *orig = strtok(str2, vp);
  ck_assert_pstr_eq(res, orig);

  for (int i = 0; i < n; i++) {
    res = s21_strtok(s21_NULL, vp);
    orig = strtok(s21_NULL, vp);
  }
}

END_TEST

START_TEST(test_strtok_04) {
  int n = 6;
  char str1[] = "";
  char str2[] = "";
  const char vp[] = "";

  char *res = s21_strtok(str1, vp);
  char *orig = strtok(str2, vp);
  ck_assert_pstr_eq(res, orig);

  for (int i = 0; i < n; i++) {
    res = s21_strtok(s21_NULL, vp);
    orig = strtok(s21_NULL, vp);
  }
}
END_TEST

START_TEST(test_strtok_05) {
  int n = 10;
  char str1[] = "";
  char str2[] = "";
  const char vp[] = " !_";

  char *res = s21_strtok(str1, vp);
  char *orig = strtok(str2, vp);
  ck_assert_pstr_eq(res, orig);

  for (int i = 0; i < n; i++) {
    res = s21_strtok(s21_NULL, vp);
    orig = strtok(s21_NULL, vp);
  }
}
END_TEST

START_TEST(test_strtok_06) {
  int n = 7;
  char str1[] = "_afga ___aers@asr___sweer__";
  char str2[] = "_afga ___aers@asr___sweer__";
  const char vp[] = "";

  char *res = s21_strtok(str1, vp);
  char *orig = strtok(str2, vp);
  ck_assert_pstr_eq(res, orig);

  for (int i = 0; i < n; i++) {
    res = s21_strtok(s21_NULL, vp);
    orig = strtok(s21_NULL, vp);
  }
}
END_TEST

START_TEST(test_strtok_07) {
  int n = 4;
  char str1[] = "_afga ___aers@asr___sweer__";
  char str2[] = "_afga ___aers@asr___sweer__";
  const char vp[] = "\0";

  char *res = s21_strtok(str1, vp);
  char *orig = strtok(str2, vp);
  ck_assert_pstr_eq(res, orig);

  for (int i = 0; i < n; i++) {
    res = s21_strtok(s21_NULL, vp);
    orig = strtok(s21_NULL, vp);
  }
}
END_TEST

START_TEST(test_strtok_08) {
  int n = 10;
  char str1[] = "\0\0";
  char str2[] = "\0\0";
  const char vp[] = "\0";

  char *res = s21_strtok(str1, vp);
  char *orig = strtok(str2, vp);
  ck_assert_pstr_eq(res, orig);

  for (int i = 0; i < n; i++) {
    res = s21_strtok(s21_NULL, vp);
    orig = strtok(s21_NULL, vp);
  }
}
END_TEST

START_TEST(test_strtok_1) {
  int n = 4;
  char str1[] = "_afga ___aers@asr___sweer__";
  char str2[] = "_afga ___aers@asr___sweer__";
  const char vp[] = " _!@";

  char *res = s21_strtok(str1, vp);
  char *orig = strtok(str2, vp);
  ck_assert_pstr_eq(res, orig);

  for (int i = 0; i < n; i++) {
    res = s21_strtok(s21_NULL, vp);
    orig = strtok(s21_NULL, vp);
  }
}
END_TEST

START_TEST(test_strtok_2) {
  int n = 4;
  char str1[] = "Hello,World!";
  char str2[] = "Hello,World!";
  const char vp[] = ",";

  char *res = s21_strtok(str1, vp);
  char *orig = strtok(str2, vp);
  ck_assert_pstr_eq(res, orig);

  for (int i = 0; i < n; i++) {
    res = s21_strtok(s21_NULL, vp);
    orig = strtok(s21_NULL, vp);
  }
}
END_TEST

START_TEST(test_strtok_3) {
  int n = 4;
  char str1[] = "1234567890";
  char str2[] = "1234567890";
  const char vp[] = "369";

  char *res = s21_strtok(str1, vp);
  char *orig = strtok(str2, vp);
  ck_assert_pstr_eq(res, orig);

  for (int i = 0; i < n; i++) {
    res = s21_strtok(s21_NULL, vp);
    orig = strtok(s21_NULL, vp);
  }
}
END_TEST

START_TEST(test_strtok_4) {
  int n = 4;
  char str1[] = "abcdefghijklmnopqrstuvwxyz";
  char str2[] = "abcdefghijklmnopqrstuvwxyz";
  const char vp[] = "aeiou";

  char *res = s21_strtok(str1, vp);
  char *orig = strtok(str2, vp);
  ck_assert_pstr_eq(res, orig);

  for (int i = 0; i < n; i++) {
    res = s21_strtok(s21_NULL, vp);
    orig = strtok(s21_NULL, vp);
  }
}
END_TEST

START_TEST(test_strtok_empty_string) {
  int n = 4;
  char str1[] = "";
  char str2[] = "";
  const char vp[] = " ";

  char *res = s21_strtok(str1, vp);
  char *orig = strtok(str2, vp);
  ck_assert_pstr_eq(res, orig);

  for (int i = 0; i < n; i++) {
    res = s21_strtok(s21_NULL, vp);
    orig = strtok(s21_NULL, vp);
  }
}
END_TEST

START_TEST(test_strtok_empty_delimiters) {
  int n = 4;
  char str1[] = "HelloWorld";
  char str2[] = "HelloWorld";
  const char vp[] = "";

  char *res = s21_strtok(str1, vp);
  char *orig = strtok(str2, vp);
  ck_assert_pstr_eq(res, orig);

  for (int i = 0; i < n; i++) {
    res = s21_strtok(s21_NULL, vp);
    orig = strtok(s21_NULL, vp);
  }
}
END_TEST

/* COMMENTED because original strtok follows to Segmentation fault on this
tests. Not s21_strtok. START_TEST(test_strtok_null_string) { int n = 4; char
*str1 = s21_NULL; char *str2 = s21_NULL; const char vp[] = " ";

  char *res = s21_strtok(str1, vp);
  char *orig = strtok(str2, vp);
 // ck_assert_pstr_eq(res, orig);

  for (int i = 0; i < n; i++) {
    res = s21_strtok(s21_NULL, vp);
 //   orig = strtok(s21_NULL, vp);
  }
}
END_TEST

START_TEST(test_strtok_null_delimiters) {
  int n = 4;
  char str1[] = "HelloWorld";
  char str2[] = "HelloWorld";
  const char *vp = s21_NULL;

  char *res = s21_strtok(str1, vp);
  char *orig = strtok(str2, vp);
 // ck_assert_pstr_eq(res, orig);

  for (int i = 0; i < n; i++) {
    res = s21_strtok(s21_NULL, vp);
 //   orig = strtok(s21_NULL, vp);
  }
}
END_TEST
*/

START_TEST(test_strtok_multiple_delimiters) {
  int n = 4;
  char str1[] = "Hello,World!";
  char str2[] = "Hello,World!";
  const char vp[] = ",!";

  char *res = s21_strtok(str1, vp);
  char *orig = strtok(str2, vp);
  ck_assert_pstr_eq(res, orig);

  for (int i = 0; i < n; i++) {
    res = s21_strtok(s21_NULL, vp);
    orig = strtok(s21_NULL, vp);
  }
}
END_TEST

START_TEST(test_strtok_no_delimiters) {
  int n = 4;
  char str1[] = "HelloWorld";
  char str2[] = "HelloWorld";
  const char vp[] = "xyz";

  char *res = s21_strtok(str1, vp);
  char *orig = strtok(str2, vp);
  ck_assert_pstr_eq(res, orig);

  for (int i = 0; i < n; i++) {
    res = s21_strtok(s21_NULL, vp);
    orig = strtok(s21_NULL, vp);
  }
}
END_TEST

Suite *test_strtok() {
  Suite *s = suite_create("s21_strtok");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strtok_01);
  tcase_add_test(tc_core, test_strtok_02);
  tcase_add_test(tc_core, test_strtok_03);
  tcase_add_test(tc_core, test_strtok_04);
  tcase_add_test(tc_core, test_strtok_05);
  tcase_add_test(tc_core, test_strtok_06);
  tcase_add_test(tc_core, test_strtok_07);
  tcase_add_test(tc_core, test_strtok_08);
  tcase_add_test(tc_core, test_strtok_1);
  tcase_add_test(tc_core, test_strtok_2);
  tcase_add_test(tc_core, test_strtok_3);
  tcase_add_test(tc_core, test_strtok_4);
  tcase_add_test(tc_core, test_strtok_empty_string);
  tcase_add_test(tc_core, test_strtok_empty_delimiters);
  tcase_add_test(tc_core, test_strtok_multiple_delimiters);
  tcase_add_test(tc_core, test_strtok_no_delimiters);

  suite_add_tcase(s, tc_core);

  return s;
}
