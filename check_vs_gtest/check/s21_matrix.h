#ifndef S21_MATRIX
#define S21_MATRIX

#include <math.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

#define S21_IS_INF __builtin_isinf
#define S21_IS_NAN __builtin_isnan

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

enum { OK, INCORRECT_MATRIX, CALCULATION_ERROR };

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

int is_matrix_null(matrix_t *A);
int invalid_matrix_size(int rows, int columns);
int unequal_matrix_sizes(matrix_t *A, matrix_t *B);
int check_matrix_valid(matrix_t *A, matrix_t *B, matrix_t *result);
int check_matrix_valid_transpose(matrix_t *A, matrix_t *result);
int check_matrix_valid_determinant(matrix_t *A, double *result);
int check_matrix_valid_calc(matrix_t *A, matrix_t *result);
int check_matrix_valid_mult_number(matrix_t *A, double number,
                                   matrix_t *result);
int check_matrix_valid_mult(matrix_t *A, matrix_t *B, matrix_t *result);
int check_inf_or_nan(matrix_t *A);
void swap_rows(double **matrix, int row1, int row2);
void gaussian_elimination(double **matrix, int size, double *det);
void algebraic_complements(matrix_t *A, matrix_t *result);
void create_submatrix(matrix_t *src, matrix_t *submatrix, int row_exclude,
                      int col_exclude);
double calculate_minor(matrix_t *src, int row_index, int col_index);

#endif  // SRC_S21_MATRIX_H_
