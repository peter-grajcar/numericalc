#include <complex>
#include <cmath>
#include "numericalc/fft/fft.hpp"

template <typename T>
Polynomial<std::complex<T>> fft_gen(const Polynomial<std::complex<T>> &p, bool inv)
{
    using complex = std::complex<T>;

    size_t deg = p.degree();
    //degree has to be power of two
    assert((deg & (deg - 1)) == 0);

    Polynomial<complex> y(p);

    // swap coefficients as they would be swapped by recursion
    // i.e. each recursion splits the polynomial into two
    // one with even coefficients and the other with odd.
    // For n be logarithm of deg(p) we can represent i-th
    // coefficient path in the recursion tree as i coded
    // as n-bit binary number.
    // e.g. for deg(p) = 16, n = 4, we need to find what
    // number will end up at i = 2 = 0010, the coding
    // tells us that the number we need to find was first
    // even then even then odd and even again. Number which
    // meets this criteria is 4, in binary 0100 which is
    // incidentally 0010 with reversed bits.
    for(size_t i = 1; i < deg; ++i)
    {
        size_t k = i, j = 0;
        for(size_t pow = 1; pow < deg; pow <<= 1)
        {
            j <<= 1;
            j |= k & 1;
            k >>= 1;
        }

        if(i < j)
            std::swap(y[i], y[j]);
    }

    for(size_t n = 2; n <= deg; n <<= 1)
    {
        T angle = (inv ? -1 : 1) * 2 * M_PI / n;
        complex w(cos(angle), sin(angle));
        for(size_t i = 0; i < deg; i += n)
        {
            complex wj(1);
            for(size_t j = 0; j < n / 2; ++j, wj *= w)
            {
                complex s = y[i + j];
                complex l = y[i + j + n / 2] * wj;
                y[i + j]         = s + l;
                y[i + j + n / 2] = s - l;
            }
        }
    }

    if(inv)
        for(size_t i = 0; i < deg; ++i)
            y[i] /= deg;

    return y;
}

template <typename T>
Polynomial<std::complex<T>> fft(const Polynomial<std::complex<T>> &p)
{
    return fft_gen(p, false);
}

template <typename T>
Polynomial<std::complex<T>> fft_inv(const Polynomial<std::complex<T>> &p)
{
    return fft_gen(p, true);
}

template <typename T>
Polynomial<T> fft_mult(const Polynomial<T> &p, const Polynomial<T> &q)
{
 //TODO:
}

template Polynomial<std::complex<double>> fft(const Polynomial<std::complex<double>> &p);
template Polynomial<std::complex<double>> fft_inv(const Polynomial<std::complex<double>> &p);