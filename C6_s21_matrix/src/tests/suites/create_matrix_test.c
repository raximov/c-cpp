#include "../s21_matrix_test.h"

START_TEST(TCM) {
  matrix_t test_matrix1 = {0};
  static matrix_t test_matrix2;  // static & { 0 } - same thing

  int res = s21_create_matrix(4, 4, &test_matrix1);
  ck_assert_int_eq(res, EXIT_SUCCESS);

  res = s21_create_matrix(4, 4, &test_matrix2);
  ck_assert_int_eq(res, EXIT_SUCCESS);

  s21_remove_matrix(&test_matrix1);
  s21_remove_matrix(&test_matrix2);
}

START_TEST(TCM_NULL) {
  matrix_t test_matrix1;

  int res = s21_create_matrix(4, 4, &test_matrix1);

  free(test_matrix1.matrix[2]);
  test_matrix1.matrix[2] = NULL;

  s21_remove_matrix(&test_matrix1);

  ck_assert_int_eq(res, EXIT_SUCCESS);
}

END_TEST;

Suite* create_matrix_suite(void) {
  Suite* suite = suite_create("\n\ns21_create_matrix_test");
  TCase* tc_core = tcase_create("Core`");

  tcase_add_test(tc_core, TCM);
  // tcase_add_test(tc_core, TCM_NULL);
  suite_add_tcase(suite, tc_core);
  return suite;
}