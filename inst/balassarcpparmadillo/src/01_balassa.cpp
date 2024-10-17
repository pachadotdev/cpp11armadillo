#include <RcppArmadillo.h>
using namespace Rcpp;
using namespace arma;

// [[Rcpp::export]]
NumericMatrix balassa_arma_(const NumericMatrix& x) {
  mat X = as<mat>(x);
  mat B = X.each_col() / sum(X, 1);
  B = B.each_row() / (sum(X, 0) / accu(X));
  B.elem(find(B < 1)).zeros();
  B.elem(find(B >= 1)).ones();
  return wrap(B);
}
