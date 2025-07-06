#include "../s21_matrix_test.h"

void s21_init_matrix(double number, matrix_t* A) {
  for (int x = 0; x < A->rows; x += 1) {
    for (int y = 0; y < A->columns; number += 1.0, y += 1)
      A->matrix[x][y] = number;
  }
}

START_TEST(determinant_test1) {
  int exit_check;
  int result;

  matrix_t test1 = {0};
  double res = 0;
  double expected_res = 0;

  int row = 3;
  int column = 3;

  s21_create_matrix(row, column, &test1);

  double values1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < column; j++) {
      test1.matrix[i][j] = values1[i][j];
    }
  }

  exit_check = s21_determinant(&test1, &res);

  ck_assert_int_eq(exit_check, EXIT_SUCCESS);
  ck_assert_double_eq_tol(expected_res, res, 1e-6);

  s21_remove_matrix(&test1);
}

START_TEST(determinant_test2) {
  double determ = 0.0;
  matrix_t A = {0};

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 4000.87;
  A.matrix[0][1] = 454.0;
  A.matrix[0][2] = 4.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 1.897;
  A.matrix[1][2] = 3.0;
  A.matrix[2][0] = 0.000087;
  A.matrix[2][1] = 2.5668;
  A.matrix[2][2] = 1.0;

  s21_determinant(&A, &determ);
  s21_remove_matrix(&A);
  ck_assert_double_eq(determ, -24105.996724156);
}

START_TEST(determinant_test3) {
  double determ = 0.0;
  matrix_t A = {0};

  s21_create_matrix(1, 1, &A);
  s21_init_matrix(1.0, &A);

  s21_determinant(&A, &determ);
  s21_remove_matrix(&A);
  ck_assert_double_eq(determ, 1.0);
}

START_TEST(determinant_test4) {
  int res = 0;
  double determ = 0.0;
  matrix_t A = {NULL, 0, 0};

  res = s21_determinant(&A, &determ);
  s21_remove_matrix(&A);
}

START_TEST(determinant_test5) {
  int exit_check;
  int result;

  matrix_t test1 = {0};
  double res = 0;
  double expected_res = -8;

  int row = 2;
  int column = 2;

  s21_create_matrix(row, column, &test1);

  double values1[2][2] = {{1, 2}, {5, 2}};

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < column; j++) {
      test1.matrix[i][j] = values1[i][j];
    }
  }

  exit_check = s21_determinant(&test1, &res);

  ck_assert_int_eq(exit_check, EXIT_SUCCESS);
  ck_assert_double_eq_tol(expected_res, res, 1e-6);

  s21_remove_matrix(&test1);
}

START_TEST(determinant_test6) {
  double determinant = 0.0;
  matrix_t A;
  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 5;
  A.matrix[0][1] = 4;
  A.matrix[0][2] = 13;
  A.matrix[0][3] = 7;

  A.matrix[1][0] = 5;
  A.matrix[1][1] = 10;
  A.matrix[1][2] = 23;
  A.matrix[1][3] = 11;

  A.matrix[2][0] = 13;
  A.matrix[2][1] = 6;
  A.matrix[2][2] = 9;
  A.matrix[2][3] = 8;

  A.matrix[3][0] = 20;
  A.matrix[3][1] = 12;
  A.matrix[3][2] = 4;
  A.matrix[3][3] = 7;

  int res = s21_determinant(&A, &determinant);

  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(determinant, 596, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST;

Suite* determinant_test(void) {
  Suite* suite = suite_create("\ndeterminant_test");
  TCase* tc_core = tcase_create("Core`");

  tcase_add_test(tc_core, determinant_test1);
  tcase_add_test(tc_core, determinant_test2);
  tcase_add_test(tc_core, determinant_test3);
  tcase_add_test(tc_core, determinant_test4);
  tcase_add_test(tc_core, determinant_test5);
  tcase_add_test(tc_core, determinant_test6);

  suite_add_tcase(suite, tc_core);
  return suite;
}