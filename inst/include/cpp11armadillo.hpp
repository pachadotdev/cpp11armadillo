#include <armadillo.hpp>
#include <cpp11.hpp>

using namespace arma;
using namespace cpp11;
using namespace std;

// R to Armadillo

Col<double> doubles_to_Vec_(const doubles& x) {
  int n = x.size();
  Col<double> y(REAL(x.data()), n, false);
  return y;
}

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

// Armadillo to R

doubles_matrix<> Mat_to_doubles_matrix_(const Mat<double>& A) {
  int n = A.n_rows;
  int m = A.n_cols;

  writable::doubles_matrix<> B(n, m);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      double a_ij = A(i, j);
      B(i, j) = a_ij;
    }
  }

  return B;
}

doubles Vec_to_doubles_(const Col<double>& x) {
  int n = x.n_rows;

  writable::doubles y(n);

  for (int i = 0; i < n; ++i) {
    double x_i = x[i];
    y[i] = x_i;
  }

  return y;
}

doubles_matrix<> Vec_to_doubles_matrix_(const Col<double>& x) {
  int n = x.n_rows;
  int m = 1;

  writable::doubles_matrix<> Y(n, m);

  for (int i = 0; i < n; ++i) {
    double x_i = x[i];
    Y(i, 0) = x_i;
  }

  return Y;
}
