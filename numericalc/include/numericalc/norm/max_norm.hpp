/**
 * Max norm.
 *
 * @file max_norm.hpp
 * Copyright (c) 2020 Peter Grajcar
 */
#ifndef NUMERICALC_MAX_NORM_HPP
#define NUMERICALC_MAX_NORM_HPP

#include <numericalc/Matrix.hpp>
#include <algorithm>

template <typename T>
T max_norm(const Matrix<T> &a);

#endif //NUMERICALC_MAX_NORM_HPP
