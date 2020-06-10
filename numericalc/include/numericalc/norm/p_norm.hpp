/**
 * Includes p-norm and euclidean norm functions.
 *
 * @file p_norm.hpp
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
T p_norm_pow(S p, const Matrix<T> &a)
{
    assert(p >= 1);
    T sum = 0;
    for(auto x : a.memory())
        sum += pow(abs(x), p);
    return sum;
}

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
T p_norm(S p, const Matrix<T> &a)
{
    assert(p >= 1);
    return pow(p_norm_pow(p, a), ((T) 1)/p);
}

/**
 * Returns squared Euclidean norm. \f$\Vert A \Vert^2_2\f$.
 *
 * @tparam T matrix type
 * @param a matrix
 * @return squared Euclidean norm
 */
template <typename T>
T euclidean_norm_sqr(const Matrix<T> &a)
{
    return p_norm_pow(2, a);
}

/**
 * Returns Euclidean norm of a matrix. \f$\Vert A \Vert_2\f$.
 *
 * @tparam T matrix type
 * @param a matrix
 * @return Euclidean norm
 */
template <typename T>
T euclidean_norm(const Matrix<T> &a)
{
    return p_norm(2, a);
}

#endif //NUMERICALC_P_NORM_HPP