#ifndef SRC_LIBRARY_S21_MATRIX_OOP_H_
#define SRC_LIBRARY_S21_MATRIX_OOP_H_

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>

class S21Matrix {
 public:
  S21Matrix();
  explicit S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;

  bool EqMatrix(const S21Matrix& other) const noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  double Determinant() const;
  S21Matrix CalcComplements() const;
  S21Matrix InverseMatrix() const;

  friend S21Matrix operator+(S21Matrix A, const S21Matrix& B);
  friend S21Matrix operator-(S21Matrix A, const S21Matrix& B);
  friend S21Matrix operator*(S21Matrix A, const S21Matrix& B);
  friend S21Matrix operator*(S21Matrix A, const double num);
  friend S21Matrix operator*(const double num, S21Matrix A);
  friend bool operator==(const S21Matrix& A, const S21Matrix& B) noexcept;

  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  double& operator()(int row, int col);
  const double& operator()(int row, int col) const;

  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

 private:
  int rows_;
  int cols_;
  double** matrix_;

  void InitializeMatrix();
  void CheckMatrixSize() const;
  void CheckMatrixSize(const S21Matrix& other) const;
  void CopyMatrix(const S21Matrix& other);
  void FreeMatrix();
  void CreateMinorMatrix(const S21Matrix& other, int row, int col);
};

#endif  // SRC_LIBRARY_S21_MATRIX_OOP_H_
