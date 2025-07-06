#include "../s21_matrix_test.h"

START_TEST(TSM) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  int exit_check;
  int result;

  matrix_t test1;
  matrix_t test2;
  matrix_t correct_matrix = {0};
  matrix_t func_result = {0};

  s21_create_matrix(rows, cols, &test1);
  s21_create_matrix(rows, cols, &test2);
  s21_create_matrix(rows, cols, &correct_matrix);

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      test1.matrix[row][col] =
          get_rand_range(MATRIX_T_RAND_MIN, MATRIX_T_RAND_MAX);
      test2.matrix[row][col] =
          get_rand_range(MATRIX_T_RAND_MIN, MATRIX_T_RAND_MAX);
      correct_matrix.matrix[row][col] =
          test1.matrix[row][col] + test2.matrix[row][col];
    }
  }

  exit_check = s21_sum_matrix(&test1, &test2, &func_result);
  result = s21_eq_matrix(&correct_matrix, &func_result);

  ck_assert_int_eq(exit_check, EXIT_SUCCESS);
  ck_assert_int_eq(result, 1);

  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&correct_matrix);
}

START_TEST(err_sum_matrix_test) {
  matrix_t test1;
  matrix_t test2;
  matrix_t correct_matrix = {0};
  matrix_t func_result = {0};
  int res;

  s21_create_matrix(4, 4, &test1);
  s21_create_matrix(4, 4, &test2);
  s21_create_matrix(4, 4, &correct_matrix);

  s21_remove_matrix(&test1);

  res = s21_sum_matrix(&test1, &test2, &func_result);

  ck_assert_int_eq(res, EXIT_FAILURE);

  s21_create_matrix(5, 3, &test1);

  res = s21_sum_matrix(&test1, &test2, &func_result);

  ck_assert_int_eq(res, EXIT_CALC_FAILURE);

  s21_remove_matrix(&correct_matrix);
  s21_remove_matrix(&test2);
}

END_TEST;

Suite* sum_matrix_suite(void) {
  Suite* suite = suite_create("\ns21_sum_matrix_test");
  TCase* tc_core = tcase_create("Core`");

  tcase_add_test(tc_core, TSM);
  tcase_add_test(tc_core, err_sum_matrix_test);
  suite_add_tcase(suite, tc_core);
  return suite;
}