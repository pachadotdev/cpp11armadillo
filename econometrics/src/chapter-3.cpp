#include "00_main.h"

Mat<double> ols_(const Mat<double>& Y, const Mat<double>& X) {
  Mat<double> XtX = X.t() * X;             // X'X
  Mat<double> XtX_inv = inv(XtX);          // (X'X)^(-1)
  Mat<double> beta = XtX_inv * X.t() * Y;  // (X'X)^(-1)(X'Y)

  return beta;
}

[[cpp11::register]] doubles_matrix<> ols_mat_(const doubles_matrix<>& y,
                                              const doubles_matrix<>& x) {
  Mat<double> Y = as_Mat(y);  // Col<double> Y = as_Col(y); also works
  Mat<double> X = as_Mat(x);
  Mat<double> beta = ols_(Y, X);
  return as_doubles_matrix(beta);
}

double influence_(const doubles_matrix<>& y, const doubles_matrix<>& x) {
  Mat<double> Y = as_Mat(y);
  Mat<double> X = as_Mat(x);

  Mat<double> e = Y - (X * ols_(Y, X));
  Mat<double> XXi = inv(X.t() * X);
  Mat<double> leverage = sum(X % (X * XXi), 1);
  Mat<double> ones = Mat<double>(Y.n_rows, 1, fill::ones);
  Mat<double> d = (leverage % e) / (ones - leverage);

  return as_scalar(max(abs(d)));
}

[[cpp11::register]] double influence_dbl_(const doubles_matrix<>& y,
                                          const doubles_matrix<>& x) {
  return influence_(y, x);
}
