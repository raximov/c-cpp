#include "./../s21_matrix.h"

int s21_mult_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
  int rows = (A->rows > B->rows) ? A->rows : B->rows;
  int columns = (A->columns > B->columns) ? A->columns : B->columns;

  if (is_correct_matrix_t(A) || is_correct_matrix_t(B) ||
      s21_create_matrix(rows, columns, result))
    return EXIT_FAILURE;
  if (A->columns != B->rows || A->rows != B->columns) return EXIT_CALC_FAILURE;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }

  return EXIT_SUCCESS;
}