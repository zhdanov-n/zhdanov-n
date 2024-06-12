#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = check_matrix_valid_calc(A, result);
  if (res) return res;
  double det = 0;
  s21_determinant(A, &det);
  if (!det) {
    res = CALCULATION_ERROR;
  } else {
    matrix_t calc = {0};
    matrix_t transpose = {0};
    s21_calc_complements(A, &calc);
    s21_transpose(&calc, &transpose);
    det = 1 / det;
    s21_mult_number(&transpose, det, result);
    s21_remove_matrix(&calc);
    s21_remove_matrix(&transpose);
  }
  return res;
}
