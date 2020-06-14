/**
 *
 *
 * @file max_norm.cpp
 * Copyright (c) 2020 Peter Grajcar
 */
#include "numericalc/norm/max_norm.hpp"

template <typename T>
T max_norm(const Matrix<T> &a)
{
    return *std::max_element(a.elements().begin(), a.elements().end());
}

template double max_norm(const Matrix<double> &a);
template float max_norm(const Matrix<float> &a);
template int max_norm(const Matrix<int> &a);

