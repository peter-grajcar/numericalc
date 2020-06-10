/**
 * Max norm.
 *
 * @file max_norm.hpp
 */
#ifndef NUMERICALC_MAX_NORM_HPP
#define NUMERICALC_MAX_NORM_HPP

#include <numericalc/Matrix.hpp>
#include <algorithm>

template <typename T>
T max_norm(const Matrix<T> &a)
{
    return *std::max_element(a.memory().begin(), a.memory().end());
}

#endif //NUMERICALC_MAX_NORM_HPP
