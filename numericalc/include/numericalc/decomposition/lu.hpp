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
 *      <li>\f$l_{i,m} = \frac{1}{u_{m,m}} \left (a_{i,m} - \sum^{m-1}_{k=1} l_{i,k} u_{k,m} \right )\f$</li>
 * </ol>
 *
 * @tparam T matrix element type
 * @param a matrix A
 * @return decomposed matrix
 */
template<typename T>
Matrix<T> lu_decomposition(const Matrix<T> a);

#endif //NUMERICALC_LU_HPP
