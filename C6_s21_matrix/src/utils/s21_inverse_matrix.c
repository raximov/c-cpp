#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t* A, matrix_t* result) {
  if (is_correct_matrix_t(A)) return EXIT_FAILURE;
  if (A->columns != A->rows) return EXIT_CALC_FAILURE;

  if (s21_create_matrix(A->rows, A->columns, result)) return EXIT_FAILURE;

  if (A->rows == 1) {
    double element = A->matrix[0][0];
    if (fabs(element) < 1e-7) {
      return EXIT_CALC_FAILURE;
    }
    result->matrix[0][0] = 1.0 / element;
    return EXIT_SUCCESS;
  }

  double det = 0;
  matrix_t complements = {0};
  matrix_t transpose_complements = {0};
  int N = A->rows;
  s21_determinant(A, &det);

  if (!det) {
    return EXIT_CALC_FAILURE;
  }

  s21_calc_complements(A, &complements);
  s21_transpose(&complements, &transpose_complements);

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      result->matrix[i][j] = transpose_complements.matrix[i][j] / det;
    }
  }

  s21_remove_matrix(&complements);
  s21_remove_matrix(&transpose_complements);
  return EXIT_SUCCESS;
}