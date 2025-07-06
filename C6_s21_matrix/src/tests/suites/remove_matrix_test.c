#include "../s21_matrix_test.h"

START_TEST(TRM_NULL) {
  matrix_t test_matrix1;

  int res = s21_create_matrix(4, 4, &test_matrix1);

  free(test_matrix1.matrix[2]);
  test_matrix1.matrix[2] = NULL;

  s21_remove_matrix(&test_matrix1);

  ck_assert_int_eq(res, EXIT_SUCCESS);
}

START_TEST(TRM_NULL2) {
  matrix_t test_matrix1;

  s21_remove_matrix(&test_matrix1);
}

END_TEST;

Suite* remove_matrix_suite(void) {
  Suite* suite = suite_create("s21_remove_matrix_test");
  TCase* tc_core = tcase_create("Core`");

  tcase_add_test(tc_core, TRM_NULL);
  suite_add_tcase(suite, tc_core);
  return suite;
}