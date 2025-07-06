#ifndef TEST_H
#define TEST_H

#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_matrix.h"

#define MATRIX_T_RAND_MIN -1e6
#define MATRIX_T_RAND_MAX 1e6

Suite* create_matrix_suite(void);
Suite* eq_matrix_suite(void);
Suite* remove_matrix_suite(void);
Suite* sum_matrix_suite(void);
Suite* sub_matrix_suite(void);
Suite* mul_num_matrix_suite(void);
Suite* mul_matrix_suite(void);
Suite* transpose_test(void);
Suite* calc_complements_test(void);
Suite* determinant_test(void);
Suite* inverse_matrix_test(void);

// helpers
double get_rand_range(double min, double max);
#endif
