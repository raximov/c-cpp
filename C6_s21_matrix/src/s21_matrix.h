#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define CALC_ERR 2
#define EPSILON 1e-7
#define EXIT_CALC_FAILURE 2

typedef struct matrix_struct {
  double** matrix;
  int rows;
  int columns;
} matrix_t;

/// basic
int s21_create_matrix(int rows, int columns, matrix_t* result);
int s21_eq_matrix(matrix_t* A, matrix_t* B);
void s21_remove_matrix(matrix_t* A);

// Adding and subtracting
int s21_sum_matrix(matrix_t* A, matrix_t* B, matrix_t* result);
int s21_sub_matrix(matrix_t* A, matrix_t* B, matrix_t* result);

// Matrix multiplication by scalar
int s21_mult_number(matrix_t* A, double number, matrix_t* result);
int s21_mult_matrix(matrix_t* A, matrix_t* B, matrix_t* result);

// OTHERS
int s21_transpose(matrix_t* A, matrix_t* result);
int s21_calc_complements(matrix_t* A, matrix_t* result);
int s21_determinant(matrix_t* A, double* result);
int s21_inverse_matrix(matrix_t* A, matrix_t* result);

// COMMON.C
void print_matrix(matrix_t* A);
int is_correct_matrix_t(matrix_t* m);
void gauss_step(matrix_t* A, matrix_t* result, int* sign);
void get_minor(const matrix_t* A, int skip_row, int skip_column,
               matrix_t* minor_matrix);

#endif  // S21_MATRIX_H
