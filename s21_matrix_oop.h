#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <iostream>
#include <cstring>
#include <cmath>

class S21Matrix {
   friend S21Matrix operator*(const double, const S21Matrix&);

 private:
    int rows_, cols_;
    double *matrix_;

    S21Matrix CalcMinor(int, int);

 public:
    S21Matrix();
    S21Matrix(int, int);
    S21Matrix(const S21Matrix&);
    S21Matrix(S21Matrix&&);
    ~S21Matrix();

    int getRows();
    int getCols();
    void setRows(int);
    void setCols(int);

    bool EqMatrix(const S21Matrix&);
    void SumMatrix(const S21Matrix&);
    void SubMatrix(const S21Matrix&);
    void MulNumber(const double);
    void MulMatrix(const S21Matrix&);
    S21Matrix Transpose();
    S21Matrix CalcComplements();
    double Determinant();
    S21Matrix InverseMatrix();

    S21Matrix operator+(const S21Matrix&);
    S21Matrix operator-(const S21Matrix&);
    S21Matrix operator*(const double);
    S21Matrix operator*(const S21Matrix&);
    bool operator==(const S21Matrix&);
    S21Matrix& operator=(const S21Matrix&);
    S21Matrix& operator+=(const S21Matrix&);
    S21Matrix& operator-=(const S21Matrix&);
    S21Matrix& operator*=(const double);
    S21Matrix& operator*=(const S21Matrix&);
    double& operator()(int, int);
};

#endif  // SRC_S21_MATRIX_OOP_H_
