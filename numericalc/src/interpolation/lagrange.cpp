#include "numericalc/interpolation/lagrange.hpp"

/*
 * Divides polynomial such that p(x) = (x - x0)q(x)
 */
template <typename T>
Polynomial<T> long_division(const Polynomial<T> &p, T x0)
{
    Polynomial<T> q = p.derivative();

    for(size_t i = 1; i < q.degree(); ++i)
    {
        q[q.degree() - 1 - i] += q[q.degree() - i] * x0;
    }

    return q;
}

template <typename T>
std::vector<Polynomial<T>> lagrange_polynomials(const std::vector<T> &grid)
{
    assert(grid.size() > 0);
    Polynomial<T> w(grid.size() + 1);

    // w = (x - x_0)(x - x_1)...(x - x_n)
    w[0] = -grid[0];
    w[1] = 1;
    for(size_t i = 1; i < w.degree() - 1; ++i)
    {
        w[i + 1] = 1;
        for(size_t j = 0; j <= i; ++j) {
            w[i - j] *= -grid[i];
            if(j + 1 <= i) w[i - j] += w[i - j - 1];
        }
    }

    std::vector<Polynomial<T>> l;
    l.reserve(grid.size());
    Polynomial<T> wd = w.derivative();

    for(size_t i = 0; i < grid.size(); ++i)
        l.push_back(long_division(w, grid[i]) / wd(grid[i]));

    return l;
}


template std::vector<Polynomial<double>> lagrange_polynomials(const std::vector<double> &grid);
template std::vector<Polynomial<float>> lagrange_polynomials(const std::vector<float> &grid);
template std::vector<Polynomial<int>> lagrange_polynomials(const std::vector<int> &grid);

