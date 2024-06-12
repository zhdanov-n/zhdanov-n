#include "s21_matrix_oop.h"

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw std::logic_error(
        "Error: Inverse can only be calculated for square matrices.");
  }
  S21Matrix Inverse;
  if (rows_ == 1) {
    if (std::abs(matrix_[0][0]) < 1e-7) {
      throw std::logic_error("Matrix is singular and cannot be inverted.");
    }
    Inverse = S21Matrix(1, 1);
    Inverse(0, 0) = 1.0 / matrix_[0][0];
  } else {
    double det = Determinant();
    if (std::abs(det) < 1e-7) {
      throw std::logic_error("Matrix is singular and cannot be inverted.");
    }
    Inverse = Transpose().CalcComplements() * (1 / det);
  }
  return Inverse;
}
