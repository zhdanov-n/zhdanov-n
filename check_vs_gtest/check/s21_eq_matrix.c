#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (is_matrix_null(A) || is_matrix_null(B) || unequal_matrix_sizes(A, B))
    return FAILURE;
  int result = SUCCESS;
  for (int m = 0; m < A->rows; m++) {
    for (int n = 0; n < A->columns; n++) {
      if (fabs(A->matrix[m][n] - B->matrix[m][n]) > 1e-7) {
        result = FAILURE;
        n = A->columns;
        m = A->rows;
      }
    }
  }
  return result;
}
