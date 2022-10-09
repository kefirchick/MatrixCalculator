#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix::S21Matrix(3, 3) {}

S21Matrix::S21Matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0)
        throw std::out_of_range(
            "Incorrect input, indexes should not be negative");

    rows_ = rows, cols_ = cols;
    matrix_ = new double[rows_ * cols_]();
}

S21Matrix::S21Matrix(const S21Matrix& other) : matrix_{nullptr} {
    *this = other;
}

S21Matrix::S21Matrix(S21Matrix&& other) : rows_{0}, cols_{0}, matrix_{nullptr} {
    if (this != &other) {
        std::swap(this->matrix_, other.matrix_);
        std::swap(rows_, other.rows_);
        std::swap(cols_, other.cols_);
    }
}

S21Matrix::~S21Matrix() {
    rows_ = 0;
    cols_ = 0;

    if (matrix_) delete[] matrix_;
    matrix_ = nullptr;
}

int S21Matrix::getRows() {
    return rows_;
}

int S21Matrix::getCols() {
    return cols_;
}

void S21Matrix::setRows(int num) {
    if (num <= 0)
        throw std::out_of_range(
            "Incorrect input, rows number should not be negative");

    S21Matrix temp(*this);

    if (matrix_) delete[] matrix_;

    matrix_ = new double[num * cols_]();
    int min = (rows_ < num) ? rows_ : num;
    rows_ = num;

    for (auto i = 0; i < min; i++) {
        for (auto j = 0; j < cols_; j++) {
            matrix_[i * cols_ + j] = temp(i, j);
        }
    }
}

void S21Matrix::setCols(int num) {
    if (num <= 0)
        throw std::out_of_range(
            "Incorrect input, columns number should not be negative");

    S21Matrix temp(*this);

    if (matrix_) delete[] matrix_;

    matrix_ = new double[rows_ * num]();
    int min = (cols_ < num) ? cols_ : num;
    cols_ = num;

    for (auto i = 0; i < rows_; i++) {
        for (auto j = 0; j < min; j++) {
            matrix_[i * num + j] = temp(i, j);
        }
    }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        return false;
    }

    for (auto i = 0; i < rows_ * cols_; i++) {
        if (matrix_[i] != other.matrix_[i]) return false;
    }

    return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_)
        throw std::out_of_range(
            "Incorrect input, matrices should have the same size");

    for (auto i = 0; i < rows_ * cols_; i++) {
        matrix_[i] = matrix_[i] + other.matrix_[i];
    }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_)
        throw std::out_of_range(
            "Incorrect input, matrices should have the same size");

    for (auto i = 0; i < rows_ * cols_; i++) {
        matrix_[i] = matrix_[i] - other.matrix_[i];
    }
}

void S21Matrix::MulNumber(const double num) {
    for (auto i = 0; i < rows_ * cols_; i++) {
        matrix_[i] *= num;
    }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
    if (cols_ != other.rows_)
        throw std::invalid_argument(
            "First matrix columns number should equals second matrix rows number");

    S21Matrix result(rows_, other.cols_);

    for (auto i = 0; i < rows_; i++)
        for (auto j = 0; j < other.cols_; j++)
            for (auto k = 0; k < cols_; k++)
                result(i, j) += matrix_[i * cols_ + k] * other.matrix_[k * other.cols_ + j];

    *this = result;
}

S21Matrix S21Matrix::Transpose() {
    S21Matrix result(cols_, rows_);

    for (auto i = 0; i < rows_; i++)
        for (auto j = 0; j < cols_; j++)
            result(j, i) = matrix_[i * cols_ + j];

    return result;
}

S21Matrix S21Matrix::CalcMinor(int row, int col) {
    S21Matrix minor(cols_ - 1, rows_ - 1);

    int i_min = -1;
    for (auto i = 0; i < rows_; i++) {
        if (i != row) i_min++;
        int j_min = -1;
        for (auto j = 0; j < cols_; j++) {
            if (j != col) j_min++;
            if (i != row && j != col) minor(i_min, j_min) = matrix_[i * cols_ + j];
        }
    }

    return minor;
}

double S21Matrix::Determinant() {
    if (cols_ != rows_ || cols_ == 0)
        throw std::invalid_argument(
            "Can't calculate determinant, matrix shoud be a square matrix and not empty");

    double result = 0;

    if (rows_ == 1) {
        result = matrix_[0];
    } else if (rows_ == 2) {
        result = matrix_[0] * matrix_[3] - matrix_[1] * matrix_[2];
    } else {
        for (auto i = 0; i < rows_; i++) {
            S21Matrix minor(CalcMinor(i, 0));
            double complement = minor.Determinant() * pow(-1, i);
            result += matrix_[i * rows_] * complement;
        }
    }

    return result;
}

S21Matrix S21Matrix::CalcComplements() {
    if (cols_ != rows_ || cols_ == 0)
        throw std::invalid_argument(
            "Can't calculate complements, matrix shoud be a square matrix and not empty");

    S21Matrix complements(rows_, cols_);

    for (auto i = 0; i < rows_; i++) {
        for (auto j = 0; j < cols_; j++) {
            S21Matrix minor(CalcMinor(i, j));
            complements(i, j) = minor.Determinant() * pow(-1, i + j);
        }
    }

    return complements;
}

S21Matrix S21Matrix::InverseMatrix() {
    if (Determinant() == 0)
        throw std::invalid_argument(
            "Can't calculate inverse matrix with zero determinant");

    S21Matrix complements(CalcComplements());
    S21Matrix result(complements.Transpose());
    result *= -1;

    return result;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
    S21Matrix result(*this);
    result.SumMatrix(other);

    return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
    S21Matrix result(*this);
    result.SubMatrix(other);

    return result;
}

S21Matrix S21Matrix::operator*(const double num) {
    S21Matrix result(*this);
    result.MulNumber(num);

    return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
    S21Matrix result(*this);
    result.MulMatrix(other);

    return result;
}

S21Matrix operator*(const double num, const S21Matrix& other) {
    S21Matrix result(other);
    return result * num;
}

bool S21Matrix::operator==(const S21Matrix& other) {
    return EqMatrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
    if (this == &other) return *this;

    rows_ = other.rows_;
    cols_ = other.cols_;

    if (matrix_) delete[] matrix_;

    matrix_ = new double[other.rows_ * other.cols_]();
    std::memcpy(matrix_, other.matrix_, other.rows_ * other.cols_ * sizeof(double));

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

S21Matrix& S21Matrix::operator*=(const double num) {
    MulNumber(num);

    return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
    MulMatrix(other);

    return *this;
}

double& S21Matrix::operator()(int row, int col) {
    if (row >= rows_ || row < 0 || col >= cols_ || col < 0)
        throw std::out_of_range("Incorrect input, index is out of range");

    return matrix_[row * cols_ + col];
}
