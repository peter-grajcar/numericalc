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
    std::vector<T> coef;
    size_t deg;
public:
    /**
     * Constructs a polynomial of certain degree.
     *
     * @param deg degree of the polynomial
     */
    explicit Polynomial(size_t deg) : deg(deg), coef(deg) {}

    /**
     *
     * @param deg
     */
    Polynomial(size_t deg, const T coefs[]) : deg(deg), coef(coefs, coefs + deg) {}

    /**
     *
     * @param coefs
     */
    explicit Polynomial(const std::vector<T> &coefs) : deg(coefs.size()), coef(coefs) {}

    /**
     *
     * @param coefs
     */
    explicit Polynomial(const std::vector<T> &&coefs) : deg(coefs.size()), coef(coefs) {}

    /**
     *
     * @return
     */
    inline size_t degree() const
    {
        return deg;
    }

    /**
     *
     * @param i
     * @return
     */
    inline T &operator[](size_t i)
    {
        return coef[i];
    }

    /**
     *
     * @param i
     * @return
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
     *
     * @return
     */
    Polynomial derivative() const;

    /**
     *
     * @return
     */
    Polynomial operator-() const;

    /**
     *
     * @param q
     * @return
     */
    Polynomial operator+(const Polynomial &q) const;

    /**
     *
     * @param q
     * @return
     */
    Polynomial operator-(const Polynomial &q) const;

    /**
     *
     * @param q
     * @return
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
