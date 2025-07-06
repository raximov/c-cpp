#include "../s21_matrix.h"

#define SUCCESS 1
#define FAILURE 0

int s21_eq_matrix(matrix_t* A, matrix_t* B) {
  if (A->rows != B->rows || A->columns != B->columns ||
      is_correct_matrix_t(A) || is_correct_matrix_t(B))
    return FAILURE;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= EPSILON) return FAILURE;
    }
  }
  return SUCCESS;
}