#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = check_matrix_valid_calc(A, result);
  if (res) return res;
  if (!(res = s21_create_matrix(A->rows, A->columns, result))) {
    if (A->rows > 1) {
      algebraic_complements(A, result);
    } else {
      result->matrix[0][0] = 1.;
    }
  }
  return res;
}
