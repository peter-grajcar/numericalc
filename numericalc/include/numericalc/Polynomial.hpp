#ifndef NUMERICALC_POLYNOMIAL_HPP
#define NUMERICALC_POLYNOMIAL_HPP

#include <vector>
#include <iostream>

/**
 * Class representing polynomial
 *
 * @tparam T coefficient type
 */
template <typename T>
class Polynomial
{
private:
    size_t deg;
    std::vector<T> coef;
public:
    /**
     * Constructs a zero polynomial of certain degree.
     *
     * @param deg degree of the polynomial
     */
    explicit Polynomial(size_t deg) : deg(deg), coef(deg) {}

    /**
     * Constructs a polynomial with initial coefficients.
     *
     * @param deg degree
     * @param coefs initial coeffictients
     */
    Polynomial(size_t deg, const T coefs[]) : deg(deg), coef(coefs, coefs + deg) {}

    /**
     * Constructs a polynomial with initial coefficients. Degree is determined from the coefficient vector.
     *
     * @param coefs initial coeffictients
     */
    explicit Polynomial(const std::vector<T> &coefs) : deg(coefs.size()), coef(coefs) {}

    /**
     * Constructs a polynomial with initial coefficients. Degree is determined from the coefficient vector.
     *
     * @param coefs initial coeffictients
     */
    explicit Polynomial(const std::vector<T> &&coefs) : deg(coefs.size()), coef(coefs) {}

    /**
     *
     * @return degree of polynomial
     */
    inline size_t degree() const
    {
        return deg;
    }

    /**
     * Returns i-th coefficient.
     *
     * @param i index
     * @return i-th coefficient
     */
    inline T &operator[](size_t i)
    {
        return coef[i];
    }

    /**
     * Returns i-th coefficient.
     *
     * @param i index
     * @return i-th coefficient
     */
    inline const T &operator[](size_t i) const
    {
        return coef[i];
    }

    /**
     * Evaluates polynomial at x.
     *
     * @param x x value
     * @return value of polynomial at x
     */
    inline T operator()(T x) const
    {
        return eval(x);
    }

    /**
     * Evaluates polynomial at x. Evaluation is done using Horner's schema.
     *
     * @param x x value
     * @return value of polynomial at x
     */
    T eval(T x) const;

    /**
     * Returns first derivative of polynomial. Returned polynomial is of size \f$n - 1\f$ where \f$n\f$ is
     * size of original polynomial.
     *
     * @return first derivative of polynomial
     */
    Polynomial derivative() const;

    /**
     * Polynomial negation.
     *
     * @return negated polynomial
     */
    Polynomial operator-() const;

    /**
     * Polynomial addition. Resulting polynomial always has size \f$max(m, n)\f$. No
     * implicit zero trimming is done.
     *
     * @param q second polynomial
     * @return sum
     */
    Polynomial operator+(const Polynomial &q) const;

    /**
     * Polynomial subtraction. Resulting polynomial always has size \f$max(m, n)\f$. No
     * implicit zero trimming is done.
     *
     * @param q second polynomial
     * @return difference
     */
    Polynomial operator-(const Polynomial &q) const;

    /**
     * \f$O(mn)\f$ polynomial multiplication. Resulting polynomial always has size \f$m + n\f$. No
     * implicit zero trimming is done. For more effictient multiplication see Fast Fourier Transform (FFT)
     * header file.
     *
     * @see fft Fast Fourier Transform
     * @param q second polynomial
     * @return polynomial product
     */
    Polynomial operator*(const Polynomial &q) const;

    /**
     *
     * @tparam S
     * @param n
     * @return
     */
    template <typename S>
    Polynomial operator*(S n) const;

    /**
     *
     * @tparam S
     * @param n
     * @return
     */
    template <typename S>
    Polynomial operator/(S n) const;

    Polynomial &operator+=(const Polynomial &q)
    {
        *this = *this + q;
        return *this;
    }

    Polynomial &operator-=(const Polynomial &q)
    {
        *this = *this + q;
        return *this;
    }

    Polynomial &operator*=(const Polynomial &q)
    {
        *this = *this + q;
        return *this;
    }

    template <typename S>
    Polynomial &operator*=(S n)
    {
        *this = *this * n;
        return *this;
    }

    template <typename S>
    Polynomial &operator/=(S n)
    {
        *this = *this / n;
        return *this;
    }

    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const Polynomial<U> &p);


};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Polynomial<T> &p)
{
    for(size_t i = 0; i < p.deg; ++i) {
        const T c = p.coef[i];
        if(i == 0) os << c;
        else {
            os << (c >= 0 ? " + " : " - ");
            if(i == 1)  os << (c >= 0 ? c : -c) << "x";
            else        os << (c >= 0 ? c : -c) << "x^" << i;
        }
    }
    return os;
}

template <typename T>
template <typename S>
Polynomial<T> Polynomial<T>::operator*(S n) const
{
    Polynomial result(deg);
    for(size_t i = 0; i < coef; ++i)
        result.coef[i] = n * coef[i];
    return result;
}

template <typename T>
template <typename S>
Polynomial<T> Polynomial<T>::operator/(S n) const
{
    Polynomial result(deg);
    for(size_t i = 0; i < deg; ++i)
        result.coef[i] = coef[i] / n;
    return result;
}

template <typename T, typename S>
Polynomial<T> operator*(S n, const Polynomial<T> &p)
{
    return p * n;
}

#endif //NUMERICALC_POLYNOMIAL_HPP
