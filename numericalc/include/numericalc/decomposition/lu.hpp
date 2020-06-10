/**
 * LU decomposition algorithm.
 *
 * @file lu.hpp
 */
#ifndef NUMERICALC_LU_HPP
#define NUMERICALC_LU_HPP

#include "numericalc/Matrix.hpp"

/**
 * Decomposes square matrix A. Returns decomposed matrix containing both matrix L and U such that
 * strict lower triangle matches L and upper triangle matches U. Ones on diagonal of L are implied.
 *
 * Formulae for determining elements of LU matrix:
 * <ol>
 *      <li>\f$u_{m,j} = a_{m,j} - \sum^{m-1}_{k=1} l_{m,k} u_{k,j}\f$</li>
 *      <li>\f$l_{i,m} = \frac{1}{u_{m,m}}(a_{i,m} - \sum^{m-1}_{k=1} l_{i,k} u_{k,m})\f$</li>
 * </ol>
 *
 * @tparam T matrix element type
 * @param a matrix A
 * @return decomposed matrix
 */
template<typename T>
Matrix<T> lu_decomposition(const Matrix<T> a)
{
    assert(a.get_rows() == a.get_cols());
    Matrix<T> lu(a.get_rows(), a.get_cols());

    for (size_t m = 0; m < a.get_rows(); ++m) {
        for (size_t i = 0; i < a.get_cols(); ++i) {
            if (i > m) {
                T sum_col = 0;
                for (size_t k = 0; k + 1 < m; ++k)
                    sum_col += lu(i, k) * lu(k, m);
                lu(i, m) = (a(i, m) - sum_col) / lu(m, m);
            }
            if (i >= m) {
                T sum_row = 0;
                for (size_t k = 0; k < m; ++k)
                    sum_row += lu(m, k) * lu(k, i);
                lu(m, i) = a(m, i) - sum_row;
            }
        }
    }

    return lu;
}

#endif //NUMERICALC_LU_HPP
