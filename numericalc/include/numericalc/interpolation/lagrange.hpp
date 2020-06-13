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

/**
 * Constructs lagrange polynomials at grid points. \f$O(n^2)\f$ algorithm.
 *
 * @tparam T polynomial type
 * @param grid grid points
 * @return Lagrange polynomials
 */
template <typename T>
std::vector<Polynomial<T>> lagrange_polynomials(const std::vector<T> &grid);


#endif //NUMERICALC_LAGRANGE_HPP
