/**
 *
 *
 * @file dft.cpp
 * Copyright (c) 2020 Peter Grajcar
 */
#include "numericalc/dft/dft.hpp"

template <typename T>
Polynomial<std::complex<T>> dft_gen(const Polynomial<std::complex<T>> &p, bool inv)
{
    using complex = std::complex<T>;

    size_t deg = p.degree();

    Polynomial<complex> y(deg);

    for(size_t i = 0; i < deg; ++i)
    {
        T angle = (inv ? -1 : 1) * 2 * M_PI * i / deg;
        complex w(cos(angle), sin(angle)), wj(1);
        for(size_t j = 0; j < deg; ++j, wj *= w)
        {
            y[i] += p[j] * wj;
        }
    }

    if(inv)
        for(size_t i = 0; i < deg; ++i)
            y[i] /= deg;

    return y;
}

template <typename T>
Polynomial<std::complex<T>> dft(const Polynomial<std::complex<T>> &p)
{
    return dft_gen(p, false);
}

template <typename T>
Polynomial<std::complex<T>> dft_inv(const Polynomial<std::complex<T>> &p)
{
    return dft_gen(p, true);
}

template Polynomial<std::complex<double>> dft(const Polynomial<std::complex<double>> &p);
template Polynomial<std::complex<double>> dft_inv(const Polynomial<std::complex<double>> &p);