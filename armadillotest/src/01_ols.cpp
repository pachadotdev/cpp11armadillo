#include "00_main.h"

[[cpp11::register]] doubles_matrix<> ols_mat(const doubles_matrix<>& y,
                                             const doubles_matrix<>& x) {
  Mat<double> Y = as_Mat(y);
  Mat<double> X = as_Mat(x);

  Mat<double> XtX = X.t() * X;             // X'X
  Mat<double> XtX_inv = inv(XtX);          // (X'X)^(-1)
  Mat<double> beta = XtX_inv * X.t() * Y;  // (X'X)^(-1)(X'Y)

  return as_doubles_matrix(beta);
}

[[cpp11::register]] doubles ols_dbl(const doubles_matrix<>& y,
                                    const doubles_matrix<>& x) {
  Mat<double> Y = as_Mat(y);
  Mat<double> X = as_Mat(x);

  Mat<double> XtX = X.t() * X;
  Mat<double> XtX_inv = inv(XtX);
  Mat<double> beta = XtX_inv * X.t() * Y;

  return as_doubles(beta);
}

[[cpp11::register]] doubles ols_dbl2(const doubles& y, const doubles_matrix<>& x) {
  Mat<double> Y = as_Mat(y);
  Mat<double> X = as_Mat(x);

  Mat<double> XtX = X.t() * X;
  Mat<double> XtX_inv = inv(XtX);
  Mat<double> beta = XtX_inv * X.t() * Y;

  return as_doubles(beta);
}

[[cpp11::register]] doubles ols_dbl3(const doubles& y, const doubles_matrix<>& x) {
  Col<double> Y = as_Col(y);
  Mat<double> X = as_Mat(x);

  Mat<double> XtX = X.t() * X;
  Mat<double> XtX_inv = inv(XtX);
  Mat<double> beta = XtX_inv * X.t() * Y;

  return as_doubles(beta);
}
