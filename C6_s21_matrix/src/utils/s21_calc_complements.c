#include "./../s21_matrix.h"

int s21_calc_complements(matrix_t* A, matrix_t* result) {
  if (is_correct_matrix_t(A)) return EXIT_FAILURE;
  if (A->columns != A->rows || A->rows == 1) return EXIT_CALC_FAILURE;

  if (s21_create_matrix(A->rows, A->columns, result)) return EXIT_FAILURE;

  int sign = 1;
  int n = A->rows;
  matrix_t minor_matrix = {0};

  if (s21_create_matrix(n - 1, n - 1, &minor_matrix)) return EXIT_FAILURE;

  for (int r = 0; r < n; r++) {
    for (int c = 0; c < n; c++) {
      get_minor(A, r, c, &minor_matrix);
      s21_determinant(&minor_matrix, &result->matrix[r][c]);
      result->matrix[r][c] *= pow(-1, r + c);
    }
  }

  s21_remove_matrix(&minor_matrix);
  return EXIT_SUCCESS;
}

void get_minor(const matrix_t* A, int skip_row, int skip_column,
               matrix_t* minor_matrix) {
  int n = A->rows;
  int row_shift = 0, column_shift = 0;

  for (int i = 0; i < n; i++) {
    if (i == skip_row) {
      if (!row_shift) row_shift = 1;
      continue;
    }
    for (int j = 0; j < n; j++) {
      if (j == skip_column) {
        if (!column_shift) column_shift = 1;
        continue;
      }
      minor_matrix->matrix[i - row_shift][j - column_shift] = A->matrix[i][j];
    }
    column_shift--;
  }
}