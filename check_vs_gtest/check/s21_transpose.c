#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = check_matrix_valid_transpose(A, result);
  if (res) return res;
  if (!(res = s21_create_matrix(A->columns, A->rows, result))) {
    for (int m = 0; m < A->rows; m++) {
      for (int n = 0; n < A->columns; n++) {
        result->matrix[n][m] = A->matrix[m][n];
      }
    }
  }
  return res;
}
