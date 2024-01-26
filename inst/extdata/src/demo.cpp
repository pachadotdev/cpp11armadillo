#include <armadillo.hpp>
#include <cpp11.hpp>
#include <cpp11armadillo.hpp>

using namespace arma;
using namespace cpp11;
using namespace std;

[[cpp11::register]] doubles_matrix<> ols_(const doubles_matrix<>& y,
                                          const doubles_matrix<>& x) {
  Mat<double> Y = doubles_matrix_to_Mat_(y);
  Mat<double> X = doubles_matrix_to_Mat_(x);

  Mat<double> XtX = X.t() * X;
  Mat<double> XtX_inv = inv(XtX);
  Mat<double> beta = XtX_inv * X.t() * Y;

  return Mat_to_doubles_matrix_(beta);
}
