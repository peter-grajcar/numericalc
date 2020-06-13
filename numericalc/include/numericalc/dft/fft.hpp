/**
 * Fast Fourier Transform.
 *
 * @file fft.hpp
 * Copyright (c) 2020 Peter Grajcar
 */
#ifndef NUMERICALC_FFT_HPP
#define NUMERICALC_FFT_HPP

#include "numericalc/Polynomial.hpp"
#include <complex>

/**
 * Fast Fourier Transform. The degree of the polynomial has to be power of two.
 *
 * @tparam T polynomial type
 * @param p polynomial
 * @return fourier-transformed polynomial
 */
template <typename T>
Polynomial<std::complex<T>> fft(const Polynomial<std::complex<T>> &p);

/**
 * Inverse Fast Fourier Transform. The degree of the polynomial has to be power of two.
 *
 * @tparam T polynomial type
 * @param p polynomial
 * @return inverse fourier-transformed polynomial
 */
template <typename T>
Polynomial<std::complex<T>> fft_inv(const Polynomial<std::complex<T>> &p);

/**
 * Polynomial multiplication using FFT.
 *
 * @tparam T polynomial type
 * @param p polynomial p
 * @param q polynomial q
 * @return product of p and q
 */
template <typename T>
Polynomial<T> fft_mult(const Polynomial<T> &p, const Polynomial<T> &q);

#endif //NUMERICALC_FFT_HPP
