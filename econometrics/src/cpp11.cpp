// Generated by cpp11: do not edit by hand
// clang-format off


#include "cpp11/declarations.hpp"
#include <R_ext/Visibility.h>

// chapter-3.cpp
doubles_matrix<> ols_mat_(const doubles_matrix<>& y, const doubles_matrix<>& x);
extern "C" SEXP _econometrics_ols_mat_(SEXP y, SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(ols_mat_(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(y), cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x)));
  END_CPP11
}
// chapter-3.cpp
double influence_dbl_(const doubles_matrix<>& y, const doubles_matrix<>& x);
extern "C" SEXP _econometrics_influence_dbl_(SEXP y, SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(influence_dbl_(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(y), cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x)));
  END_CPP11
}
// chapter-4.cpp
doubles_matrix<> stderr_dbl_(const doubles_matrix<>& y, const doubles_matrix<>& x);
extern "C" SEXP _econometrics_stderr_dbl_(SEXP y, SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(stderr_dbl_(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(y), cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x)));
  END_CPP11
}
// chapter-4.cpp
doubles_matrix<> beta_stderr_dbl_(const doubles_matrix<>& y, const doubles_matrix<>& x, const doubles_matrix<>& z);
extern "C" SEXP _econometrics_beta_stderr_dbl_(SEXP y, SEXP x, SEXP z) {
  BEGIN_CPP11
    return cpp11::as_sexp(beta_stderr_dbl_(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(y), cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x), cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(z)));
  END_CPP11
}
// chapter-4.cpp
doubles_matrix<> ddk_dbl_(const doubles_matrix<>& y, const doubles_matrix<>& x, const doubles_matrix<>& z);
extern "C" SEXP _econometrics_ddk_dbl_(SEXP y, SEXP x, SEXP z) {
  BEGIN_CPP11
    return cpp11::as_sexp(ddk_dbl_(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(y), cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x), cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(z)));
  END_CPP11
}

extern "C" {
static const R_CallMethodDef CallEntries[] = {
    {"_econometrics_beta_stderr_dbl_", (DL_FUNC) &_econometrics_beta_stderr_dbl_, 3},
    {"_econometrics_ddk_dbl_",         (DL_FUNC) &_econometrics_ddk_dbl_,         3},
    {"_econometrics_influence_dbl_",   (DL_FUNC) &_econometrics_influence_dbl_,   2},
    {"_econometrics_ols_mat_",         (DL_FUNC) &_econometrics_ols_mat_,         2},
    {"_econometrics_stderr_dbl_",      (DL_FUNC) &_econometrics_stderr_dbl_,      2},
    {NULL, NULL, 0}
};
}

extern "C" attribute_visible void R_init_econometrics(DllInfo* dll){
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
  R_forceSymbols(dll, TRUE);
}
