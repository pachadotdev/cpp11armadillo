#include "00_main.h"

// The same example from the first script but using QR instead of directly
// obtaining the inverse

Mat<double> ols_qr_(const doubles_matrix<>& y, const doubles_matrix<>& x,
                    const bool econ) {
  Mat<double> Y = as_Mat(y);  // Col<double> Y = as_Col(y); also works
  Mat<double> X = as_Mat(x);

  // no need to define the dimensions of Q and R
  // qr() will automatically initialize them
  Mat<double> Q;
  Mat<double> R;

  bool computable;

  if (!econ) {
    computable = qr(Q, R, X);
  } else {
    computable = qr_econ(Q, R, X);
  }

  if (!computable) {
    stop("QR decomposition failed");
  } else {
    return solve(R, Q.t() * Y);
  }
}

[[cpp11::register]] doubles_matrix<> ols_qr_mat(const doubles_matrix<>& y,
                                                const doubles_matrix<>& x,
                                                const bool econ) {
  Mat<double> beta = ols_qr_(y, x, econ);
  return as_doubles_matrix(beta);
}

[[cpp11::register]] doubles ols_qr_dbl(const doubles_matrix<>& y,
                                       const doubles_matrix<>& x, const bool econ) {
  Mat<double> beta = ols_qr_(y, x, econ);
  return as_doubles(beta);
}
