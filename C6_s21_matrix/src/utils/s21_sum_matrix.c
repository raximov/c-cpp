#include "./../s21_matrix.h"

int s21_sum_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
  if (is_correct_matrix_t(A) || is_correct_matrix_t(B) ||
      s21_create_matrix(A->rows, A->columns, result))
    return EXIT_FAILURE;
  if (A->rows != B->rows || A->columns != B->columns) return EXIT_CALC_FAILURE;

  for (int row = 0; row < B->rows; row++) {
    for (int col = 0; col < A->columns; col++) {
      result->matrix[row][col] = A->matrix[row][col] + B->matrix[row][col];
    }
  }

  return EXIT_SUCCESS;
}