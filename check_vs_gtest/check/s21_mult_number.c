#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = check_matrix_valid_mult_number(A, number, result);
  if (res) return res;
  if (!(res = s21_create_matrix(A->rows, A->columns, result))) {
    for (int m = 0; m < A->rows; m++) {
      for (int n = 0; n < A->columns; n++) {
        result->matrix[m][n] = number * A->matrix[m][n];
      }
    }
  }
  return res;
}
