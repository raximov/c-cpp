#include "./../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t* result) {
  if (rows < 1 || columns < 1) return EXIT_CALC_FAILURE;
  if (result == NULL) return EXIT_FAILURE;

  result->rows = rows;
  result->columns = columns;
  result->matrix = (double**)malloc(rows * sizeof(double*));

  if (result->matrix == NULL) return EXIT_FAILURE;

  for (int i = 0; i < rows; i++) {
    result->matrix[i] = calloc(columns, sizeof(double));

    if (!result->matrix[i]) {
      //   for (int j = i; 0 <= j; j--) free(result->matrix[j]);
      //   free(result->matrix);
      //   result->matrix = NULL;
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}