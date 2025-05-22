#include <cpp11.hpp>
#include <cpp11armadillo.hpp>
using namespace cpp11;
using namespace arma;

[[cpp11::register]] doubles bench_eig_cpp11armadillo_(const doubles_matrix<>& m) {
  mat M = as_Mat(m);
  colvec Y = eig_sym(M);
  return as_doubles(Y);
}

[[cpp11::register]] double bench_multi_cpp11armadillo_(const doubles& p, const doubles& q,
                                                       const doubles& r) {
  colvec P = as_Col(p);
  colvec Q = as_Col(q);
  colvec R = as_Col(r);
  return as_scalar(trans(P) * inv(diagmat(Q)) * R);
}
