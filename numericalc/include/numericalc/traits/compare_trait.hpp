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

template <typename T, typename U = void>
struct compare_trait;

template <typename Integral>
struct compare_trait<Integral, typename std::enable_if<std::is_integral<Integral>::value>::type>
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

template <typename Floating>
struct compare_trait <Floating, typename std::enable_if<std::is_floating_point<Floating>::value>::type>
{
    static bool eq(const Floating &a, const Floating &b)
    {
        return std::fabs(a - b) < std::numeric_limits<Floating>::epsilon();
    }
    static bool neq(const Integral &a, const Integral &b)
    {
        return std::fabs(a - b) > std::numeric_limits<Floating>::epsilon();
    }
    static bool lt(const Integral &a, const Integral &b)
    {
        return a < b && neq(a, b);
    }
    static bool gt(const Integral &a, const Integral &b)
    {
        return a > b && neq(a, b);
    }
    static bool lte(const Integral &a, const Integral &b)
    {
        return a <= b || eq(a, b);
    }
    static bool gte(const Integral &a, const Integral &b)
    {
        return a >= b || eq(a, b);
    }
};

template <typename T>
struct compare_trait<std::complex<T>>
{
    static bool eq(const std::complex<T> &a, const std::complex<T> &b)
    {
        return compare_trait<T>::eq(a.real(), b.real()) && compare_trait<T>::eq(a.imag(), b.imag());
    }
};

#endif //NUMERICALC_COMPARE_HPP
