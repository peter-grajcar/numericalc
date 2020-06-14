/**
 * Lagrange polynomial interpolation.
 *
 * @file lagrange.hpp
 * Copyright (c) 2020 Peter Grajcar
 */
#ifndef NUMERICALC_LAGRANGE_HPP
#define NUMERICALC_LAGRANGE_HPP

#include <vector>
#include <numericalc/Polynomial.hpp>
#include <numericalc/Matrix.hpp>

/**
 * Constructs lagrange polynomials at grid points. \f$O(n^2)\f$ algorithm.
 *
 * @tparam T polynomial type
 * @param grid grid points
 * @return Lagrange polynomials
 */
template <typename T>
std::vector<Polynomial<T>> lagrange_polynomials(const std::vector<T> &grid);

/**
 * Constructs lagrange polynomials at grid points. Returns matrix with each row representing
 * coefficients of polynomial \f$l_i\f$. \f$O(n^2)\f$ algorithm.
 *
 * @tparam T polynomial type
 * @param grid grid points
 * @return Lagrange polynomial matrix
 */
template <typename T>
Matrix<T> lagrange_polynomial_matrix(const std::vector<T> &grid);


#endif //NUMERICALC_LAGRANGE_HPP
