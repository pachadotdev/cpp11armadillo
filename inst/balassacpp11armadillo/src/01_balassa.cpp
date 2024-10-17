#include <cpp11.hpp>
#include <cpp11armadillo.hpp>
using namespace cpp11;
using namespace arma;

[[cpp11::register]] doubles_matrix<> balassa_arma_(const doubles_matrix<>& x) {
  mat X = as_Mat(x);
  mat B = X.each_col() / sum(X, 1);
  B = B.each_row() / (sum(X, 0) / accu(X));
  B.elem(find(B < 1)).zeros();
  B.elem(find(B >= 1)).ones();
  return as_doubles_matrix(B);
}
