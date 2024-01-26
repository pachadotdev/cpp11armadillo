#include <armadillo.hpp>
#include <cpp11.hpp>
#include <cpp11armadillo.hpp>

using namespace arma;
using namespace cpp11;
using namespace std;

[[cpp11::register]] doubles_matrix<> ols_mat(const doubles_matrix<>& y,
                                             const doubles_matrix<>& x) {
  Mat<double> Y = as_Mat(y);
  Mat<double> X = as_Mat(x);

  Mat<double> XtX = X.t() * X;
  Mat<double> XtX_inv = inv(XtX);
  Mat<double> beta = XtX_inv * X.t() * Y;

  return as_doubles_matrix(beta);
}

[[cpp11::register]] doubles ols_double(const doubles_matrix<>& y,
                                       const doubles_matrix<>& x) {
  Mat<double> Y = as_Mat(y);
  Mat<double> X = as_Mat(x);

  Mat<double> XtX = X.t() * X;
  Mat<double> XtX_inv = inv(XtX);
  Mat<double> beta = XtX_inv * X.t() * Y;

  return as_doubles(beta);
}
