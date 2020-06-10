#ifndef NSMERICALC_MATRIX_HPP
#define NSMERICALC_MATRIX_HPP

#include <cstddef>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>

/**
 * Class representing a matrix.
 */
template <typename T>
class Matrix
{
private:
    /**
     * Class representing i-th row of the matrix.
     */
    class Row {
        friend class Matrix;
    private:
        Matrix *matrixRef;
        size_t i;
        Row(Matrix &matrix, size_t i) : matrixRef(&matrix), i(i) {}

    public:
        /**
         * Returns row as a matrix \f$1 \times M\f$.
         *
         * @return
         */
        Matrix asMatrix()
        {
            std::vector<T> row(matrixRef->matrix.begin() + i*matrixRef->cols, matrixRef->matrix.begin() + (i + 1) * matrixRef->cols);
            return Matrix(1, matrixRef->cols, std::move(row));
        }

        /**
         * Returns j-th element of the row
         *
         * @param j index
         * @return j-th element
         */
        inline T &operator()(size_t j)
        {
            return matrixRef->matrix[i * matrixRef->cols + j];
        }

        /**
         * Returns j-th element of the row
         *
         * @param j index
         * @return j-th element
         */
        inline const T &operator()(size_t j) const
        {
            return matrixRef->matrix[i * matrixRef->cols + j];
        }

        /**
         * Adds a multiple of one row to other.
         *
         * @tparam S scalar type
         * @param lhs row to be added
         * @param n multiple
         */
        template<typename S>
        void add_multiple(const Row &lhs, S n)
        {
            assert(matrixRef == lhs.matrixRef);
            size_t cols = matrixRef->cols;
            for(size_t j = 0; j < cols; ++j)
                matrixRef->matrix[i * cols + j] += n * lhs.matrixRef->matrix[i * cols + j];
        }

        /**
         * Swaps rows a and b.
         *
         * @param a first row
         * @param b second row
         */
        friend void swap(Row &a, Row &b)
        {
            assert(a.matrixRef == b.matrixRef);
            size_t cols = a.matrixRef->cols;
            for(size_t j = 0; j < cols; ++j)
                std::swap(a.matrixRef->matrix[a.i * cols + j], a.matrixRef->matrix[b.i * cols + j]);
        }
    };
private:
    std::vector<T> matrix;
    size_t rows, cols;

    Matrix(size_t m, size_t n, std::vector<T> &vec) : rows(m), cols(n), matrix(vec) {};
    Matrix(size_t m, size_t n, std::vector<T> &&vec) : rows(m), cols(n), matrix(vec) {};
public:

    /**
     * Constructs a new matrix \f$M \times N\f$.
     *
     * @param m rows
     * @param n columns
     */
    Matrix(size_t m, size_t n) : rows(m), cols(n), matrix(m*n) {}

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
     * Returns i-th row of the matrix.
     *
     * @param i row index
     * @return i-th row
     */
    Row operator()(size_t i)
    {
        assert(i < rows);
        return Row(*this, i);
    }

    /**
     * Returns i-th row of the matrix.
     *
     * @param i row index
     * @return i-th row
     */
    Row operator()(size_t i) const
    {
        assert(i < rows);
        return Row(*this, i);
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

    /**
     * Returns matrix with inverted elements. \f$A^\prime\f$ with elements \f$a^\prime_{i,j} = \frac{1}{a_{i,j}}\f$.
     * Not to be misinterpreted as a matrix inverse \f$A^{-1}\f$.
     *
     * @return matrix with inverted elements.
     */
    Matrix invertElements() const
    {
        Matrix result(rows, cols);
        for(size_t i = 0; i < rows*cols; ++i)
            result.matrix[i] = 1.0 / matrix[i];
        return result;
    }

    /**
     * Transposes the matrix. \f$A^T\f$
     *
     * @return transposed matrix
     */
    Matrix transpose()
    {
        Matrix result(cols, rows, matrix);
        for(size_t i = 0; i < rows; ++i)
            for(size_t j = 0; j < cols; ++j)
                result.matrix[i *rows + j] = matrix[i*cols + j];
        return result;
    }

    /**
     *
     *
     * @return matrix with negated elements.
     */
    Matrix operator-()
    {
        Matrix result(rows, cols);
        for(size_t i = 0; i < rows*cols; ++i)
            result.matrix[i] = -matrix[i];
        return result;
    }

    /**
     * Matrix addition. For matrices \f$A,B,C \in \mathbb{R}^{M \times N}\f$ the addition \f$C = A + B\f$ is
     * defined as follows \f$c_{ij} = a_{ij} + b_{ij}\f$ for each \f$i,j\f$
     *
     * @param lhs left hand side
     * @return sum
     */
    Matrix operator+(const Matrix &lhs) const
    {
        assert(rows == lhs.rows && cols == lhs.cols);
        Matrix result(rows, cols);
        for(size_t i = 0; i < rows*cols; ++i)
            result.matrix[i] = matrix[i] + lhs.matrix[i];
        return result;
    }

    /**
     * Matrix subtraction. For matrices \f$A,B,C \in \mathbb{R}^{M \times N}\f$ the addition \f$C = A - B\f$ is
     * defined as follows \f$c_{ij} = a_{ij} - b_{ij}\f$ for each \f$i,j\f$
     *
     * @param lhs left hand side
     * @return difference
     */
    Matrix operator-(const Matrix &lhs) const
    {
        assert(rows == lhs.rows && cols == lhs.cols);
        Matrix result(rows, cols);
        for(size_t i = 0; i < rows*cols; ++i)
            result.matrix[i] = matrix[i] - lhs.matrix[i];
        return result;
    }

    /**
     * Matrix multiplication in \f$O(n^3)\f$. For matrices
     * \f$A \in \mathbb{R}^{M \times K}, B \in \mathbb{R}^{K \times N},C \in \mathbb{R}^{M \times N}\f$
     * the multiplication \f$C = A \cdot B\f$ is defined as follows
     * \f$c_{ij} = \sum_k a_{ik} - b_{kj}\f$ for each \f$i,j\f$
     *
     * @param lhs left hand side
     * @return product
     */
    Matrix operator*(const Matrix &lhs) const
    {
        assert(rows == lhs.cols);
        Matrix result(rows, lhs.cols);
        for(size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < lhs.cols; ++j)
                for (size_t k = 0; k < cols; ++k)
                    result.matrix[lhs.cols * i + j] += matrix[cols * i + k] * lhs.matrix[lhs.cols * k + j];
        return result;
    }

    /**
     * Matrix multiplication with scalar.
     *
     * @tparam S scalar type
     * @param n scalar
     * @return product
     */
    template <typename S>
    Matrix operator*(S n) const
    {
        Matrix result(rows, cols);
        for(size_t i = 0; i < rows*cols; ++i)
            result.matrix[i] = n * matrix[i];
        return result;
    }

    /**
     * Matrix division by scalar.
     *
     * @tparam S scalar type
     * @param n scalar
     * @return quotient
     */
    template <typename S>
    Matrix operator/(S n) const
    {
        Matrix<T> result(rows, cols);
        for(size_t i = 0; i < rows*cols; ++i)
            result.matrix[i] = matrix[i] / n;
        return result;
    }

    /**
     * Applies function f on each element of the matrix.
     *
     * @param f function
     * @return a new matrix
     */
    Matrix function(T f(T))
    {
        Matrix<T> result(rows, cols);
        for(size_t i = 0; i < rows*cols; ++i)
            result.matrix[i] = f(matrix[i]);
        return result;
    }

    /**
     * Applies function f on each element on the diagonal of the square matrix.
     *
     * @param f function
     * @return a new matrix
     */
    Matrix function_diag(T f(T))
    {
        Matrix<T> result(rows, cols);
        for(size_t i = 0; i < rows; ++i)
            result.matrix[i*cols + i] = f(matrix[i*cols + i]);
        return result;
    }

    /**
     * Applies function f on each element of the matrix.
     *
     * @param f function
     * @return a new matrix
     */
    Matrix &apply(T f(T))
    {
        for(size_t i = 0; i < rows*cols; ++i)
            matrix[i] = f(matrix[i]);
        return *this;
    }

    /**
     * Applies function f on each element on the diagonal of the square matrix.
     *
     * @param f function
     * @return a new matrix
     */
    Matrix &apply_diag(T f(T))
    {
        assert(rows == cols);
        for(size_t i = 0; i < rows; ++i)
            matrix[i*cols + i] = f(matrix[i*cols + i]);
        return *this;
    }

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
    std::vector<T> &memory() const
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
    friend std::ostream &operator<<(std::ostream &os, const Matrix &m)
    {
        for(size_t i = 0, j = 1; i < m.rows * m.cols; ++i, ++j) {
            os << std::setprecision(2) << std::setw(6) <<  m.matrix[i];
            if(j == m.cols)
            {
                j = 0;
                os << std::endl;
            }
        }
        return os;
    }

};

template<typename T, typename S>
Matrix<T> operator*(S n, const Matrix<T> &m)
{
    return m * n;
}

#endif //NSMERICALC_MATRIX_HPP
