#include "./../s21_matrix.h"

int s21_transpose(matrix_t* A, matrix_t* result) {
  if (is_correct_matrix_t(A) || s21_create_matrix(A->columns, A->rows, result))
    return EXIT_FAILURE;

  for (int row = 0; row < A->rows; row++) {
    for (int col = 0; col < A->columns; col++) {
      result->matrix[col][row] = A->matrix[row][col];
    }
  }

  return EXIT_SUCCESS;
}