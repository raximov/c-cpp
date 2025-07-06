#include "../s21_matrix_test.h"

START_TEST(inverse_matrix_test1) {
  matrix_t test1 = {0};

  int exit_check;

  exit_check = s21_inverse_matrix(&test1, NULL);

  ck_assert_int_eq(exit_check, EXIT_FAILURE);
}

START_TEST(inverse_matrix_test2) {
  int exit_check;
  int result;

  matrix_t test1 = {0};
  matrix_t res_matrix = {0};
  matrix_t expected_matrix = {0};

  int row = 3;
  int column = 3;

  s21_create_matrix(row, column, &test1);
  s21_create_matrix(row, column, &expected_matrix);

  double values1[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};

  double expect_value[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < column; j++) {
      test1.matrix[i][j] = values1[i][j];
      expected_matrix.matrix[i][j] = expect_value[i][j];
    }
  }

  exit_check = s21_inverse_matrix(&test1, &res_matrix);
  result = s21_eq_matrix(&res_matrix, &expected_matrix);

  printf("result:\n");
  print_matrix(&res_matrix);
  // printf("expected_matrix:\n");
  // print_matrix(&expected_matrix);

  ck_assert_int_eq(exit_check, EXIT_SUCCESS);
  ck_assert_int_eq(result, 1);

  s21_remove_matrix(&test1);
  s21_remove_matrix(&res_matrix);
  s21_remove_matrix(&expected_matrix);
}

START_TEST(inverse_matrix_1x1_test3) {
  int exit_check;
  int result = 0;

  matrix_t test1 = {0};
  matrix_t res_matrix = {0};
  matrix_t expected_matrix = {0};

  int row = 1;
  int column = 1;

  s21_create_matrix(row, column, &test1);
  s21_create_matrix(row, column, &expected_matrix);

  double values1[1][1] = {{1}};

  double expect_value[1][1] = {{1}};

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < column; j++) {
      test1.matrix[i][j] = values1[i][j];
      expected_matrix.matrix[i][j] = expect_value[i][j];
    }
  }

  exit_check = s21_inverse_matrix(&test1, &res_matrix);
  result = s21_eq_matrix(&res_matrix, &expected_matrix);

  printf("result:\n");
  print_matrix(&res_matrix);
  printf("expected_matrix:\n");
  print_matrix(&expected_matrix);

  ck_assert_int_eq(exit_check, EXIT_SUCCESS);
  ck_assert_int_eq(result, 1);

  // ==========================_devide_by_zero_=======================================
  s21_remove_matrix(&res_matrix);

  test1.matrix[0][0] = 0;
  expected_matrix.matrix[0][0] = 0;

  exit_check = s21_inverse_matrix(&test1, &res_matrix);
  result = s21_eq_matrix(&res_matrix, &expected_matrix);

  ck_assert_int_eq(exit_check, EXIT_CALC_FAILURE);
  // =================================================================

  s21_remove_matrix(&test1);
  s21_remove_matrix(&res_matrix);
  s21_remove_matrix(&expected_matrix);
}

END_TEST;

Suite* inverse_matrix_test(void) {
  Suite* suite = suite_create("\ncalc_complements_test");
  TCase* tc_core = tcase_create("Core`");

  tcase_add_test(tc_core, inverse_matrix_test1);
  tcase_add_test(tc_core, inverse_matrix_test2);
  tcase_add_test(tc_core, inverse_matrix_1x1_test3);

  suite_add_tcase(suite, tc_core);
  return suite;
}
