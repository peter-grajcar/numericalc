#include "numericalc/decomposition/lu.hpp"

template<typename T>
Matrix<T> lu_decomposition(const Matrix<T> a)
{
    assert(a.get_rows() == a.get_cols());
    Matrix<T> lu(a.get_rows(), a.get_cols());

    for (size_t m = 0; m < a.get_rows(); ++m) {
        for (size_t i = 0; i < a.get_cols(); ++i) {
            if (i > m) {
                T sum_col = 0;
                for (size_t k = 0; k + 1 < m; ++k)
                    sum_col += lu(i, k) * lu(k, m);
                lu(i, m) = (a(i, m) - sum_col) / lu(m, m);
            }
            if (i >= m) {
                T sum_row = 0;
                for (size_t k = 0; k < m; ++k)
                    sum_row += lu(m, k) * lu(k, i);
                lu(m, i) = a(m, i) - sum_row;
            }
        }
    }

    return lu;
}

template Matrix<double> lu_decomposition(const Matrix<double> a);
template Matrix<float> lu_decomposition(const Matrix<float> a);
template Matrix<int> lu_decomposition(const Matrix<int> a);
