#include "00_main.h"

Mat<double> ols2_(const doubles_matrix<>& y, const doubles_matrix<>& x) {
  Mat<double> Y = as_Mat(y);
  Mat<double> X = as_Mat(x);

  Mat<double> beta = ols_(Y, X);
  Mat<double> e = Y - (X * beta);
  Mat<double> XXi = inv(X.t() * X);
  Mat<double> leverage = sum(X % (X * XXi), 1);

  double n = Y.n_rows;  // using int then returns the wrong "a" value
  double k = X.n_cols;
  double sig2 = as_scalar((e.t() * e) / (n - k));

  Mat<double> ones = Mat<double>(1, k, fill::ones);
  Mat<double> xx = inv(X.t() * X);

  // Heteroskedastic formula
  Mat<double> v0 = xx * sig2;
  Mat<double> s0 = sqrt(v0.diag());

  // White formula
  Mat<double> u1 = X % (e * ones);
  Mat<double> v1 = xx * (u1.t() * u1) * xx;
  Mat<double> s1 = sqrt(v1.diag());

  // HC1 formula
  double a = n / (n - k);
  Mat<double> v1a = a * (xx * (u1.t() * u1) * xx);
  Mat<double> s1a = sqrt(v1a.diag());

  // HC2 formula
  Mat<double> u2 = X % ((e / sqrt(1 - leverage)) * ones);
  Mat<double> v2 = xx * (u2.t() * u2) * xx;
  Mat<double> s2 = sqrt(v2.diag());

  // HC3 formula
  Mat<double> u3 = X % ((e / (1 - leverage)) * ones);
  Mat<double> v3 = xx * (u3.t() * u3) * xx;
  Mat<double> s3 = sqrt(v3.diag());

  // Bind the results
  Mat<double> result = join_rows(s0, s1, s1a, s2);
  result = join_rows(result, s3);  // join_rows admits max 4 arguments
  return result.t();
}

[[cpp11::register]] doubles_matrix<> ols2_mat_(const doubles_matrix<>& y,
                                                 const doubles_matrix<>& x) {
  return as_doubles_matrix(ols2_(y, x));
}

Mat<double> cls_(const doubles_matrix<>& y, const doubles_matrix<>& x) {
  Mat<double> Y = as_Mat(y);
  Mat<double> X = as_Mat(x);

  Mat<double> beta = ols_(Y, X);
  Mat<double> e = Y - (X * beta);
  Mat<double> XXi = inv(X.t() * X);
  Mat<double> leverage = sum(X % (X * XXi), 1);

  int k = X.n_cols;

  Mat<double> ones = Mat<double>(1, k, fill::ones);
  Mat<double> xx = inv(X.t() * X);

  // HC2 formula
  Mat<double> u2 = X % ((e / sqrt(1 - leverage)) * ones);
  Mat<double> v2 = xx * (u2.t() * u2) * xx;
  Mat<double> s2 = sqrt(v2.diag());

  // Bind the results
  Mat<double> result = join_rows(beta, s2);
  return result;
}

[[cpp11::register]] doubles_matrix<> cls_mat_(const doubles_matrix<>& y,
                                                      const doubles_matrix<>& x) {
  return as_doubles_matrix(cls_(y, x));
}

Mat<double> ddk_(const doubles_matrix<>& y, const doubles_matrix<>& x,
                 const doubles_matrix<>& z) {
  Mat<double> Y = as_Mat(y);
  Mat<double> X = as_Mat(x);
  Mat<double> Z = as_Mat(z);

  int n = Y.n_rows;
  int k = X.n_cols;

  Mat<double> xx = X.t() * X;
  Mat<double> xx_inv = inv(xx);
  Mat<double> beta = ols_(Y, X);

  Mat<double> xe(n, k);
  for (int j = 0; j < k; j++) {
    xe.col(j) = X.col(j) % (Y - X * beta);
  }

  // Unique groups in Z
  Mat<double> Z_unique = unique(Z);
  int n_groups = Z_unique.n_rows;

  // Grouped sums
  Mat<double> xe_sum(n_groups, k, fill::zeros);
  for (int g = 0; g < n_groups; g++) {
    int group = Z_unique(g, 0);
    for (int i = 0; i < n; ++i) {
      if (Z(i, 0) == group) {
        xe_sum.row(g) += xe.row(i);
      }
    }
  }

  Mat<double> omega = xe_sum.t() * xe_sum;
  double scale = (n_groups / (n_groups - 1)) * ((n - 1) / (n - k));
  Mat<double> V_clustered = scale * (xx_inv * omega * xx_inv);
  Mat<double> se_clustered = sqrt(V_clustered.diag());

  return join_rows(beta, se_clustered);
}

[[cpp11::register]] doubles_matrix<> ddk_mat_(const doubles_matrix<>& y,
                                              const doubles_matrix<>& x,
                                              const doubles_matrix<>& z) {
  return as_doubles_matrix(ddk_(y, x, z));
}
