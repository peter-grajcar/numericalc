#include <iostream>
#include <iomanip>
#include "numericalc/Polynomial.hpp"
#include "numericalc/interpolation/lagrange.hpp"
#include "numericalc/dft/dft.hpp"
#include "numericalc/dft/fft.hpp"
#include <cmath>

using namespace std;

int poly_test()
{
    Polynomial<double> p(4, (double []){1, -1, 2, 3});

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

    ios::fmtflags f(cout.flags());
    cout << "q              = " << setprecision(2) << fixed << q << endl;
    cout << "FFT(q)         = " << setprecision(2) << fixed << fft(q) << endl;
    cout << "FFT^-1(FFT(q)) = " << setprecision(2) << fixed << fft_inv(fft(q)) << endl;
    cout << "DFT(q)         = " << setprecision(2) << fixed << dft(q) << endl;
    cout << "DFT^-1(DFT(q)) = " << setprecision(2) << fixed << dft(dft_inv(q)) << endl << endl;
    cout.flags(f);

    Polynomial<double> r(3, (double []){2, -1, 3});
    cout << setprecision(3) << fixed;
    cout << "p = " << p << endl;
    cout << "r = " << r << endl;
    cout << "p * r = " << p * r << endl;
    cout << "p * r = " << fft_mult(p, r) << endl;

    return 0;
}

