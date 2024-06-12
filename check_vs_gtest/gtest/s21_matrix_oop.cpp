#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  CheckMatrixSize();
  InitializeMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  CheckMatrixSize();
  InitializeMatrix();
  CopyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = other.matrix_;
  other.rows_ = other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { FreeMatrix(); }

void S21Matrix::InitializeMatrix() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::CheckMatrixSize() const {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::invalid_argument("Error: Invalid dimensions for matrix.");
  }
}

void S21Matrix::CheckMatrixSize(const S21Matrix& other) const {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::invalid_argument("Error: Matrices must have the same size.");
  }
}

void S21Matrix::CopyMatrix(const S21Matrix& other) {
  for (int i = 0; i < rows_ && i < other.rows_; i++) {
    for (int j = 0; j < cols_ && j < other.cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::FreeMatrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  matrix_ = nullptr;
}

int S21Matrix::GetRows() const { return rows_; }
int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows <= 0) {
    throw std::invalid_argument("Error: Invalid dimensions for matrix.");
  }
  S21Matrix temp(rows, cols_);
  temp.CopyMatrix(*this);
  std::swap(*this, temp);
}

void S21Matrix::SetCols(int cols) {
  if (cols <= 0) {
    throw std::invalid_argument("Error: Invalid dimensions for matrix.");
  }
  S21Matrix temp(rows_, cols);
  temp.CopyMatrix(*this);
  std::swap(*this, temp);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    FreeMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    InitializeMatrix();
    CopyMatrix(other);
  }
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix operator+(S21Matrix A, const S21Matrix& B) {
  A += B;
  return A;
}

S21Matrix operator-(S21Matrix A, const S21Matrix& B) {
  A -= B;
  return A;
}

S21Matrix operator*(S21Matrix A, const S21Matrix& B) {
  A *= B;
  return A;
}

S21Matrix operator*(S21Matrix A, const double num) {
  A *= num;
  return A;
}

S21Matrix operator*(const double num, S21Matrix A) {
  A *= num;
  return A;
}

bool operator==(const S21Matrix& A, const S21Matrix& B) noexcept {
  return A.EqMatrix(B);
}

double& S21Matrix::operator()(int row, int col) {
  if (!matrix_ || row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Error: Incorrect indexes of matrix!");
  }
  return matrix_[row][col];
}

const double& S21Matrix::operator()(int row, int col) const {
  if (!matrix_ || row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Error: Incorrect indexes of matrix!");
  }
  return matrix_[row][col];
}
