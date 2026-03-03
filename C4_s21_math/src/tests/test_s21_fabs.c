#include <stdlib.h>
#include <time.h>

#include "s21_math_tests.h"

void test_fabs(double input) {
  double result = s21_fabs(input);
  double expected = fabs(input);
  s21_test_case(result, expected);
}

START_TEST(test_s21_fabs_zero) { test_fabs(0.0); }
END_TEST

START_TEST(test_s21_fabs_minus_zero) { test_fabs(-0.0); }
END_TEST

START_TEST(test_s21_fabs_infinity) { test_fabs(INFINITY); }
END_TEST

START_TEST(test_s21_fabs_minus_infinity) { test_fabs(-INFINITY); }
END_TEST

START_TEST(test_s21_fabs_nan) { test_fabs(NAN); }
END_TEST

START_TEST(test_s21_fabs_minus_nan) { test_fabs(-NAN); }
END_TEST

START_TEST(test_s21_fabs_min_denormalized) { test_fabs(DBL_TRUE_MIN); }
END_TEST

START_TEST(test_s21_fabs_minus_min_denormalized) { test_fabs(-DBL_TRUE_MIN); }
END_TEST

START_TEST(test_s21_fabs_almost_min_denormalized) {
  double input = nextafter(DBL_TRUE_MIN, 1.0);
  test_fabs(input);
}
END_TEST

START_TEST(test_s21_fabs_minus_almost_min_denormalized) {
  double input = nextafter(-DBL_TRUE_MIN, -1.0);
  test_fabs(input);
}
END_TEST

START_TEST(test_s21_fabs_max_denormalized) {
  double max_denormalized = nextafter(DBL_MIN, 0.0);
  test_fabs(max_denormalized);
}
END_TEST

START_TEST(test_s21_fabs_minus_max_denormalized) {
  double max_denormalized = nextafter(-DBL_MIN, 0.0);
  test_fabs(max_denormalized);
}
END_TEST

START_TEST(test_s21_fabs_almost_max_denormalized) {
  double max_denormalized = nextafter(DBL_MIN, 0.0);
  double almost_max_denormalized = nextafter(max_denormalized, 0.0);
  test_fabs(almost_max_denormalized);
}
END_TEST

START_TEST(test_s21_fabs_minus_almost_max_denormalized) {
  double max_denormalized = nextafter(DBL_MIN, 0.0);
  double almost_max_denormalized = nextafter(-max_denormalized, 0.0);
  test_fabs(almost_max_denormalized);
}
END_TEST

START_TEST(test_s21_fabs_random_denormalized) {
  srand(time(NULL));
  const int num_tests = 1000;
  for (int i = 0; i < num_tests; i++) {
    double x =
        (double)rand() / RAND_MAX * (DBL_MIN - DBL_TRUE_MIN) + DBL_TRUE_MIN;
    test_fabs(x);
  }
}
END_TEST

START_TEST(test_s21_fabs_minus_random_denormalized) {
  srand(time(NULL));
  const int num_tests = 1000;
  for (int i = 0; i < num_tests; i++) {
    double x =
        (double)rand() / RAND_MAX * (DBL_TRUE_MIN - DBL_MIN) - DBL_TRUE_MIN;
    test_fabs(x);
  }
}
END_TEST

START_TEST(test_s21_fabs_min_normalized) { test_fabs(DBL_MIN); }
END_TEST

START_TEST(test_s21_fabs_minus_min_normalized) { test_fabs(-DBL_MIN); }
END_TEST

START_TEST(test_s21_fabs_almost_min_normalized) {
  double almost_min_normalized = nextafter(DBL_MIN, 2.0);
  test_fabs(almost_min_normalized);
}
END_TEST

START_TEST(test_s21_fabs_minus_almost_min_normalized) {
  double almost_min_normalized = nextafter(-DBL_MIN, -2.0);
  test_fabs(almost_min_normalized);
}
END_TEST

START_TEST(test_s21_fabs_almost_min_normalized_2) {
  double almost_min_normalized = DBL_MIN + DBL_EPSILON;
  test_fabs(almost_min_normalized);
}
END_TEST

START_TEST(test_s21_fabs_minus_almost_min_normalized_2) {
  double almost_min_normalized = -DBL_MIN - DBL_EPSILON;
  test_fabs(almost_min_normalized);
}
END_TEST

START_TEST(test_s21_fabs_max_normalized) { test_fabs(DBL_MAX); }
END_TEST

START_TEST(test_s21_fabs_minus_max_normalized) { test_fabs(-DBL_MAX); }
END_TEST

START_TEST(test_s21_fabs_almost_max_normalized) {
  double almost_max_normalized = nextafter(DBL_MAX, 0.0);
  test_fabs(almost_max_normalized);
}
END_TEST

START_TEST(test_s21_fabs_minus_almost_max_normalized) {
  double almost_max_normalized = nextafter(-DBL_MAX, 0.0);
  test_fabs(almost_max_normalized);
}
END_TEST

START_TEST(test_s21_fabs_almost_max_normalized_2) {
  double almost_max_normalized = DBL_MAX - DBL_EPSILON;
  test_fabs(almost_max_normalized);
}
END_TEST

START_TEST(test_s21_fabs_minus_almost_max_normalized_2) {
  double almost_max_normalized = -DBL_MAX + DBL_EPSILON;
  test_fabs(almost_max_normalized);
}
END_TEST

START_TEST(test_s21_fabs_random_small_normalized) {
  srand(time(NULL));
  const int num_tests = 1000;
  for (int i = 0; i < num_tests; i++) {
    double x = (double)rand() / RAND_MAX * (1.0 - DBL_MIN) + DBL_MIN;
    test_fabs(x);
  }
}
END_TEST

START_TEST(test_s21_fabs_minus_random_small_normalized) {
  srand(time(NULL));
  const int num_tests = 1000;
  for (int i = 0; i < num_tests; i++) {
    double x = (double)rand() / RAND_MAX * (-1.0 + DBL_MIN) - DBL_MIN;
    test_fabs(x);
  }
}
END_TEST

// Как я вычисляла первое настолько большое число, что оно не имеет дробной
// части. https://habr.com/ru/articles/337260/ Экспонента показывает, в "окне"
// между какими двумя степенями двойки будет лежать искомое число, указывая на
// первое из них. Мантисса как бы делит это окно на 8388608 частей - возможных
// значений мантиссы. Чтобы число не имело дробной части, каждый кусочек, на
// который мантисса разбивает окно, должен быть равен или больше 1. Найти размер
// кусочка по формуле (2^(x+1) - 2^x) / 8388608, где в числителе "объем"
// заданного экспонентой окна, а в знаменателе - количество кусочков. Кусочек
// равен единице при 2^23, т.е. начиная с 8388608. Да, это можно было вычислить
// и проще, знаю.

START_TEST(test_s21_fabs_random_medium_normalized) {
  srand(time(NULL));
  const int num_tests = 1000;
  for (int i = 0; i < num_tests; i++) {
    double x = (double)rand() / RAND_MAX * (8388608.0 - 1.0) + 1.0;
    test_fabs(x);
  }
}
END_TEST

START_TEST(test_s21_fabs_minus_random_medium_normalized) {
  srand(time(NULL));
  const int num_tests = 1000;
  for (int i = 0; i < num_tests; i++) {
    double x = (double)rand() / RAND_MAX * (-8388608.0 + 1.0) - 1.0;
    test_fabs(x);
  }
}
END_TEST

START_TEST(test_s21_fabs_random_big_normalized) {
  srand(time(NULL));
  const int num_tests = 1000;
  for (int i = 0; i < num_tests; i++) {
    double x = (double)rand() / RAND_MAX * (DBL_MAX - 8388608.0) + 8388608.0;
    test_fabs(x);
  }
}
END_TEST

START_TEST(test_s21_fabs_minus_random_big_normalized) {
  srand(time(NULL));
  const int num_tests = 1000;
  for (int i = 0; i < num_tests; i++) {
    double x = (double)rand() / RAND_MAX * (-DBL_MAX + 8388608.0) - 8388608.0;
    test_fabs(x);
  }
}
END_TEST

START_TEST(test_s21_fabs_normalized_edge_no_fractional) {
  test_fabs(8388608.0);
}
END_TEST

START_TEST(test_s21_fabs_minus_normalized_edge_no_fractional) {
  test_fabs(-8388608.0);
}
END_TEST

START_TEST(test_s21_fabs_almost_normalized_edge) {
  double almost_edge = nextafter(8388608.0, 0.0);
  test_fabs(almost_edge);
}
END_TEST

START_TEST(test_s21_fabs_minus_almost_normalized_edge) {
  double almost_edge = nextafter(-8388608.0, 0.0);
  test_fabs(almost_edge);
}
END_TEST

START_TEST(test_s21_fabs_almost_normalized_edge_2) {
  double almost_edge = nextafter(8388608.0, DBL_MAX);
  test_fabs(almost_edge);
}
END_TEST

START_TEST(test_s21_fabs_minus_almost_normalized_edge_2) {
  double almost_edge = nextafter(-8388608.0, -DBL_MAX);
  test_fabs(almost_edge);
}
END_TEST

START_TEST(test_s21_fabs_almost_normalized_edge_3) {
  double almost_edge = 8388608.0 - DBL_EPSILON;
  test_fabs(almost_edge);
}
END_TEST

START_TEST(test_s21_fabs_minus_almost_normalized_edge_3) {
  double almost_edge = -8388608.0 + DBL_EPSILON;
  test_fabs(almost_edge);
}
END_TEST

START_TEST(test_s21_fabs_almost_normalized_edge_4) {
  double almost_edge = 8388608.0 + DBL_EPSILON;
  test_fabs(almost_edge);
}
END_TEST

START_TEST(test_s21_fabs_minus_almost_normalized_edge_4) {
  double almost_edge = -8388608.0 - DBL_EPSILON;
  test_fabs(almost_edge);
}
END_TEST

Suite *test_s21_fabs(void) {
  Suite *s = suite_create("\033[42m-=S21_fabs=-\033[0m");
  TCase *tc = tcase_create("s21_fabs_tc");

  tcase_add_test(tc, test_s21_fabs_zero);
  tcase_add_test(tc, test_s21_fabs_minus_zero);
  tcase_add_test(tc, test_s21_fabs_infinity);
  tcase_add_test(tc, test_s21_fabs_minus_infinity);
  tcase_add_test(tc, test_s21_fabs_nan);
  tcase_add_test(tc, test_s21_fabs_minus_nan);

  tcase_add_test(tc, test_s21_fabs_min_denormalized);
  tcase_add_test(tc, test_s21_fabs_minus_min_denormalized);
  tcase_add_test(tc, test_s21_fabs_almost_min_denormalized);
  tcase_add_test(tc, test_s21_fabs_minus_almost_min_denormalized);
  tcase_add_test(tc, test_s21_fabs_max_denormalized);
  tcase_add_test(tc, test_s21_fabs_minus_max_denormalized);
  tcase_add_test(tc, test_s21_fabs_almost_max_denormalized);
  tcase_add_test(tc, test_s21_fabs_minus_almost_max_denormalized);
  tcase_add_test(tc, test_s21_fabs_random_denormalized);
  tcase_add_test(tc, test_s21_fabs_minus_random_denormalized);

  tcase_add_test(tc, test_s21_fabs_min_normalized);
  tcase_add_test(tc, test_s21_fabs_minus_min_normalized);
  tcase_add_test(tc, test_s21_fabs_almost_min_normalized);
  tcase_add_test(tc, test_s21_fabs_minus_almost_min_normalized);
  tcase_add_test(tc, test_s21_fabs_almost_min_normalized_2);
  tcase_add_test(tc, test_s21_fabs_minus_almost_min_normalized_2);
  tcase_add_test(tc, test_s21_fabs_max_normalized);
  tcase_add_test(tc, test_s21_fabs_minus_max_normalized);
  tcase_add_test(tc, test_s21_fabs_almost_max_normalized);
  tcase_add_test(tc, test_s21_fabs_minus_almost_max_normalized);
  tcase_add_test(tc, test_s21_fabs_almost_max_normalized_2);
  tcase_add_test(tc, test_s21_fabs_minus_almost_max_normalized_2);
  tcase_add_test(tc, test_s21_fabs_random_small_normalized);
  tcase_add_test(tc, test_s21_fabs_minus_random_small_normalized);
  tcase_add_test(tc, test_s21_fabs_random_medium_normalized);
  tcase_add_test(tc, test_s21_fabs_minus_random_medium_normalized);
  tcase_add_test(tc, test_s21_fabs_random_big_normalized);
  tcase_add_test(tc, test_s21_fabs_minus_random_big_normalized);
  tcase_add_test(tc, test_s21_fabs_normalized_edge_no_fractional);
  tcase_add_test(tc, test_s21_fabs_minus_normalized_edge_no_fractional);
  tcase_add_test(tc, test_s21_fabs_almost_normalized_edge);
  tcase_add_test(tc, test_s21_fabs_minus_almost_normalized_edge);
  tcase_add_test(tc, test_s21_fabs_almost_normalized_edge_2);
  tcase_add_test(tc, test_s21_fabs_minus_almost_normalized_edge_2);
  tcase_add_test(tc, test_s21_fabs_almost_normalized_edge_3);
  tcase_add_test(tc, test_s21_fabs_minus_almost_normalized_edge_3);
  tcase_add_test(tc, test_s21_fabs_almost_normalized_edge_4);
  tcase_add_test(tc, test_s21_fabs_minus_almost_normalized_edge_4);

  suite_add_tcase(s, tc);
  return s;
}
