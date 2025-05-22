#include <RcppArmadillo.h>
using namespace Rcpp;
using namespace arma;

// [[Rcpp::export]]
NumericVector bench_eig_rcpparmadillo_(const NumericMatrix& m) {
  mat M = as<mat>(m);
  colvec Y = eig_sym(M);
  return wrap(Y);
}

// [[Rcpp::export]]
double bench_multi_rcpparmadillo_(const NumericVector& p, const NumericVector& q,
                                  const NumericVector& r) {
  colvec P = as<colvec>(p);
  colvec Q = as<colvec>(q);
  colvec R = as<colvec>(r);
  return as_scalar(trans(P) * inv(diagmat(Q)) * R);
}
