#include "s21_matrix.h"

int is_matrix_null(matrix_t *A) { return A == NULL; }

int invalid_matrix_size(int rows, int columns) {
  return rows <= 0 || columns <= 0;
}

int unequal_matrix_sizes(matrix_t *A, matrix_t *B) {
  return A->rows != B->rows || A->columns != B->columns;
}

int check_matrix_valid(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (is_matrix_null(A) || is_matrix_null(B) || is_matrix_null(result)) {
    res = INCORRECT_MATRIX;
  } else if (unequal_matrix_sizes(A, B) || check_inf_or_nan(A) ||
             check_inf_or_nan(B)) {
    res = CALCULATION_ERROR;
  }
  return res;
}

int check_matrix_valid_transpose(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (is_matrix_null(A) || is_matrix_null(result)) res = INCORRECT_MATRIX;
  return res;
}

int check_matrix_valid_determinant(matrix_t *A, double *result) {
  int res = OK;
  if (is_matrix_null(A) || result == NULL) {
    res = INCORRECT_MATRIX;
  } else if (A->rows != A->columns || check_inf_or_nan(A)) {
    res = CALCULATION_ERROR;
  }
  return res;
}

int check_matrix_valid_calc(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (is_matrix_null(A) || is_matrix_null(result)) {
    res = INCORRECT_MATRIX;
  } else if (A->rows != A->columns || check_inf_or_nan(A)) {
    res = CALCULATION_ERROR;
  }
  return res;
}

int check_matrix_valid_mult_number(matrix_t *A, double number,
                                   matrix_t *result) {
  int res = OK;
  if (is_matrix_null(A) || is_matrix_null(result)) {
    res = INCORRECT_MATRIX;
  } else if (check_inf_or_nan(A) || S21_IS_INF(number) || S21_IS_NAN(number)) {
    res = CALCULATION_ERROR;
  }
  return res;
}

int check_matrix_valid_mult(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (is_matrix_null(A) || is_matrix_null(B) || is_matrix_null(result) ||
      B->rows <= 0 || A->columns <= 0) {
    res = INCORRECT_MATRIX;
  } else if (A->columns != B->rows || check_inf_or_nan(A) ||
             check_inf_or_nan(B)) {
    res = CALCULATION_ERROR;
  }
  return res;
}

int check_inf_or_nan(matrix_t *A) {
  int result = OK;
  for (int m = 0; m < A->rows; m++) {
    for (int n = 0; n < A->columns; n++) {
      if (S21_IS_INF(A->matrix[m][n]) || S21_IS_NAN(A->matrix[m][n])) {
        result = CALCULATION_ERROR;
        n = A->columns;
        m = A->rows;
      }
    }
  }
  return result;
}

void swap_rows(double **matrix, int row1, int row2) {
  double *temp = matrix[row1];
  matrix[row1] = matrix[row2];
  matrix[row2] = temp;
}

void gaussian_elimination(double **matrix, int size, double *det) {
  *det = 1.0;
  int i, j = 0;
  for (i = 0; i < size; i++) {
    // Check if diagonal element is zero
    if (matrix[i][i] == 0.0) {
      // Find a row below with non-zero element and swap
      for (j = i + 1; j < size; j++) {
        if (matrix[j][i] != 0.0) {
          swap_rows(matrix, i, j);
          *det *= -1.0;  // Swapping rows changes the sign of determinant
          break;
        }
      }
      if (j == size) {
        *det = 0.0;  // If no non-zero element found, determinant is zero
        break;
      }
    }
    *det *= matrix[i][i];  // Multiply determinant by diagonal element
    for (int k = i + 1; k < size; k++) {
      double factor =
          matrix[k][i] /
          matrix[i][i];  // Calculating the factor needed for elimination
      for (int l = i; l < size; l++) {
        matrix[k][l] -= factor * matrix[i][l];  // Row reduction below diagonal
      }
    }
  }
}

double calculate_minor(matrix_t *src, int row_index, int col_index) {
  matrix_t submatrix = {0};
  create_submatrix(src, &submatrix, row_index, col_index);
  double minor_det = 0.0;
  s21_determinant(&submatrix, &minor_det);
  s21_remove_matrix(&submatrix);
  return minor_det;
}

void create_submatrix(matrix_t *src, matrix_t *submatrix, int row_exclude,
                      int col_exclude) {
  int sub_rows = src->rows - 1;
  int sub_cols = src->columns - 1;
  s21_create_matrix(sub_rows, sub_cols, submatrix);
  int sub_row = 0, sub_col = 0;
  for (int i = 0; i < src->rows; i++) {
    if (i != row_exclude) {
      sub_col = 0;
      for (int j = 0; j < src->columns; j++) {
        if (j != col_exclude) {
          submatrix->matrix[sub_row][sub_col] = src->matrix[i][j];
          sub_col++;
        }
      }
      sub_row++;
    }
  }
}

void algebraic_complements(matrix_t *A, matrix_t *result) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      double minor = calculate_minor(A, i, j);
      if ((i + j) % 2 == 1) {
        minor *= -1.0;
      }
      result->matrix[i][j] = minor;
    }
  }
}
