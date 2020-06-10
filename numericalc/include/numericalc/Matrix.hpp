#ifndef NUMERICALC_MATRIX_HPP
#define NUMERICALC_MATRIX_HPP

#include <cstddef>
#include <vector>
#include <iostream>
#include <iomanip>

/**
 * Class representing a matrix.
 */
template <typename T>
class Matrix
{
private:
    std::vector<T> matrix;
    size_t rows, cols;
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
     * Returns iterator at first element of i-th row.
     *
     * Operator[] can be applied on the returned iterator to retrieve element
     * at position (i, j).
     *
     * <pre>{@code
     * Matrix A(3, 3);
     * A[2][1] = 1.5;
     * }</pre>
     *
     * @param i row index
     * @return iterator at first element of i-th row
     */
    typename std::vector<T>::iterator operator[](size_t i)
    {
        assert(i < rows);
        return matrix.begin() + i * cols;
    }

    /**
     * Returns iterator at first element of i-th row.
     *
     * Operator[] can be applied on the returned iterator to retrieve element
     * at position (i, j).
     *
     * <pre>{@code
     * const Matrix A(3, 3);
     * std::cout << "A_{2,1} = " << A[2][1] << std::endl;
     * }</pre>
     *
     * @param i row index
     * @return iterator at first element of i-th row
     */
    typename std::vector<T>::const_iterator operator[](size_t i) const // TODO: create custom iterator
    {
        assert(i < rows);
        return matrix.begin() + i * cols;
    }

    /**
     * Matrix addition. For matrices \f$A,B,C \in \mathbb{R}^{M \times N}\f$ the addition \f$C = A + B\f$ is
     * defined as follows \f$c_{ij} = a_{ij} + b_{ij}\f$ for each \f$i,j\f$
     *
     * @param lhs left hand side
     * @return sum
     */
    Matrix operator+(Matrix &lhs) const
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
    Matrix operator-(Matrix &lhs) const
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
    Matrix operator*(Matrix &lhs) const
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
     * @param n scalar
     * @return product
     */
    template <typename U>
    Matrix operator*(U n) const
    {
        Matrix result(rows, cols);

        for(size_t i = 0; i < rows*cols; ++i)
            result.matrix[i] = n * matrix[i];

        return result;
    }

    /**
     * Matrix division by scalar.
     *
     * @param n scalar
     * @return quotient
     */
    template <typename U>
    Matrix operator/(U n) const
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
     */
    void apply(T f(T))
    {
        for(size_t i = 0; i < rows*cols; ++i)
            matrix[i] = f(matrix[i]);
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

template<typename T, typename U>
Matrix<T> operator*(U n, Matrix<T> &matrix)
{
    return matrix * n;
}

#endif //NUMERICALC_MATRIX_HPP
