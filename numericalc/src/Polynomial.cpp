/**
 *
 *
 * @file Polynomial.cpp
 * Copyright (c) 2020 Peter Grajcar
 */
#include "numericalc/Polynomial.hpp"

template <typename T>
T Polynomial<T>::eval(T x) const
{
    T b = 0;
    if(!deg) return b;
    for(auto i = coef.rbegin(); i < coef.rend(); ++i) {
        b *= x;
        b += *i;
    }
    return b;
}

template <typename T>
Polynomial<T> Polynomial<T>::derivative() const
{
    std::vector<T> d_coef(coef.begin() + 1, coef.end());
    return Polynomial(std::move(d_coef));
}

template <typename T>
Polynomial<T> Polynomial<T>::operator-() const
{
    Polynomial result(coef);
    for(auto &c : result.coef)
        c = -c;
    return result;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator+(const Polynomial<T> &q) const
{
    Polynomial result(std::max(deg, q.deg));
    for(size_t i = 0; i < result.deg; ++i) {
        if(i < deg && i < q.deg)
            result[i] = coef[i] + q.coef[i];
        else if(i < deg)
            result[i] = coef[i];
        else
            result[i] = q.coef[i];
    }
}

template <typename T>
Polynomial<T> Polynomial<T>::operator-(const Polynomial<T> &q) const
{
    Polynomial result(std::max(deg, q.deg));
    for(size_t i = 0; i < result.deg; ++i) {
        if(i < deg && i < q.deg)
            result[i] = coef[i] - q.coef[i];
        else if(i < deg)
            result[i] = coef[i];
        else
            result[i] = -q.coef[i];
    }
}

template <typename T>
Polynomial<T> Polynomial<T>::operator*(const Polynomial<T> &q) const
{
    Polynomial result(deg + q.deg);
    for(size_t i = 0; i < deg; ++i)
        for(size_t j = 0; j < q.deg; ++j)
            result.coef[i + j] = coef[i]*q.coef[j];
    return result;
}

template class Polynomial<double>;
template class Polynomial<float>;
template class Polynomial<int>;