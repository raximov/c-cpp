#include "s21_matrix_test.h"

double get_rand_range(double min, double max) {
  return min + ((double)rand() / MATRIX_T_RAND_MAX) * (max - min);
}