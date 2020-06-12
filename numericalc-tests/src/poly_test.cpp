#include <iostream>
#include "numericalc/Polynomial.hpp"
#include "numericalc/interpolation/lagrange.hpp"
#include <cmath>

using namespace std;

int poly_test()
{
    Polynomial<double> p(4, (double []){0, -1, 2, 3});

    cout << "p = " << p << endl;
    cout << "p(2) = " << p(2) << endl;

    vector<double> grid(3);
    grid[0] = 1;
    grid[1] = -2;
    grid[2] = 3;
    std::vector<Polynomial<double>> ls = lagrange_polynomials(grid);

    size_t idx = 0;
    for(auto &l : ls)
        cout << "l_" << ++idx << " = " << l << endl;

    return 0;
}

