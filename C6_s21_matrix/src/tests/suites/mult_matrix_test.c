#include "../s21_matrix_test.h"

START_TEST(mult_matrix_test) {
  int rows = 4;
  int cols = 4;
  int exit_check;
  int result;

  matrix_t test1 = {0};
  matrix_t test2 = {0};
  matrix_t correct_matrix = {0};
  matrix_t func_result = {0};

  s21_create_matrix(rows, cols, &test1);
  s21_create_matrix(rows, cols, &test2);
  s21_create_matrix(rows, cols, &correct_matrix);

  double values_restul[4][4] = {{90, 100, 110, 120},
                                {202, 228, 254, 280},
                                {314, 356, 398, 440},
                                {426, 484, 542, 600}};

  double values1[4][4] = {
      {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

  double values2[4][4] = {
      {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      test1.matrix[i][j] = values1[i][j];
      test2.matrix[i][j] = values2[i][j];
      correct_matrix.matrix[i][j] = values_restul[i][j];
    }
  }

  exit_check = s21_mult_matrix(&test1, &test2, &func_result);
  result = s21_eq_matrix(&correct_matrix, &func_result);

  ck_assert_int_eq(exit_check, EXIT_SUCCESS);
  ck_assert_int_eq(result, 1);

  s21_remove_matrix(&test1);
  s21_remove_matrix(&correct_matrix);
  s21_remove_matrix(&test2);
}

START_TEST(err_mult_matrix_test) {
  int exit_check;
  int result;
  matrix_t test1 = {0};
  matrix_t test2 = {0};
  matrix_t correct_matrix = {0};
  matrix_t func_result = {0};

  exit_check = s21_mult_matrix(&test1, &test2, &func_result);
  result = s21_eq_matrix(&correct_matrix, &func_result);

  ck_assert_int_eq(exit_check, EXIT_FAILURE);
}

END_TEST

Suite* mul_matrix_suite(void) {
  Suite* suite = suite_create("\n s21_mult_matrix_test");
  TCase* tc_core = tcase_create("Core`");

  tcase_add_test(tc_core, mult_matrix_test);
  tcase_add_test(tc_core, err_mult_matrix_test);
  suite_add_tcase(suite, tc_core);
  return suite;
}