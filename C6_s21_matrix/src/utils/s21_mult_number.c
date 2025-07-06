#include "./../s21_matrix.h"

int s21_mult_number(matrix_t* A, double number, matrix_t* result) {
  if (is_correct_matrix_t(A) || s21_create_matrix(A->rows, A->columns, result))
    return EXIT_FAILURE;

  for (int row = 0; row < A->rows; row++) {
    for (int col = 0; col < A->columns; col++) {
      result->matrix[row][col] = A->matrix[row][col] * number;
    }
  }

  return EXIT_SUCCESS;
}