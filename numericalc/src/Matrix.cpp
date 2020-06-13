/**
 *
 *
 * @file Matrix.cpp
 * Copyright (c) 2020 Peter Grajcar
 */
#include "numericalc/Matrix.hpp"

template <typename T>
Matrix<T> Matrix<T>::operator()(size_t i)
{
    assert(i < rows);
    std::vector<T> row(matrix.begin() + i*cols, matrix.begin() + (i + 1) * cols);
    return Matrix(1, cols, std::move(row));
}

template <typename T>
Matrix<T> Matrix<T>::invertElements() const
{
    Matrix result(rows, cols);
    for(size_t i = 0; i < rows*cols; ++i)
        result.matrix[i] = 1.0 / matrix[i];
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const
{
    Matrix result(cols, rows, matrix);
    if(cols == 1 || rows == 1) return result;
    for(size_t i = 0; i < rows; ++i)
        for(size_t j = 0; j < cols; ++j)
            result.matrix[i *rows + j] = matrix[i*cols + j];
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator-() const
{
    Matrix result(rows, cols);
    for(size_t i = 0; i < rows*cols; ++i)
        result.matrix[i] = -matrix[i];
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &lhs) const
{
    assert(rows == lhs.rows && cols == lhs.cols);
    Matrix result(rows, cols);
    for(size_t i = 0; i < rows*cols; ++i)
        result.matrix[i] = matrix[i] + lhs.matrix[i];
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &lhs) const
{
    assert(rows == lhs.rows && cols == lhs.cols);
    Matrix result(rows, cols);
    for(size_t i = 0; i < rows*cols; ++i)
        result.matrix[i] = matrix[i] - lhs.matrix[i];
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &lhs) const
{
    assert(rows == lhs.cols);
    Matrix result(rows, lhs.cols);
    for(size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < lhs.cols; ++j)
            for (size_t k = 0; k < cols; ++k)
                result.matrix[lhs.cols * i + j] += matrix[cols * i + k] * lhs.matrix[lhs.cols * k + j];
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::function(T f(T)) const
{
    Matrix<T> result(rows, cols);
    for(size_t i = 0; i < rows*cols; ++i)
        result.matrix[i] = f(matrix[i]);
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::function(T f(size_t, size_t, T)) const
{
    Matrix<T> result(rows, cols);
    for(size_t i = 0; i < rows; ++i)
        for(size_t j = 0; j < cols; ++j)
            result.matrix[i*cols + j] = f(i, j, matrix[i*cols + j]);
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::function(T f(size_t, T)) const
{
    assert(rows == cols);
    Matrix<T> result(rows, cols);
    for(size_t i = 0; i < rows; ++i)
            result.matrix[i*cols + i] = f(i, matrix[i*cols + i]);
    return result;
}

template <typename T>
Matrix<T> &Matrix<T>::apply(T f(T))
{
    for(size_t i = 0; i < rows*cols; ++i)
        matrix[i] = f(matrix[i]);
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::apply(T f(size_t, T))
{
    assert(rows == cols);
    for(size_t i = 0; i < rows; ++i)
        matrix[i*cols + i] = f(i, matrix[i*cols + i]);
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::apply(T f(size_t, size_t, T))
{
    assert(rows == cols);
    for(size_t i = 0; i < rows; ++i)
        for(size_t j = 0; j < cols; ++j)
            matrix[i*cols + j] = f(i, j, matrix[i*cols + j]);
    return *this;
}

template class Matrix<double>;
template class Matrix<float>;
template class Matrix<int>;