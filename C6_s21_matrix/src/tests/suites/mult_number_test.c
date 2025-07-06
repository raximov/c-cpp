#include "../s21_matrix_test.h"

START_TEST(mul_num_test) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  double mul_num = get_rand_range(-1000, 1000) / (rand() % 100 + 1);
  int exit_check;
  int result;

  matrix_t test1 = {0};
  matrix_t correct_matrix = {0};
  matrix_t func_result = {0};

  s21_create_matrix(rows, cols, &test1);
  s21_create_matrix(rows, cols, &correct_matrix);

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      test1.matrix[row][col] =
          get_rand_range(MATRIX_T_RAND_MIN, MATRIX_T_RAND_MAX);
      correct_matrix.matrix[row][col] = test1.matrix[row][col] * mul_num;
    }
  }

  exit_check = s21_mult_number(&test1, mul_num, &func_result);
  result = s21_eq_matrix(&correct_matrix, &func_result);

  ck_assert_int_eq(exit_check, EXIT_SUCCESS);
  ck_assert_int_eq(result, 1);

  s21_remove_matrix(&test1);
  s21_remove_matrix(&correct_matrix);
  s21_remove_matrix(&func_result);
}

START_TEST(err_mul_num_test) {
  matrix_t test1 = {0};
  matrix_t func_result = {0};
  double mul_number = 3;
  int res;

  res = s21_mult_number(&test1, mul_number, &func_result);

  ck_assert_int_eq(res, EXIT_FAILURE);

  s21_remove_matrix(&test1);
}

END_TEST;

Suite* mul_num_matrix_suite(void) {
  Suite* suite = suite_create("\ns21_mult_number");
  TCase* tc_core = tcase_create("Core`");

  tcase_add_test(tc_core, mul_num_test);
  tcase_add_test(tc_core, err_mul_num_test);
  suite_add_tcase(suite, tc_core);
  return suite;
}