/**
 * Includes p-norm and euclidean norm functions.
 *
 * @file p_norm.hpp
 * Copyright (c) 2020 Peter Grajcar
 */
#ifndef NUMERICALC_P_NORM_HPP
#define NUMERICALC_P_NORM_HPP

#include <numericalc/Matrix.hpp>
#include <cmath>

/**
 * Returns p-th power of p-norm of a matrix.
 *
 * @tparam T
 * @tparam S
 * @param p
 * @param a
 * @return
 */
template <typename T, typename S>
T p_norm_pow(S p, const Matrix<T> &a);

/**
 * Returns p-norm of a matrix. The p-norm is defined as \f$\Vert A \Vert_p = \left (\sum^n_{i=0} \sum^m_{j=0} |a_{i,j}|^p \right )^{1 \over p}\f$.
 *
 * @tparam T matrix type
 * @tparam S p type
 * @param p p value
 * @param a matrix
 * @return p-norm of a
 */
template <typename T, typename S>
T p_norm(S p, const Matrix<T> &a);

/**
 * Returns squared Euclidean norm. \f$\Vert A \Vert^2_2\f$.
 *
 * @tparam T matrix type
 * @param a matrix
 * @return squared Euclidean norm
 */
template <typename T>
T euclidean_norm_sqr(const Matrix<T> &a);

/**
 * Returns Euclidean norm of a matrix. \f$\Vert A \Vert_2\f$.
 *
 * @tparam T matrix type
 * @param a matrix
 * @return Euclidean norm
 */
template <typename T>
T euclidean_norm(const Matrix<T> &a);

#endif //NUMERICALC_P_NORM_HPP
