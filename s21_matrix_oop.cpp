#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  rows_ = 1;
  cols_ = 1;
  allocate_matrix();
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1)
    throw std::logic_error("rows & cols can't be less then 1x1");

  rows_ = rows;
  cols_ = cols;
  allocate_matrix();
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    allocate_matrix();
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr)
    destroy_matrix();
}

void S21Matrix::allocate_matrix() {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
  }
}

void S21Matrix::destroy_matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i)
      delete[] matrix_[i];
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

void S21Matrix::fillMatrix() {
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j)
      matrix_[i][j] = rows_ * i + j + 1;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool result = true;
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_ && result; ++i)
      for (int j = 0; j < cols_ && result; ++j)
        if (matrix_[i][j] != other.matrix_[i][j]) {
          result = false;
        }
  } else
    result = false;
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error("the size of the matrices must match");

  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j)
      matrix_[i][j] += other.matrix_[i][j];
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error("the size of the matrices must match");

  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j)
      matrix_[i][j] -= other.matrix_[i][j];
}

void S21Matrix::MulNumber(double number) {
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j)
      matrix_[i][j] *= number;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (this->cols_ != other.rows_)
    throw std::logic_error(
        "cols of the 1-st matrix must be equal rows of the 2-nd matrix");

  S21Matrix tmp_matrix(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < other.cols_; ++j)
      for (int ii = 0; ii < cols_; ++ii)
        tmp_matrix.matrix_[i][j] += matrix_[i][ii] * other.matrix_[ii][j];

  destroy_matrix();
  matrix_ = tmp_matrix.matrix_;
  rows_ = tmp_matrix.rows_;
  cols_ = tmp_matrix.cols_;
  tmp_matrix.matrix_ = nullptr;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix tmp_matrix(cols_, rows_);
  for (int i = 0; i < cols_; ++i)
    for (int j = 0; j < rows_; ++j)
      tmp_matrix.matrix_[i][j] = matrix_[j][i];
  return tmp_matrix;
}

int S21Matrix::getRows() { return rows_; }
int S21Matrix::getCols() { return cols_; }

void S21Matrix::setRows(int rows) {
  if (rows < 1)
    throw std::logic_error("Rows must be more than 0");

  S21Matrix tmp(rows, cols_);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (i < this->rows_)
        tmp.matrix_[i][j] = this->matrix_[i][j];
      else
        tmp.matrix_[i][j] = 0;
    }
  }
  this->destroy_matrix();
  this->rows_ = rows;
  this->matrix_ = tmp.matrix_;
  tmp.matrix_ = nullptr;
}

void S21Matrix::setCols(int cols) {
  if (cols < 1)
    throw std::logic_error("Cols must be more than 0");

  S21Matrix tmp(rows_, cols);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (j < this->cols_)
        tmp.matrix_[i][j] = this->matrix_[i][j];
      else
        tmp.matrix_[i][j] = 0;
    }
  }
  this->destroy_matrix();
  this->cols_ = cols;
  this->matrix_ = tmp.matrix_;
  tmp.matrix_ = nullptr;
}

S21Matrix S21Matrix::GetMinor(const S21Matrix &other, int row, int col) {
  for (int i = 0; i < row; ++i)
    for (int j = 0; j < col; ++j)
      matrix_[i][j] = other.matrix_[i][j];

  for (int i = 0; i < row; ++i)
    for (int j = col + 1; j < other.cols_; ++j)
      matrix_[i][j - 1] = other.matrix_[i][j];

  for (int i = row + 1; i < other.rows_; ++i)
    for (int j = 0; j < col; ++j)
      matrix_[i - 1][j] = other.matrix_[i][j];

  for (int i = row + 1; i < other.rows_; ++i)
    for (int j = col + 1; j < other.cols_; ++j)
      matrix_[i - 1][j - 1] = other.matrix_[i][j];

  return *this;
}

double S21Matrix::Determinant() {
  double result = 0.0;
  if (rows_ != cols_) {
    throw std::logic_error("Matrix is not square");
  }

  for (int j = 0, sign = 1; j < cols_; j++, sign *= -1) {
    if (rows_ == 1) {
      result = matrix_[0][0];
    } else if (rows_ == 2) {
      result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
    } else {
      S21Matrix tmp(rows_ - 1, cols_ - 1);
      tmp.GetMinor(*this, 0, j);
      result += matrix_[0][j] * sign * tmp.Determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_)
    throw std::logic_error("matrix must be square");

  S21Matrix minor(rows_ - 1, cols_ - 1);
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      minor.GetMinor(*this, i, j);
      int sign = ((i + j) % 2 == 0) ? 1 : -1;
      result.matrix_[i][j] = sign * minor.Determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_)
    throw std::logic_error("matrix must be square");

  double det = this->Determinant();
  if (det == 0)
    throw std::logic_error("determinant must be not equal 0");

  S21Matrix comps = CalcComplements();
  S21Matrix comps_trans(comps.Transpose());
  comps_trans.MulNumber(1 / det);
  S21Matrix result = comps_trans;

  return result;
}

std::istream &operator>>(std::istream &stream, S21Matrix &matrix) {
  for (int i = 0; i < matrix.rows_; ++i) {
    for (int j = 0; j < matrix.cols_; ++j) {
      stream >> matrix.matrix_[i][j];
    }
  }
  return stream;
}

std::ostream &operator<<(std::ostream &stream, const S21Matrix &matrix) {
  for (int i = 0; i < matrix.rows_; ++i) {
    for (int j = 0; j < matrix.cols_; ++j) {
      stream << matrix.matrix_[i][j] << " ";
    }
    stream << "\n";
  }
  return stream;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(double number) {
  S21Matrix result(*this);
  result.MulNumber(number);
  return result;
}

S21Matrix operator*(double number, const S21Matrix &other) {
  S21Matrix result(other);
  result.MulNumber(number);
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) {
  return this->EqMatrix(other);
}

void S21Matrix::operator+=(const S21Matrix &other) { this->SumMatrix(other); }
void S21Matrix::operator-=(const S21Matrix &other) { this->SubMatrix(other); }
void S21Matrix::operator*=(const S21Matrix &other) { this->MulMatrix(other); }
void S21Matrix::operator*=(double number) { this->MulNumber(number); }

S21Matrix S21Matrix::operator=(const S21Matrix &other) {
  this->~S21Matrix();
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->allocate_matrix();
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j)
      this->matrix_[i][j] = other.matrix_[i][j];
  return *this;
}

double &S21Matrix::operator()(int row, int col) {
  if ((0 <= row && row < rows_) && (0 <= col && col < cols_))
    return this->matrix_[row][col];
  else
    throw std::out_of_range("Index out of range");
}
