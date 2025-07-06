#include "../s21_matrix_test.h"

START_TEST(s21_eq_matrix_test) {
  matrix_t test_matrix1;
  matrix_t test_matrix2;

  s21_create_matrix(3, 3, &test_matrix1);
  s21_create_matrix(3, 3, &test_matrix2);

  int res = s21_eq_matrix(&test_matrix1, &test_matrix2);

  ck_assert_int_eq(res, 1);

  s21_remove_matrix(&test_matrix1);
  s21_remove_matrix(&test_matrix2);
}

START_TEST(EMT) {
  matrix_t test_matrix1;
  matrix_t test_matrix2;

  s21_create_matrix(3, 3, &test_matrix1);
  s21_create_matrix(3, 3, &test_matrix2);

  free(test_matrix1.matrix[2]);
  test_matrix1.matrix[2] = NULL;

  int res = s21_eq_matrix(&test_matrix1, &test_matrix2);

  s21_remove_matrix(&test_matrix1);
  s21_remove_matrix(&test_matrix2);
}
END_TEST;

Suite *eq_matrix_suite(void) {
  Suite *suite = suite_create("s21_eq_matrix_test");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_eq_matrix_test);
  // tcase_add_test(tc_core, EMT);
  suite_add_tcase(suite, tc_core);
  return suite;
}