#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]

using namespace Rcpp;

// [[Rcpp::export]]
arma::mat eigen_sym_mat(const arma::mat& x) {
  arma::mat eigval = eig_sym(x);

  return eigval;
}
