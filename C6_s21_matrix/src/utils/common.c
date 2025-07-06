#include "../s21_matrix.h"

void print_matrix(matrix_t* A) {
  if (!A->matrix) return;

  printf("======================\n");
  for (int i = 0; i < A->rows; i++) {
    if (A->matrix[i] == NULL) return;
    for (int j = 0; j < A->columns; j++) {
      printf("%g ", A->matrix[i][j]);
    }
    printf("\n");
  }
  printf("======================\n");
}

int is_correct_matrix_t(matrix_t* m) {
  if (m->matrix == NULL || m->rows < 1 || m->columns < 1) return EXIT_FAILURE;
  for (int i = 0; i < m->rows; i++) {
    if (m->matrix[i] == NULL) return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}