#include <gtest/gtest.h>
#include "s21_matrix_oop.h"

#if defined(__linux__)
    #define IF_LINUX(x) EXPECT_ANY_THROW(x);
#else
    #define IF_LINUX(x) {}
#endif

S21Matrix setFromStatic(const S21Matrix& matrix, const double array[][3], int rows) {
    S21Matrix result(matrix);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < 3; j++)
            result(i, j) = array[i][j];

    return result;
}

TEST(s21_matrix_oop_test, constructor_test) {
    double array[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    S21Matrix matrix;
    matrix = setFromStatic(matrix, array, 3);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(array[i][j], matrix(i, j));

    IF_LINUX(S21Matrix matrix(-1, -1));
}

TEST(s21_matrix_oop_test, constructor_copy_test) {
    double array[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    S21Matrix matrix;
    matrix = setFromStatic(matrix, array, 3);

    S21Matrix newMatrix(matrix);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(array[i][j], newMatrix(i, j));

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(array[i][j], matrix(i, j));
}

TEST(s21_matrix_oop_test, constructor_transition_test) {
    double array[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    S21Matrix matrix1;
    matrix1 = setFromStatic(matrix1, array, 3);

    S21Matrix matrix2(std::move(matrix1));

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(array[i][j], matrix2(i, j));
}

TEST(s21_matrix_oop_test, getters_test) {
    S21Matrix matrix;

    EXPECT_EQ(3, matrix.getCols());
    EXPECT_EQ(3, matrix.getRows());
}

TEST(s21_matrix_oop_test, set_rows_test) {
    double array[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    S21Matrix matrix;
    matrix = setFromStatic(matrix, array, 3);

    matrix.setRows(4);

    EXPECT_EQ(4, matrix.getRows());
    EXPECT_EQ(0, matrix(3, 1));

    IF_LINUX(matrix.setRows(-1));
}

TEST(s21_matrix_oop_test, set_cols_test) {
    double array[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    S21Matrix matrix;
    matrix = setFromStatic(matrix, array, 3);

    matrix.setCols(4);

    EXPECT_EQ(4, matrix.getCols());
    EXPECT_EQ(0, matrix(1, 3));

    IF_LINUX(matrix.setCols(-1));
}

TEST(s21_matrix_oop_test, eq_matrix_test) {
    double array[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    S21Matrix matrix1;
    S21Matrix matrix2;
    matrix1 = setFromStatic(matrix1, array, 3);
    matrix2 = setFromStatic(matrix2, array, 3);

    EXPECT_EQ(true, matrix1.EqMatrix(matrix2));

    matrix2(1, 1) = 0;

    EXPECT_EQ(false, matrix1.EqMatrix(matrix2));

    matrix2.setCols(2);

    EXPECT_EQ(false, matrix1.EqMatrix(matrix2));
}

TEST(s21_matrix_oop_test, sum_matrix_test) {
    double array[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double result[3][3] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
    S21Matrix matrix1;
    S21Matrix matrix2;
    matrix1 = setFromStatic(matrix1, array, 3);
    matrix2 = setFromStatic(matrix2, array, 3);

    matrix1.SumMatrix(matrix2);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(result[i][j], matrix1(i, j));

    matrix1.setCols(2);

    IF_LINUX(matrix1.SumMatrix(matrix2));
}

TEST(s21_matrix_oop_test, sub_matrix_test) {
    double array1[3][3] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
    double array2[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    S21Matrix matrix1;
    S21Matrix matrix2;
    matrix1 = setFromStatic(matrix1, array1, 3);
    matrix2 = setFromStatic(matrix2, array2, 3);

    matrix1.SubMatrix(matrix2);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(array2[i][j], matrix1(i, j));

    matrix1.setCols(2);

    IF_LINUX(matrix1.SubMatrix(matrix2));
}

TEST(s21_matrix_oop_test, mul_number_test) {
    double array[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double result[3][3] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
    S21Matrix matrix;
    matrix = setFromStatic(matrix, array, 3);

    matrix.MulNumber(2);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(result[i][j], matrix(i, j));
}

TEST(s21_matrix_oop_test, mul_matrix_test) {
    double array[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double result[3][3] = {30, 36, 42, 66, 81, 96, 102, 126, 150};
    S21Matrix matrix1;
    S21Matrix matrix2;
    matrix1 = setFromStatic(matrix1, array, 3);
    matrix2 = setFromStatic(matrix2, array, 3);

    matrix1.MulMatrix(matrix2);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(result[i][j], matrix1(i, j));

    matrix1.setCols(2);

    IF_LINUX(matrix1.MulMatrix(matrix2));
}

TEST(s21_matrix_oop_test, transpose_test) {
    double array[2][3] = {1, 2, 3, 4, 5, 6};
    double result[3][2] = {1, 4, 2, 5, 3, 6};
    S21Matrix matrix1;
    S21Matrix matrix2;
    matrix1 = setFromStatic(matrix1, array, 2);

    matrix2 = matrix1.Transpose();

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 2; j++)
            EXPECT_EQ(result[i][j], matrix2(i, j));
}

TEST(s21_matrix_oop_test, determinant_test) {
    double array[3][3] = {1, -2, 3, 4, 0, 6, -7, 8, 9};
    S21Matrix matrix;
    matrix = setFromStatic(matrix, array, 3);

    EXPECT_EQ(204, matrix.Determinant());

    matrix.setCols(2);

    IF_LINUX(matrix.Determinant());

    matrix.setCols(1);
    matrix.setRows(1);

    EXPECT_EQ(1, matrix.Determinant());
}

TEST(s21_matrix_oop_test, calc_complements_test) {
    double array[3][3] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
    double result[3][3] = {0, 10, -20, 4, -14, 8, -8, -2, 4};
    S21Matrix matrix1;
    S21Matrix matrix2;
    matrix1 = setFromStatic(matrix1, array, 3);

    matrix2 = matrix1.CalcComplements();

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(result[i][j], matrix2(i, j));

    matrix1.setCols(2);

    IF_LINUX(matrix1.CalcComplements());
}

TEST(s21_matrix_oop_test, inverse_matrix_test) {
    double array1[3][3] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
    double array2[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double result[3][3] = {1, -1, 1, -38, 41, -34, 27, -29, 24};
    S21Matrix matrix1;
    S21Matrix matrix2;
    matrix1 = setFromStatic(matrix1, array1, 3);

    matrix2 = matrix1.InverseMatrix();

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(result[i][j], matrix2(i, j));

    matrix1 = setFromStatic(matrix1, array2, 3);

    IF_LINUX(matrix1.InverseMatrix());
}

TEST(s21_matrix_oop_test, plus_test) {
    double array[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double result[3][3] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
    S21Matrix matrix1;
    S21Matrix matrix2;
    S21Matrix matrix3;
    matrix1 = setFromStatic(matrix1, array, 3);
    matrix2 = setFromStatic(matrix2, array, 3);

    matrix3 = matrix1 + matrix2;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(result[i][j], matrix3(i, j));
}

TEST(s21_matrix_oop_test, minus_test) {
    double array1[3][3] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
    double array2[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    S21Matrix matrix1;
    S21Matrix matrix2;
    S21Matrix matrix3;
    matrix1 = setFromStatic(matrix1, array1, 3);
    matrix2 = setFromStatic(matrix2, array2, 3);

    matrix3 = matrix1 - matrix2;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(array2[i][j], matrix3(i, j));
}

TEST(s21_matrix_oop_test, asterisk_matrix_number_test) {
    double array[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double result[3][3] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
    S21Matrix matrix1;
    S21Matrix matrix2;
    matrix1 = setFromStatic(matrix1, array, 3);

    matrix2 = matrix1 * 2;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(result[i][j], matrix2(i, j));
}

TEST(s21_matrix_oop_test, asterisk_number_matrix_test) {
    double array[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double result[3][3] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
    S21Matrix matrix1;
    S21Matrix matrix2;
    matrix1 = setFromStatic(matrix1, array, 3);

    matrix2 = 2 * matrix1;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(result[i][j], matrix2(i, j));
}

TEST(s21_matrix_oop_test, asterisk_matrix_test) {
    double array[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double result[3][3] = {30, 36, 42, 66, 81, 96, 102, 126, 150};
    S21Matrix matrix1;
    S21Matrix matrix2;
    S21Matrix matrix3;
    matrix1 = setFromStatic(matrix1, array, 3);
    matrix2 = setFromStatic(matrix2, array, 3);

    matrix3 = matrix1 * matrix2;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(result[i][j], matrix3(i, j));
}

TEST(s21_matrix_oop_test, equals_test) {
    double array[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    S21Matrix matrix1;
    S21Matrix matrix2;
    matrix1 = setFromStatic(matrix1, array, 3);
    matrix2 = setFromStatic(matrix2, array, 3);

    EXPECT_EQ(true, matrix1 == matrix2);

    matrix2(1, 1) = 0;

    EXPECT_EQ(false, matrix1 == matrix2);
}

TEST(s21_matrix_oop_test, assignment_test) {
    double array[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    S21Matrix matrix1;
    S21Matrix matrix2;
    matrix1 = setFromStatic(matrix1, array, 3);

    matrix2 = matrix1;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(array[i][j], matrix2(i, j));

    matrix1 = matrix1;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(array[i][j], matrix1(i, j));
}

TEST(s21_matrix_oop_test, assignment_plus_test) {
    double array[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double result[3][3] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
    S21Matrix matrix1;
    S21Matrix matrix2;
    matrix1 = setFromStatic(matrix1, array, 3);
    matrix2 = setFromStatic(matrix2, array, 3);

    matrix2 += matrix1;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(result[i][j], matrix2(i, j));
}

TEST(s21_matrix_oop_test, assignment_minus_test) {
    double array1[3][3] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
    double array2[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    S21Matrix matrix1;
    S21Matrix matrix2;
    matrix1 = setFromStatic(matrix1, array1, 3);
    matrix2 = setFromStatic(matrix2, array2, 3);

    matrix1 -= matrix2;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(array2[i][j], matrix1(i, j));
}

TEST(s21_matrix_oop_test, assignment_mul_number_test) {
    double array[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double result[3][3] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
    S21Matrix matrix;
    matrix = setFromStatic(matrix, array, 3);

    matrix *= 2;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(result[i][j], matrix(i, j));
}

TEST(s21_matrix_oop_test, assignment_mul_matrix_test) {
    double array[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double result[3][3] = {30, 36, 42, 66, 81, 96, 102, 126, 150};
    S21Matrix matrix1;
    S21Matrix matrix2;
    matrix1 = setFromStatic(matrix1, array, 3);
    matrix2 = setFromStatic(matrix2, array, 3);

    matrix1 *= matrix2;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(result[i][j], matrix1(i, j));
}

TEST(s21_matrix_oop_test, brackets_test) {
    S21Matrix matrix;

    matrix(1, 1) = 5;

    EXPECT_EQ(5, matrix(1, 1));
    IF_LINUX(matrix(-1, 5));
}
