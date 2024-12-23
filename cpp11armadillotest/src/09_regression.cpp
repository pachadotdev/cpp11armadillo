#include "00_main.h"

vec ols_fit(const Mat<double>& X, const Col<double>& Y) {
  // QR decomposition
  mat Q, R;
  qr_econ(Q, R, X);

  // Least Squares Problem
  vec betas = solve(trimatu(R), Q.t() * Y);

  return betas;
}

[[cpp11::register]] doubles ols_(const doubles_matrix<>& x, const doubles& y) {
  mat X = as_Mat(x);
  vec Y = as_Col(y);
  return as_doubles(ols_fit(X, Y));
}

vec ols_weighted_fit(const Mat<double>& X, const Col<double>& Y, const Col<double>& W) {
  // Create a diagonal matrix from the weight vector
  mat W_diag = diagmat(W);

  // Weighted least squares problem
  mat XTWX = X.t() * W_diag * X;
  vec XTWY = X.t() * W_diag * Y;

  // Solve the system
  vec betas = solve(XTWX, XTWY);

  return betas;
}

vec poisson_fit(const Mat<double>& X, const Col<double>& Y) {
  // Data transformation
  vec MU = Y + 0.1;  // Initial guess for MU
  vec ETA = log(MU);
  vec Z = ETA + (Y - MU) / MU;

  // Iterate with initial values for the difference and the sum of sq residuals
  double dif = 1;
  double rss = 1;
  double tol = 1e-10;

  vec W;
  vec betas, res;
  double rss2;

  while (abs(dif) > tol) {
    W = MU;  // Weights are the current estimates of MU
    betas = ols_weighted_fit(X, Z, W);
    ETA = X * betas;
    MU = exp(ETA);
    Z = ETA + (Y - MU) / MU;
    res = Y - MU;
    rss2 = sum(res % res);
    dif = rss2 - rss;
    rss = rss2;
  }

  return betas;
}

[[cpp11::register]] doubles poisson_(const doubles_matrix<>& x, const doubles& y) {
  mat X = as_Mat(x);
  vec Y = as_Col(y);
  return as_doubles(poisson_fit(X, Y));
}
