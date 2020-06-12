#include "numericalc/Polynomial.hpp"

template <typename T>
T Polynomial<T>::eval(T x) const
{
    //TODO:
}

template <typename T>
Polynomial<T> Polynomial<T>::derivative() const
{
    //TODO:
}

template <typename T>
Polynomial<T> Polynomial<T>::operator-() const
{
    //TODO:
}

template <typename T>
Polynomial<T> Polynomial<T>::operator+(const Polynomial<T> &q) const
{
    //TODO:
}

template <typename T>
Polynomial<T> Polynomial<T>::operator-(const Polynomial<T> &q) const
{
    //TODO:
}

template <typename T>
Polynomial<T> Polynomial<T>::operator*(const Polynomial<T> &q) const
{
    //TODO:
}

template class Polynomial<double>;
template class Polynomial<float>;
template class Polynomial<int>;