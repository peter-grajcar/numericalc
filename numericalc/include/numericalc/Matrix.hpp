#ifndef NUMERICALC_MATRIX_HPP
#define NUMERICALC_MATRIX_HPP

#include <cstddef>
#include <vector>
#include <iostream>

/**
 * Class representing a matrix.
 */
class Matrix
{
private:
    std::vector<double> matrix;
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
    std::vector<double>::iterator operator[](size_t i);

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
    std::vector<double>::const_iterator operator[](size_t i) const; // TODO: create custom iterator

    /**
     * Matrix addition. For matrices \f$A,B,C \in \mathbb{R}^{M \times N}\f$ the addition \f$C = A + B\f$ is
     * defined as follows \f$c_{ij} = a_{ij} + b_{ij}\f$ for each \f$i,j\f$
     *
     * @param lhs
     * @return
     */
    Matrix operator+(Matrix &lhs) const;

    /**
     * Prints the matrix to the output stream.
     *
     * @param os output stream
     * @param matrix matrix
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

};


#endif //NUMERICALC_MATRIX_HPP
