#include "s21_matrix_oop.h"

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (!matrix_ || !other.matrix_) {
    throw std::runtime_error("Error: Matrix is nullptr.");
  }
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Error: Matrix sizes are incompatible for multiplication.");
  }
  S21Matrix temp = S21Matrix(rows_, other.cols_);
  for (int m1 = 0, m = 0; m1 < temp.rows_; m1++, m++) {
    for (int n2 = 0, n = 0; n2 < temp.cols_; n2++, n++) {
      for (int n1 = 0, m2 = 0; n1 < cols_; n1++, m2++) {
        temp.matrix_[m][n] += matrix_[m1][n1] * other.matrix_[m2][n2];
        if (std::isinf(temp.matrix_[m][n]) || std::isnan(temp.matrix_[m][n])) {
          throw std::runtime_error(
              "Error: Matrix contains Inf or NaN after multiplication.");
        }
      }
    }
  }
  std::swap(*this, temp);
}
