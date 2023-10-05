#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <iostream>

class S21Matrix {

private:
  int rows_;
  int cols_;
  double **matrix_ = nullptr;
  void allocate_matrix();
  void destroy_matrix();

public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  bool EqMatrix(const S21Matrix &other);

  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(double number);
  void MulMatrix(const S21Matrix &other);

  S21Matrix GetMinor(const S21Matrix &other, int row, int col);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();

  double Determinant();

  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator=(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(double number);
  friend S21Matrix operator*(double number, const S21Matrix &other);

  int getRows();
  int getCols();

  void setRows(int rows);
  void setCols(int cols);

  void fillMatrix();

  bool operator==(const S21Matrix &other);

  void operator+=(const S21Matrix &other);
  void operator-=(const S21Matrix &other);
  void operator*=(const S21Matrix &other);
  void operator*=(double number);

  double &operator()(int row, int col);

  friend std::istream &operator>>(std::istream &stream, S21Matrix &matrix);
  friend std::ostream &operator<<(std::ostream &stream,
                                  const S21Matrix &matrix);

  friend std::ifstream &operator>>(std::ifstream &fstream, S21Matrix &matrix);
};

#endif
