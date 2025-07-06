#include "./../s21_matrix.h"

int s21_determinant(matrix_t* A, double* result) {
  if (is_correct_matrix_t(A) || result == NULL) return EXIT_FAILURE;
  if (A->columns != A->rows) return EXIT_CALC_FAILURE;

  int n = A->rows;
  double det = 1;
  int sign = 1;
  matrix_t gauss_matrix = {0};

  s21_create_matrix(n, n, &gauss_matrix);

  if (n == 1) {
    det = A->matrix[0][0];
  } else {
    gauss_step(A, &gauss_matrix, &sign);

    for (int i = 0; i < n; i++) {
      det = det * gauss_matrix.matrix[i][i];
    }
  }

  s21_remove_matrix(&gauss_matrix);
  *result = det * sign;
  return EXIT_SUCCESS;
}

void gauss_step(matrix_t* A, matrix_t* result, int* sign) {
  int n = A->rows;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      result->matrix[i][j] = A->matrix[i][j];
    }
  }

  for (int i = 0; i < n; i++) {
    if (fabs(result->matrix[i][i]) < 1e-8) {
      for (int j = i + 1; j < n; j++) {
        if (fabs(result->matrix[j][i]) > 1e-8) {
          double* tmp = result->matrix[i];
          result->matrix[i] = result->matrix[j];
          result->matrix[j] = tmp;

          *sign *= -1;

          break;
        }
      }
    }
    for (int j = i + 1; j < n; j++) {
      if (fabs(result->matrix[i][i]) < 1e-8) continue;

      double ratio = result->matrix[j][i] / result->matrix[i][i];
      for (int k = i; k < n; k++) {
        result->matrix[j][k] -= ratio * result->matrix[i][k];
      }
    }
  }
}