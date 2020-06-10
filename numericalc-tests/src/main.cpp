#include <iostream>
#include "numericalc/Matrix.hpp"
using namespace std;

using dMatrix = Matrix<double>;

int main()
{
    dMatrix A(2, 2);
    dMatrix B = dMatrix::identity(2);

    A(0,0) = 1;
    A(0,1) = 2;
    A(1,0) = 3;
    A(1,1) = 4;

    cout << "A = " << endl << A << endl;
    cout << "B = " << endl << B << endl;

    cout << "2A = " << endl << 2 * A << endl;
    cout << "-A = " << endl << -A << endl;
    cout << "A^T = " << endl << A.transpose() << endl;
    cout << "A(1) = " << endl << A(1).asMatrix() << endl;
    cout << "A + B =" << endl << A + B << endl;
    cout << "A - B =" << endl << A - B << endl;
    cout << "A * B =" << endl << A * B << endl;

    return 0;
}