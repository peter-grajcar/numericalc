#include <iostream>
#include <iomanip>
#include "numericalc/Polynomial.hpp"
#include "numericalc/interpolation/lagrange.hpp"
#include "numericalc/dft/fft.hpp"
#include <cmath>

using namespace std;

int poly_test()
{
    Polynomial<double> p(4, (double []){0, -1, 2, 3});

    cout << "p = " << p << endl;
    cout << "p(2) = " << p(2) << endl << endl;

    vector<double> grid(3);
    grid[0] = 1;
    grid[1] = -2;
    grid[2] = 3;
    std::vector<Polynomial<double>> ls = lagrange_polynomials(grid);

    size_t idx = 0;
    for(auto &l : ls)
        cout << "l_" << ++idx << " = " << l << endl;

    cout << endl;

    Polynomial<complex<double>> q(4, (complex<double> []){0, -1, 2, 3});
    cout << "q              = " << setprecision(4) << fixed << q << endl;
    cout << "FFT(q)         = " << setprecision(4) << fixed << fft(q) << endl;
    cout << "FFT^-1(FFT(q)) = " << setprecision(4) << fixed << fft_inv(fft(q)) << endl;

    return 0;
}

