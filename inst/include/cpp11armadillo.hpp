#include <armadillo.hpp>
#include <cpp11.hpp>

using namespace arma;
using namespace cpp11;
using namespace std;

// R to Armadillo

Mat<double> doubles_matrix_to_Mat_(const doubles_matrix<>& A) {
  int n = A.nrow();
  int m = A.ncol();
  Mat<double> B(REAL(A.data()), n, m, false, false);
  return B;
}

Col<double> doubles_to_Vec_(const doubles& x) {
  int n = x.size();
  Col<double> y(REAL(x.data()), n, false);
  return y;
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
