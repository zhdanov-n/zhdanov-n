#include "s21_matrix_oop.h"

S21Matrix S21Matrix::Transpose() const {
  S21Matrix Transpose(cols_, rows_);
  for (int m = 0; m < cols_; m++) {
    for (int n = 0; n < rows_; n++) {
      Transpose.matrix_[m][n] = matrix_[n][m];
    }
  }
  return Transpose;
}
