#include "00_main.h"

[[cpp11::register]] doubles_matrix<> capm(const doubles_matrix<>& r,
                                          const doubles_matrix<>& m, double f) {
  Mat<double> R = as_Mat(r);
  Mat<double> M = as_Mat(m);

  Mat<double> F = ones<Mat<double>>(R.n_cols, 1) * f;
  Mat<double> M_avg =
      ones<Mat<double>>(R.n_cols, 1) * as_scalar(mean(M, 0));  // Market average return

  Mat<double> beta = cov(R, M) / as_scalar(var(M));  // CAPM betas

  Mat<double> out = F + beta % (M_avg - F);  // Expected returns

  return as_doubles_matrix(out);
}
