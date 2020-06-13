/**
 * @file dft.hpp
 * Copyright (c) 2020 Peter Grajcar
 */
#ifndef NUMERICALC_DFT_HPP
#define NUMERICALC_DFT_HPP

#include <complex>
#include "numericalc/Polynomial.hpp"

/**
 * Discrete Fourier Transform. \f$O(n^2)\f$ algorithm for polynomials of arbitrary length.
 * For \f$O(log(n))\f$ algorithm check @see fft.
 *
 * @tparam T polynomial type
 * @param p polynomial
 * @return fourier transformed polynomial
 */
template <typename T>
Polynomial<std::complex<T>> dft(const Polynomial<std::complex<T>> &p);

/**
 * Inverse Discrete Fourier Transform. \f$O(n^2)\f$ algorithm for polynomials of arbitrary length.
 * For \f$O(log(n))\f$ algorithm check @see fft_inv.
 *
 * @tparam T polynomial type
 * @param p polynomial
 * @return fourier transformed polynomial
 */
template <typename T>
Polynomial<std::complex<T>> dft_inv(const Polynomial<std::complex<T>> &p);

#endif //NUMERICALC_DFT_HPP
