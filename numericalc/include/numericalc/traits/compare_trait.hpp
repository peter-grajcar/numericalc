/**
 * @file compare_traits.hpp
 * Copyright (c) 2020 Peter Grajcar
 */

#ifndef NUMERICALC_COMPARE_HPP
#define NUMERICALC_COMPARE_HPP

#include <type_traits>
#include <limits>
#include <cmath>
#include <complex>


/**
 * Checks if type can be compared using standard comparison operators.
 *
 * @tparam T type
 */
template <typename T>
struct is_value_comparable : std::integral_constant<
        bool,
        std::is_integral<T>::value || std::is_pointer<T>::value || std::is_same<std::string, T>::value
        > {};

template <typename T, typename = void> struct compare_trait;

/**
 * Functions for comparing integral values. Standard comparsion operators are used.
 *
 * @tparam Integral integral type
 */
template <typename Integral>
struct compare_trait<Integral, typename std::enable_if<is_value_comparable<Integral>::value>::type>
{
    static bool eq(const Integral &a, const Integral &b)
    {
        return a == b;
    }
    static bool neq(const Integral &a, const Integral &b)
    {
        return a != b;
    }
    static bool lt(const Integral &a, const Integral &b)
    {
        return a < b;
    }
    static bool gt(const Integral &a, const Integral &b)
    {
        return a > b;
    }
    static bool lte(const Integral &a, const Integral &b)
    {
        return a <= b;
    }
    static bool gte(const Integral &a, const Integral &b)
    {
        return a >= b;
    }
};

/**
 * Includes functions for comparing floating point numbers using std::numeric_limits::epsilon.
 *
 * @tparam Floating floating points type
 */
template <typename Floating>
struct compare_trait <Floating, typename std::enable_if<std::is_floating_point<Floating>::value>::type>
{
    static bool eq(const Floating &a, const Floating &b)
    {
        return std::fabs(a - b) < std::numeric_limits<Floating>::epsilon();
    }
    static bool neq(const Floating &a, const Floating &b)
    {
        return std::fabs(a - b) > std::numeric_limits<Floating>::epsilon();
    }
    static bool lt(const Floating &a, const Floating &b)
    {
        return a < b && neq(a, b);
    }
    static bool gt(const Floating &a, const Floating &b)
    {
        return a > b && neq(a, b);
    }
    static bool lte(const Floating &a, const Floating &b)
    {
        return a <= b || eq(a, b);
    }
    static bool gte(const Floating &a, const Floating &b)
    {
        return a >= b || eq(a, b);
    }
};

/**
 * Includes functions for comparing complex. only eq, and neq functions are provided
 * as complex numbers are not ordered.
 *
 * @tparam T complex number type
 */
template <typename T>
struct compare_trait<std::complex<T>>
{
    static bool eq(const std::complex<T> &a, const std::complex<T> &b)
    {
        return compare_trait<T>::eq(a.real(), b.real()) && compare_trait<T>::eq(a.imag(), b.imag());
    }
    static bool neq(const std::complex<T> &a, const std::complex<T> &b)
    {
        return compare_trait<T>::neq(a.real(), b.real()) && compare_trait<T>::neq(a.imag(), b.imag());
    }
};

#endif //NUMERICALC_COMPARE_HPP
