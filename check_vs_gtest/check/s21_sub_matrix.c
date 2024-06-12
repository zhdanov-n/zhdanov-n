#include "s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = check_matrix_valid(A, B, result);
  if (res) return res;
  if (!(res = s21_create_matrix(A->rows, A->columns, result))) {
    for (int m = 0; m < A->rows; m++) {
      for (int n = 0; n < A->columns; n++) {
        result->matrix[m][n] = A->matrix[m][n] - B->matrix[m][n];
      }
    }
  }
  return res;
}
