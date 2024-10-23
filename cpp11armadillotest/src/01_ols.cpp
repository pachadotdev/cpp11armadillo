#include "00_main.h"

Mat<double> ols_(const doubles_matrix<>& y, const doubles_matrix<>& x) {
  Mat<double> Y = as_Mat(y);  // Col<double> Y = as_Col(y); also works
  Mat<double> X = as_Mat(x);

  Mat<double> XtX = X.t() * X;             // X'X
  Mat<double> XtX_inv = inv(XtX);          // (X'X)^(-1)
  Mat<double> beta = XtX_inv * X.t() * Y;  // (X'X)^(-1)(X'Y)

  return beta;
}

[[cpp11::register]] doubles_matrix<> ols_mat_(const doubles_matrix<>& y,
                                             const doubles_matrix<>& x) {
  Mat<double> beta = ols_(y, x);
  return as_doubles_matrix(beta);
}

[[cpp11::register]] doubles ols_dbl_(const doubles_matrix<>& y,
                                    const doubles_matrix<>& x) {
  Mat<double> beta = ols_(y, x);
  return as_doubles(beta);
}
