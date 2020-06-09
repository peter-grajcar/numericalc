#include <iostream>
#include "numericalc/matrix.hpp"
using namespace std;

int main()
{
    Matrix A(2, 2);
    Matrix B(2, 2);


    A[0][0] = 1;
    A[0][1] = 2;
    A[1][0] = 3;
    A[1][1] = 4;

    B[0][0] = 1;
    B[0][1] = 0;
    B[1][0] = 0;
    B[1][1] = 1;


    cout << "A = " << endl << A << endl;
    cout << "B = " << endl << B << endl;

    cout << "A + B =" << endl << A + B << endl;

    return 0;
}