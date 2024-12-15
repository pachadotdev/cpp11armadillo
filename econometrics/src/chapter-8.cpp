#include "00_main.h"

Mat<double> ols3_(const doubles_matrix<>& y, const doubles_matrix<>& x) {
  Mat<double> Y = as_Mat(y);
  Mat<double> X = as_Mat(x);

  int n = x.nrow();
  int k = x.ncol();

  Mat<double> beta_ols = ols_(Y, X);
  Mat<double> e_ols = Y - (X * beta_ols);
  Mat<double> Xe_ols = X.each_col() % e_ols;
  Mat<double> invX = inv(X.t() * X);
  Mat<double> V_ols = (n / (n - k)) * invX * (Xe_ols.t() * Xe_ols) * invX;
  Mat<double> se_ols = sqrt(V_ols.diag());

  Mat<double> res = join_rows(beta_ols, se_ols);
  return res;
}

[[cpp11::register]] doubles_matrix<> ols3_mat_(const doubles_matrix<>& y,
                                              const doubles_matrix<>& x) {
  return as_doubles_matrix(ols3_(y, x));
}

Mat<double> cns_(const doubles_matrix<>& y, const doubles_matrix<>& x,
                 const doubles_matrix<>& r) {
  Mat<double> Y = as_Mat(y);
  Mat<double> X = as_Mat(x);
  Mat<double> R = as_Mat(r);

  int n = x.nrow();
  int k = x.ncol();

  Mat<double> invX = inv(X.t() * X);
  Mat<double> iR = invX * R * inv(R.t() * invX * R) * R.t();
  Mat<double> beta_ols = ols_(Y, X);
  Mat<double> beta_cns = beta_ols - (iR * beta_ols);
  Mat<double> e_cns = Y - (X * beta_cns);
  Mat<double> Xe_cns = X.each_col() % e_cns;
  Mat<double> V_tilde = (n / (n - k + 1)) * invX * (Xe_cns.t() * Xe_cns) * invX;
  Mat<double> V_cls = V_tilde - (iR * V_tilde) - (V_tilde * iR.t()) +
    (iR * V_tilde * iR.t());
  Mat<double> se_cns = sqrt(V_cls.diag());

  Mat<double> res = join_rows(beta_cns, se_cns);
  return res;
}

[[cpp11::register]] doubles_matrix<> cns_mat_(const doubles_matrix<>& y,
                                              const doubles_matrix<>& x,
                                              const doubles_matrix<>& r) {
  return as_doubles_matrix(cns_(y, x, r));
}

Mat<double> emd_(const doubles_matrix<>& y, const doubles_matrix<>& x,
                 const doubles_matrix<>& r) {
  Mat<double> Y = as_Mat(y);
  Mat<double> X = as_Mat(x);
  Mat<double> R = as_Mat(r);

  int n = x.nrow();
  int k = x.ncol();

  Mat<double> invX = inv(X.t() * X);
  Mat<double> beta_ols = ols_(Y, X);
  Mat<double> e_ols = Y - (X * beta_ols);
  Mat<double> Xe_ols = X.each_col() % e_ols;
  Mat<double> V_ols = (n / (n - k)) * invX * (Xe_ols.t() * Xe_ols) * invX;

  Mat<double> V_r = V_ols * R * inv(R.t() * V_ols * R) * R.t();
  Mat<double> beta_emd = beta_ols - V_r * beta_ols;
  Mat<double> e_emd = Y - (X * beta_emd);
  Mat<double> Xe_emd = X.each_col() % e_emd;

  Mat<double> V2 = (n / (n - k + 1)) * invX * (Xe_emd.t() * Xe_emd) * invX;
  Mat<double> V_emd = V2 - V2 * R * inv(R.t() * V2 * R) * R.t() * V2;
  Mat<double> se_emd = sqrt(V_emd.diag());

  Mat<double> res = join_rows(beta_emd, se_emd);
  return res;
}

[[cpp11::register]] doubles_matrix<> emd_mat_(const doubles_matrix<>& y,
                                              const doubles_matrix<>& x,
                                              const doubles_matrix<>& r) {
  return as_doubles_matrix(emd_(y, x, r));
}
