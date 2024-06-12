#include "s21_matrix_oop.h"

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::logic_error("Error: Matrix must be square for CalcComplements");
  }
  S21Matrix Cofactor(rows_, cols_);
  if (cols_ == 1) {
    Cofactor(0, 0) = matrix_[0][0];
  } else {
    S21Matrix Submatrix(rows_ - 1, cols_ - 1);
    for (int m = 0; m < rows_; m++) {
      for (int n = 0; n < cols_; n++) {
        Submatrix.CreateMinorMatrix(*this, m, n);
        double minor = Submatrix.Determinant();
        Cofactor(m, n) = ((m + n) % 2 == 0 ? 1. : -1) * minor;
      }
    }
  }
  return Cofactor;
}

void S21Matrix::CreateMinorMatrix(const S21Matrix& other, int row, int col) {
  for (int i = 0, minorRow = 0; i < rows_ + 1; i++) {
    if (row != i) {
      for (int j = 0, minorCol = 0; j < cols_ + 1; j++) {
        if (col != j) {
          this->matrix_[minorRow][minorCol++] = other.matrix_[i][j];
        }
      }
      minorRow++;
    }
  }
}
