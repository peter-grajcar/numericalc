#include <iostream>
#include "numericalc/Matrix.hpp"
#include "numericalc/decomposition/lu.hpp"
#include "numericalc/norm/p_norm.hpp"
#include "numericalc/norm/max_norm.hpp"
using namespace std;

using dMatrix = Matrix<double>;

int main()
{
    dMatrix A(2, 2);
    dMatrix B = dMatrix::identity(2);

    dMatrix u(3, 1, (double []){1, 2, 3});
    dMatrix v(3, 1, (double[]){4, -1, 0});

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

    /* LU decomposition, both L and U are contained in one matrix */
    cout << "A = LU = " << endl << lu_decomposition(A) << endl;

    cout << "u = " << u.transpose() << endl;
    cout << "v = " << v.transpose() << endl;

    /* outer product */
    cout << "uv^T = " << endl << u * v.transpose() << endl;
    /* inner product, the result is matrix 1x1 so it can be cast to double */
    cout << "u^Tu = " << (double)(u.transpose() * u) << endl;
    /* euclidean norm of vector u, the result should be identical to the
     * previous one, but this method should be faster. */
    cout << "|u|^2 = " << euclidean_norm_sqr(u) << endl;

    cout << "|u|_{max} = " << max_norm(u) << endl;

    return 0;
}