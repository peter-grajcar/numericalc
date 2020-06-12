#include <iostream>
#include "numericalc/Polynomial.hpp"

using namespace std;

int poly_test()
{
    Polynomial<double> p(4, (double []){0, -1, 2, 3});

    cout << "p = " << p << endl;

    return 0;
}

