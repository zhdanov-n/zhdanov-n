#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int res = check_matrix_valid_determinant(A, result);
  if (res) return res;
  matrix_t copy = {0};
  if (!(res = s21_create_matrix(A->rows, A->columns, &copy))) {
    for (int m = 0; m < copy.rows; m++) {
      for (int n = 0; n < copy.rows; n++) {
        copy.matrix[m][n] = A->matrix[m][n];
      }
    }
    double determinant = 0.0;
    gaussian_elimination(copy.matrix, A->rows, &determinant);
    *result = determinant;
    s21_remove_matrix(&copy);
  }
  return res;
}
