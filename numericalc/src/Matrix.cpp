/**
 * Matrix implementation.
 */
#include "numericalc/Matrix.hpp"
#include <iostream>
#include <iomanip>
#include <vector>

std::vector<double>::iterator Matrix::operator[](size_t i)
{
    assert(i < rows);
    return matrix.begin() + i * cols;
}

std::vector<double>::const_iterator Matrix::operator[](size_t i) const
{
    assert(i < rows);
    return matrix.begin() + i * cols;
}

std::ostream & operator<<(std::ostream & os, const Matrix & matrix)
{
    for(size_t i = 0, j = 1; i < matrix.rows * matrix.cols; ++i, ++j) {
        os << std::setprecision(2) << std::setw(6) <<  matrix.matrix[i];
        if(j == matrix.cols)
        {
            j = 0;
            os << std::endl;
        }
    }
    return os;
}

Matrix Matrix::operator+(Matrix & lhs) const
{
    assert(rows == lhs.rows && cols == lhs.cols);
    Matrix result(rows, cols);

    for(size_t i = 0; i < rows*cols; ++i)
    {
        result.matrix[i] = matrix[i] + lhs.matrix[i];
    }

    return result;
}

