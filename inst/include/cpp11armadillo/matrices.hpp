#pragma once

using namespace arma;
using namespace cpp11;
using namespace std;

////////////////////////////////////////////////////////////////
// R to Armadillo
////////////////////////////////////////////////////////////////

template <typename T>
Mat<T> as_Mat(const T& x) {
  // Generic implementation
  throw runtime_error("Cannot convert to Mat");
}

template <typename T, typename U>
Mat<T> as_Mat_(const U& x) {
  int n = x.nrow();
  int m = x.ncol();
  Mat<T> B((is_same<U, doubles_matrix<>>::value
                ? reinterpret_cast<T*>(REAL(x.data()))
                : reinterpret_cast<T*>(INTEGER(x.data()))),
           n, m, false, false);
  return B;
}

Mat<double> as_Mat(const doubles_matrix<>& x) {
  return as_Mat_<double, doubles_matrix<>>(x);
}

Mat<int> as_Mat(const integers_matrix<>& x) {
  return as_Mat_<int, integers_matrix<>>(x);
}

////////////////////////////////////////////////////////////////
// Armadillo to R
////////////////////////////////////////////////////////////////

template <typename T, typename U>
U Mat_to_dblint_matrix_(const Mat<T>& A) {
  int n = A.n_rows;
  int m = A.n_cols;

  typename conditional<is_same<U, doubles_matrix<>>::value,
                       writable::doubles_matrix<>,
                       writable::integers_matrix<>>::type B(n, m);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      typename conditional<is_same<U, doubles_matrix<>>::value, double,
                           int>::type a_ij = A(i, j);
      B(i, j) = a_ij;
    }
  }

  return B;
}

doubles_matrix<> as_doubles_matrix(const Mat<double>& A) {
  return Mat_to_dblint_matrix_<double, doubles_matrix<>>(A);
}

integers_matrix<> as_integers_matrix(const Mat<int>& A) {
  return Mat_to_dblint_matrix_<int, integers_matrix<>>(A);
}
