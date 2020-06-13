#ifndef NSMERICALC_MATRIX_HPP
#define NSMERICALC_MATRIX_HPP

#include <cstddef>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>

/**
 * Class representing a matrix.
 *
 * @tparam matrix type
 * Copyright (c) 2020 Peter Grajcar
 */
template <typename T>
class Matrix
{
private:
    size_t rows, cols;
    std::vector<T> matrix;
public:

    /**
     * Constructs a new matrix \f$M \times N\f$.
     *
     * @param m rows
     * @param n columns
     */
    Matrix(size_t m, size_t n) : rows(m), cols(n), matrix(m*n) {}

    /**
     * Constructs a new matrix \f$M \times N\f$ with initial values.
     *
     * @param m rows
     * @param n columns
     * @param src initial values
     */
    Matrix(size_t m, size_t n, T src[]) : rows(m), cols(n), matrix(src, src + m*n) {
        //assert((sizeof(src) / sizeof(src[0])) == m*n);
    }

    /**
     *
     * @param m
     * @param n
     * @param vec
     */
    Matrix(size_t m, size_t n, const std::vector<T> &vec) : rows(m), cols(n), matrix(vec) {};

    /**
     *
     * @param m
     * @param n
     * @param vec
     */
    Matrix(size_t m, size_t n, std::vector<T> &&vec) : rows(m), cols(n), matrix(vec) {};

    /**
     * Creates an identity matrix. Identity matrix is a matrix \f$N*N\f$ with ones on the diagonal.
     *
     * @param n size of the matrix
     * @return identity matrix
     */
    static Matrix identity(size_t n)
    {
        Matrix result(n, n);

        for(size_t i = 0; i < n; ++i)
            result.matrix[i*n + i] = 1;

        return result;
    }

    /**
     * Returns the number of rows in the matrix.
     *
     * @return number of rows
     */
    inline size_t get_rows() const
    {
        return rows;
    }

    /**
     * Returns the number of columns in the matrix.
     *
     * @return number of columns
     */
    inline size_t get_cols() const
    {
        return cols;
    }

    /**
     * Returns element at position i, j.
     *
     * @param i row
     * @param j column
     * @return element at i, j
     */
    inline T & operator()(size_t i, size_t j)
    {
        assert(i < rows && j < cols);
        return matrix[i * cols + j];
    }

    /**
     * Returns element at position i, j.
     *
     * @param i row
     * @param j column
     * @return element at i, j
     */
    inline const T & operator()(size_t i, size_t j) const
    {
        return matrix[i * cols + j];
    }

    explicit operator double()
    {
        assert(rows == 1 && cols == 1);
        return matrix[0];
    }

    /**
     * Returns i-th row of the matrix.
     *
     * @param i row index
     * @return i-th row
     */
    Matrix operator()(size_t i);

    /**
     * Returns i-th row of the matrix.
     *
     * @param i row index
     * @return i-th row
     */
    /*Row operator()(size_t i) const
    {
        assert(i < rows);
        return Row(this, i);
    }*/

    /**
     * Returns matrix with inverted elements. \f$A^\prime\f$ with elements \f$a^\prime_{i,j} = \frac{1}{a_{i,j}}\f$.
     * Not to be misinterpreted as a matrix inverse \f$A^{-1}\f$.
     *
     * @return matrix with inverted elements.
     */
    Matrix invertElements() const;

    /**
     * Transposes the matrix. \f$A^T\f$
     *
     * @return transposed matrix
     */
    Matrix transpose() const;

    /**
     *
     *
     * @return matrix with negated elements.
     */
    Matrix operator-() const;

    /**
     * Matrix addition. For matrices \f$A,B,C \in \mathbb{R}^{M \times N}\f$ the addition \f$C = A + B\f$ is
     * defined as follows \f$c_{ij} = a_{ij} + b_{ij}\f$ for each \f$i,j\f$
     *
     * @param lhs left hand side
     * @return sum
     */
    Matrix operator+(const Matrix &lhs) const;

    /**
     * Matrix subtraction. For matrices \f$A,B,C \in \mathbb{R}^{M \times N}\f$ the addition \f$C = A - B\f$ is
     * defined as follows \f$c_{ij} = a_{ij} - b_{ij}\f$ for each \f$i,j\f$
     *
     * @param lhs left hand side
     * @return difference
     */
    Matrix operator-(const Matrix &lhs) const;

    /**
     * Matrix multiplication in \f$O(n^3)\f$. For matrices
     * \f$A \in \mathbb{R}^{M \times K}, B \in \mathbb{R}^{K \times N},C \in \mathbb{R}^{M \times N}\f$
     * the multiplication \f$C = A \cdot B\f$ is defined as follows
     * \f$c_{ij} = \sum_k a_{ik} - b_{kj}\f$ for each \f$i,j\f$
     *
     * @param lhs left hand side
     * @return product
     */
    Matrix operator*(const Matrix &lhs) const;

    /**
     * Applies function f on each element of the matrix.
     *
     * @param f function
     * @return a new matrix
     */
    Matrix function(T f(T)) const;

    /**
     * Applies function f on each element of the diagonal. The matrix must be square.
     *
     * @param f function
     * @return a new matrix
     */
    Matrix function(T f(size_t, T)) const;

    /**
     * Applies function f on each element of the matrix.
     *
     * @param f function
     * @return a new matrix
     */
    Matrix function(T f(size_t, size_t, T)) const;

    /**
     * Applies function f on each element of the matrix.
     *
     * @param f function
     * @return a new matrix
     */
    Matrix &apply(T f(T));

    /**
     * Applies function f on each element on the diagonal of the square matrix.
     *
     * @param f function
     * @return a new matrix
     */
    Matrix &apply(T f(size_t, T));

    /**
     * Applies function f on each element of the square matrix.
     *
     * @param f function
     * @return a new matrix
     */
    Matrix &apply(T f(size_t, size_t, T));

    /**
     * Matrix multiplication with scalar.
     *
     * @tparam S scalar type
     * @param n scalar
     * @return product
     */
    template <typename S>
    Matrix operator*(S n) const;

    /**
     * Matrix division by scalar.
     *
     * @tparam S scalar type
     * @param n scalar
     * @return quotient
     */
    template <typename S>
    Matrix operator/(S n) const;

    Matrix &operator+=(const Matrix & lhs)
    {
        *this = *this + lhs;
        return *this;
    }

    Matrix &operator-=(const Matrix & lhs)
    {
        *this = *this - lhs;
        return *this;
    }

    Matrix &operator*=(const Matrix & lhs)
    {
        *this = *this * lhs;
        return *this;
    }

    template <typename S>
    Matrix &operator*=(S n)
    {
        *this = *this * n;
        return *this;
    }

    template <typename S>
    Matrix &operator/=(S n)
    {
        *this = *this / n;
        return *this;
    }

    /**
     * Returns reference to vector which represents the matrix in the memory. The element at position i, j
     * is stored at index {@code i * cols + j}.
     *
     * @return reference to the matrix vector
     */
    std::vector<T> &memory()
    {
        return matrix;
    }

    /**
     * Returns reference to vector which represents the matrix in the memory. The element at position i, j
     * is stored at index {@code i * cols + j}.
     *
     * @return reference to the matrix vector
     */
    const std::vector<T> &memory() const
    {
        return matrix;
    }

    /**
     * Prints the matrix to the output stream.
     *
     * @param os output stream
     * @param m matrix
     * @return output stream
     */
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const Matrix<U> &m);

};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &m)
{
    for(size_t i = 0, j = 1; i < m.rows * m.cols; ++i, ++j) {
        os << std::setprecision(4) << std::setw(6) <<  m.matrix[i];
        if(j == m.cols)
        {
            j = 0;
            os << std::endl;
        }
    }
    return os;
}

template <typename T>
template <typename S>
Matrix<T> Matrix<T>::operator*(S n) const
{
    Matrix result(rows, cols);
    for(size_t i = 0; i < rows*cols; ++i)
        result.matrix[i] = n * matrix[i];
    return result;
}

template <typename T>
template <typename S>
Matrix<T> Matrix<T>::operator/(S n) const
{
    Matrix result(rows, cols);
    for(size_t i = 0; i < rows*cols; ++i)
        result.matrix[i] = matrix[i] / n;
    return result;
}

template <typename T, typename S>
Matrix<T> operator*(S n, const Matrix<T> &m)
{
    return m * n;
}

#endif //NSMERICALC_MATRIX_HPP
