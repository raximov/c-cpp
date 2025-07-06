#include "../s21_matrix_test.h"

START_TEST(transpose_test1) {
  int exit_check;
  int result;

  matrix_t test1 = {0};
  matrix_t res_matrix = {0};
  matrix_t check_matrix = {0};

  int row = 4;
  int column = 4;

  s21_create_matrix(row, column, &test1);
  s21_create_matrix(row, column, &res_matrix);
  s21_create_matrix(column, row, &check_matrix);

  double values1[4][4] = {
      {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < column; j++) {
      test1.matrix[i][j] = values1[i][j];
      check_matrix.matrix[j][i] = values1[i][j];
    }
  }

  exit_check = s21_transpose(&test1, &res_matrix);
  result = s21_eq_matrix(&res_matrix, &check_matrix);

  ck_assert_int_eq(result, 1);

  s21_remove_matrix(&test1);
  s21_remove_matrix(&res_matrix);
}

START_TEST(transpose_test2) {
  int exit_check;
  int result;

  matrix_t test1 = {0};
  matrix_t res_matrix = {0};
  matrix_t check_matrix = {0};

  int row = 3;
  int column = 2;

  s21_create_matrix(row, column, &test1);
  s21_create_matrix(column, row, &res_matrix);
  s21_create_matrix(column, row, &check_matrix);

  double values1[3][2] = {{1, 4}, {2, 5}, {3, 6}};

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < column; j++) {
      test1.matrix[i][j] = values1[i][j];
      check_matrix.matrix[j][i] = values1[i][j];
    }
  }

  exit_check = s21_transpose(&test1, &res_matrix);
  result = s21_eq_matrix(&res_matrix, &check_matrix);

  // print_matrix(&test1);
  // print_matrix(&res_matrix);

  ck_assert_int_eq(result, 1);

  s21_remove_matrix(&test1);
  s21_remove_matrix(&res_matrix);
}

END_TEST;

Suite* transpose_test(void) {
  Suite* suite = suite_create("\ns21_transpose_test");
  TCase* tc_core = tcase_create("Core`");

  tcase_add_test(tc_core, transpose_test1);
  tcase_add_test(tc_core, transpose_test2);
  // tcase_add_test(tc_core, err_sum_matrix_test);
  suite_add_tcase(suite, tc_core);
  return suite;
}