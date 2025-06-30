#include "s21_test.h"

START_TEST(test_sprintf_c) {
  char buffer[100];
  char buffer_orig[100];
  char c = '#';
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %c - da", c),
                   sprintf(buffer_orig, "Yes, %c - da", c));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_d) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %d - da", d),
                   sprintf(buffer_orig, "Yes, %d - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_f) {
  char buffer[100];
  char buffer_orig[100];
  float f = 123.456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %f - da", f),
                   sprintf(buffer_orig, "Yes, %f - da", f));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_s) {
  char buffer[100];
  char buffer_orig[100];
  char s[] = "Hello";
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %s - da", s),
                   sprintf(buffer_orig, "Yes, %s - da", s));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_u) {
  char buffer[100];
  char buffer_orig[100];
  unsigned int u = 12345;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %u - da", u),
                   sprintf(buffer_orig, "Yes, %u - da", u));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_percent) {
  char buffer[100];
  char buffer_orig[100];
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %% - da"),
                   sprintf(buffer_orig, "Yes, %% - da"));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_g) {
  char buffer[100];
  char buffer_orig[100];
  double g = 12345.6789;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %g - da", g),
                   sprintf(buffer_orig, "Yes, %g - da", g));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_G) {
  char buffer[100];
  char buffer_orig[100];
  double G = 12345.6789;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %G - da", G),
                   sprintf(buffer_orig, "Yes, %G - da", G));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_e) {
  char buffer[100];
  char buffer_orig[100];
  double e = 12345.6789;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %e - da", e),
                   sprintf(buffer_orig, "Yes, %e - da", e));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_E) {
  char buffer[100];
  char buffer_orig[100];
  double E = 12345.6789;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %E - da", E),
                   sprintf(buffer_orig, "Yes, %E - da", E));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_x) {
  char buffer[100];
  char buffer_orig[100];
  int x = 12345;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %x - da", x),
                   sprintf(buffer_orig, "Yes, %x - da", x));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_X) {
  char buffer[100];
  char buffer_orig[100];
  int X = 12345;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %X - da", X),
                   sprintf(buffer_orig, "Yes, %X - da", X));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_o) {
  char buffer[100];
  char buffer_orig[100];
  int o = 12345;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %o - da", o),
                   sprintf(buffer_orig, "Yes, %o - da", o));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_p) {
  char buffer[100];
  char buffer_orig[100];
  int *p = NULL;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %p - da", p),
                   sprintf(buffer_orig, "Yes, %p - da", p));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_width) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %10d - da", d),
                   sprintf(buffer_orig, "Yes, %10d - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_width_star) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %*d - da", 10, d),
                   sprintf(buffer_orig, "Yes, %*d - da", 10, d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_precision) {
  char buffer[100];
  char buffer_orig[100];
  double f = 123.456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %.2f - da", f),
                   sprintf(buffer_orig, "Yes, %.2f - da", f));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_precision_star) {
  char buffer[100];
  char buffer_orig[100];
  double f = 123.456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %.*f - da", 2, f),
                   sprintf(buffer_orig, "Yes, %.*f - da", 2, f));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_length_l) {
  char buffer[100];
  char buffer_orig[100];
  long int l = 123456789012345;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %ld - da", l),
                   sprintf(buffer_orig, "Yes, %ld - da", l));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_length_h) {
  char buffer[100];
  char buffer_orig[100];
  short int h = 12345;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %hd - da", h),
                   sprintf(buffer_orig, "Yes, %hd - da", h));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_length_L) {
  char buffer[100];
  char buffer_orig[100];
  long double L = 12345.6789;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %Lf - da", L),
                   sprintf(buffer_orig, "Yes, %Lf - da", L));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_flag_plus) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %+d - da", d),
                   sprintf(buffer_orig, "Yes, %+d - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_flag_minus) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %-10d - da", d),
                   sprintf(buffer_orig, "Yes, %-10d - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_flag_space) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, % d - da", d),
                   sprintf(buffer_orig, "Yes, % d - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_flag_zero) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %010d - da", d),
                   sprintf(buffer_orig, "Yes, %010d - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_flag_hash) {
  char buffer[100];
  char buffer_orig[100];
  int x = 12345;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %#x - da", x),
                   sprintf(buffer_orig, "Yes, %#x - da", x));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

// Негативные тесты

START_TEST(test_sprintf_negative_width) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %-10d - da", d),
                   sprintf(buffer_orig, "Yes, %-10d - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_negative_precision) {
  char buffer[100];
  char buffer_orig[100];
  double f = 123.456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %.2f - da", f),
                   sprintf(buffer_orig, "Yes, %.2f - da", f));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_negative_length) {
  char buffer[100];
  char buffer_orig[100];
  long int l = 123456789012345;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %ld - da", l),
                   sprintf(buffer_orig, "Yes, %ld - da", l));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_combination_flags_01) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %+010d - da", d),
                   sprintf(buffer_orig, "Yes, %+010d - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_combination_flags_02) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %-+10d - da", d),
                   sprintf(buffer_orig, "Yes, %-+10d - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_combination_flags_03) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, % 010d - da", d),
                   sprintf(buffer_orig, "Yes, % 010d - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_combination_flags_04) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %#010x - da", d),
                   sprintf(buffer_orig, "Yes, %#010x - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

Suite *test_sprintf() {
  Suite *s = suite_create("s21_sprintf");
  TCase *tc = tcase_create("s21_sprintf");

  tcase_add_test(tc, test_sprintf_c);
  tcase_add_test(tc, test_sprintf_d);
  tcase_add_test(tc, test_sprintf_f);
  tcase_add_test(tc, test_sprintf_s);
  tcase_add_test(tc, test_sprintf_u);
  tcase_add_test(tc, test_sprintf_percent);
  tcase_add_test(tc, test_sprintf_g);
  tcase_add_test(tc, test_sprintf_G);
  tcase_add_test(tc, test_sprintf_e);
  tcase_add_test(tc, test_sprintf_E);
  tcase_add_test(tc, test_sprintf_x);
  tcase_add_test(tc, test_sprintf_X);
  tcase_add_test(tc, test_sprintf_o);
  tcase_add_test(tc, test_sprintf_p);
  tcase_add_test(tc, test_sprintf_width);
  tcase_add_test(tc, test_sprintf_width_star);
  tcase_add_test(tc, test_sprintf_precision);
  tcase_add_test(tc, test_sprintf_precision_star);
  tcase_add_test(tc, test_sprintf_length_l);
  tcase_add_test(tc, test_sprintf_length_h);
  tcase_add_test(tc, test_sprintf_length_L);
  tcase_add_test(tc, test_sprintf_flag_plus);
  tcase_add_test(tc, test_sprintf_flag_minus);
  tcase_add_test(tc, test_sprintf_flag_space);
  tcase_add_test(tc, test_sprintf_flag_zero);
  tcase_add_test(tc, test_sprintf_flag_hash);

  tcase_add_test(tc, test_sprintf_negative_width);
  tcase_add_test(tc, test_sprintf_negative_precision);
  tcase_add_test(tc, test_sprintf_negative_length);

  tcase_add_test(tc, test_sprintf_combination_flags_01);
  tcase_add_test(tc, test_sprintf_combination_flags_02);
  tcase_add_test(tc, test_sprintf_combination_flags_03);
  tcase_add_test(tc, test_sprintf_combination_flags_04);

  suite_add_tcase(s, tc);
  return s;
}

/*
START_TEST(test_sprintf_1) {
  char buffer[100];
  char buffer_orig[100];

  int dest;
  dest = s21_sprintf(buffer, "Yes, 100%% ok");
  int desto;
  desto = sprintf(buffer_orig, "Yes, 100%% ok");

  ck_assert_int_eq(dest, desto);
}
END_TEST

START_TEST(test_sprintf_2) {
  char buffer[100];
  char buffer_orig[100];
  char c = '#';

  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %c - da", c),
                   sprintf(buffer_orig, "Yes, %c - da", c));
}
END_TEST

START_TEST(test_sprintf_3) {
  char buffer[100];
  char buffer_orig[100];
  char c = '#';
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %c %d - da", c, d),
                   sprintf(buffer_orig, "Yes, %c %d - da", c, d));
}
END_TEST

START_TEST(test_sprintf_4) {
  char buffer[100];
  char buffer_orig[100];
  int d = 158;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %d - da", d),
                   sprintf(buffer_orig, "Yes, %d - da", d));
}
END_TEST

START_TEST(test_sprintf_5) {
  char buffer[100];
  char buffer_orig[100];
  double f = 432.74;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %f - da", f),
                   sprintf(buffer_orig, "Yes, %f - da", f));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_6) {
  char buffer[100];
  char buffer_orig[100];
  char *s = "Utka";
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %s - da", s),
                   sprintf(buffer_orig, "Yes, %s - da", s));
}
END_TEST

START_TEST(test_sprintf_7) {
  char buffer[100];
  char buffer_orig[100];
  int u = 543;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %u - da", u),
                   sprintf(buffer_orig, "Yes, %u - da", u));
}
END_TEST

START_TEST(test_sprintf_8) {
  char buffer[100];
  char buffer_orig[100];
  int d = 158;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %-d - da", d),
                   sprintf(buffer_orig, "Yes, %-d - da", d));
}
END_TEST

START_TEST(test_sprintf_9) {
  char buffer[100];
  char buffer_orig[100];
  int d = 158;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %+d - da", d),
                   sprintf(buffer_orig, "Yes, %+d - da", d));
}
END_TEST

START_TEST(test_sprintf_10) {
  char buffer[100];
  char buffer_orig[100];
  int d = 158;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, % d - da", d),
                   sprintf(buffer_orig, "Yes, % d - da", d));
}
END_TEST

START_TEST(test_sprintf_11) {
  char buffer[100];
  char buffer_orig[100];
  int d = 158;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %5d - da", d),
                   sprintf(buffer_orig, "Yes, %5d - da", d));
}
END_TEST

START_TEST(test_sprintf_12) {
  char buffer[100];
  char buffer_orig[100];
  int d = 158;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %.5d - da", d),
                   sprintf(buffer_orig, "Yes, %.5d - da", d));
}
END_TEST

START_TEST(test_sprintf_13) {
  char buffer[100];
  char buffer_orig[100];
  int d = -158;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %.5d - da", d),
                   sprintf(buffer_orig, "Yes, %.5d - da", d));
}
END_TEST

START_TEST(test_sprintf_14) {
  char buffer[100];
  char buffer_orig[100];
  char *p = "hello";
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %p - da", p),
                   sprintf(buffer_orig, "Yes, %p - da", p));
}
END_TEST

Suite *test_sprintf() {
  Suite *s = suite_create("s21_sprintf");
  TCase *tc = tcase_create("s21_sprintf");

  tcase_add_test(tc, test_sprintf_1);
  tcase_add_test(tc, test_sprintf_2);
  tcase_add_test(tc, test_sprintf_3);
  tcase_add_test(tc, test_sprintf_4);
  tcase_add_test(tc, test_sprintf_5);
  tcase_add_test(tc, test_sprintf_6);
  tcase_add_test(tc, test_sprintf_7);
  tcase_add_test(tc, test_sprintf_8);
  tcase_add_test(tc, test_sprintf_9);
  tcase_add_test(tc, test_sprintf_10);
  tcase_add_test(tc, test_sprintf_11);
  tcase_add_test(tc, test_sprintf_12);
  tcase_add_test(tc, test_sprintf_13);
  tcase_add_test(tc, test_sprintf_14);

  suite_add_tcase(s, tc);
  return s;
}
*/