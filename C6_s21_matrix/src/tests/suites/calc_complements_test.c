#include "../s21_matrix_test.h"

START_TEST(calc_comp_test1) {
  matrix_t test1 = {0};

  int exit_check;

  exit_check = s21_calc_complements(&test1, NULL);

  ck_assert_int_eq(exit_check, EXIT_FAILURE);
}

START_TEST(calc_comp_test2) {
  int exit_check;
  int result;

  matrix_t test1 = {0};
  matrix_t res_matrix = {0};
  matrix_t expected_matrix = {0};

  int row = 3;
  int column = 3;

  s21_create_matrix(row, column, &test1);
  s21_create_matrix(column, row, &expected_matrix);

  double values1[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};

  double expect_value[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < column; j++) {
      test1.matrix[i][j] = values1[i][j];
      expected_matrix.matrix[i][j] = expect_value[i][j];
    }
  }

  exit_check = s21_calc_complements(&test1, &res_matrix);

  ck_assert_int_eq(exit_check, EXIT_SUCCESS);

  result = s21_eq_matrix(&res_matrix, &expected_matrix);
  ck_assert_int_eq(result, 1);

  s21_remove_matrix(&test1);
  s21_remove_matrix(&res_matrix);
  s21_remove_matrix(&expected_matrix);
}

START_TEST(calc_comp_test3) {
  int exit_check;
  int result;

  matrix_t test1 = {0};
  matrix_t res_matrix = {0};
  matrix_t check_matrix = {0};

  int row = 4;
  int column = 4;

  s21_create_matrix(row, column, &test1);
  s21_create_matrix(column, row, &check_matrix);

  double values1[4][4] = {
      {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

  exit_check = s21_calc_complements(&test1, &res_matrix);
  result = s21_eq_matrix(&res_matrix, &check_matrix);

  ck_assert_int_eq(result, 1);

  s21_remove_matrix(&test1);
  s21_remove_matrix(&res_matrix);
  s21_remove_matrix(&check_matrix);
}

START_TEST(calc_comp_test4) {
  matrix_t expected = {0};
  matrix_t m = {0};
  matrix_t result = {0};
  int code1 = s21_create_matrix(3, 3, &m);
  int code2 = s21_create_matrix(3, 3, &expected);
  m.matrix[0][0] = 1;
  m.matrix[0][1] = 2;
  m.matrix[0][2] = 3;

  m.matrix[1][0] = 0;
  m.matrix[1][1] = 4;
  m.matrix[1][2] = 2;

  m.matrix[2][0] = 5;
  m.matrix[2][1] = 2;
  m.matrix[2][2] = 1;

  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = -20;

  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = -14;
  expected.matrix[1][2] = 8;

  expected.matrix[2][0] = -8;
  expected.matrix[2][1] = -2;
  expected.matrix[2][2] = 4;

  int code = s21_calc_complements(&m, &result);

  ck_assert_int_eq(s21_eq_matrix(&result, &expected), 1);
  ck_assert_int_eq(code, EXIT_SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}

START_TEST(calc_complements_zero_4x4) {
  matrix_t matrix1 = {0}, result_check = {0}, matrix_before = {0}, result = {0};

  s21_create_matrix(4, 4, &matrix1);
  s21_create_matrix(4, 4, &result_check);
  s21_create_matrix(4, 4, &matrix_before);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      result_check.matrix[i][j] = 0.0;
    }
  }

  double values[4][4] = {
      {1, 5, 9, 13}, {2, 6, 10, 14}, {3, 7, 11, 15}, {4, 8, 12, 16}};

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      matrix1.matrix[i][j] = values[i][j];
      matrix_before.matrix[i][j] = values[i][j];
    }

  int status = s21_calc_complements(&matrix1, &result);

  ck_assert_int_eq(status, 0);

  ck_assert_int_eq(s21_eq_matrix(&result, &result_check), 1);

  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix_before), 1);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result_check);
  s21_remove_matrix(&matrix_before);
  s21_remove_matrix(&result);
}

END_TEST;

Suite* calc_complements_test(void) {
  Suite* suite = suite_create("\ncalc_complements_test");
  TCase* tc_core = tcase_create("Core`");

  tcase_add_test(tc_core, calc_comp_test1);
  tcase_add_test(tc_core, calc_comp_test2);
  tcase_add_test(tc_core, calc_comp_test3);
  tcase_add_test(tc_core, calc_comp_test4);
  tcase_add_test(tc_core, calc_complements_zero_4x4);

  suite_add_tcase(suite, tc_core);
  return suite;
}
