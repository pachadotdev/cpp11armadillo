#include "00_main.h"

[[cpp11::register]] SEXP implicit_conversion_double(SEXP x) {
  arma::mat result = cpp11::as_cpp<arma::mat>(x);
  return cpp11::as_sexp(result);
}

[[cpp11::register]] SEXP implicit_conversion_float(SEXP x) {
  arma::fmat result = cpp11::as_cpp<arma::fmat>(x);
  return cpp11::as_sexp(result);
}

[[cpp11::register]] SEXP implicit_conversion_int(SEXP x) {
  arma::imat result = cpp11::as_cpp<arma::imat>(x);
  return cpp11::as_sexp(result);
}

[[cpp11::register]] SEXP implicit_conversion_uint(SEXP x) {
  arma::umat result = cpp11::as_cpp<arma::umat>(x);
  return cpp11::as_sexp(result);
}
