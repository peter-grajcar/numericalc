/**
 *
 *
 * @file p_norm.cpp
 * Copyright (c) 2020 Peter Grajcar
 */
#include "numericalc/norm/p_norm.hpp"

template <typename T, typename S>
T p_norm_pow(S p, const Matrix<T> &a)
{
    assert(p >= 1);
    T sum = 0;
    for(auto x : a.memory())
        sum += pow(abs(x), p);
    return sum;
}

template <typename T, typename S>
T p_norm(S p, const Matrix<T> &a)
{
    assert(p >= 1);
    return pow(p_norm_pow(p, a), ((T) 1)/p);
}

template <typename T>
T euclidean_norm_sqr(const Matrix<T> &a)
{
    return p_norm_pow(2, a);
}

template <typename T>
T euclidean_norm(const Matrix<T> &a)
{
    return p_norm(2, a);
}

template double p_norm(int, const Matrix<double> &a);
template double p_norm(double, const Matrix<double> &a);
template float p_norm(int, const Matrix<float> &a);
template float p_norm(float, const Matrix<float> &a);
template int p_norm(int, const Matrix<int> &a);
template double p_norm_pow(int, const Matrix<double> &a);
template double p_norm_pow(double, const Matrix<double> &a);
template float p_norm_pow(int, const Matrix<float> &a);
template float p_norm_pow(float, const Matrix<float> &a);
template int p_norm_pow(int, const Matrix<int> &a);

template double euclidean_norm(const Matrix<double> &a);
template float euclidean_norm(const Matrix<float> &a);
template int euclidean_norm(const Matrix<int> &a);
template double euclidean_norm_sqr(const Matrix<double> &a);
template float euclidean_norm_sqr(const Matrix<float> &a);
template int euclidean_norm_sqr(const Matrix<int> &a);
