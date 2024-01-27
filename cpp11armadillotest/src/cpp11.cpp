// Generated by cpp11: do not edit by hand
// clang-format off


#include "cpp11/declarations.hpp"
#include <R_ext/Visibility.h>

// 00_main.cpp
doubles_matrix<> eigen_sym_mat(const doubles_matrix<>& x);
extern "C" SEXP _cpp11armadillotest_eigen_sym_mat(SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(eigen_sym_mat(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x)));
  END_CPP11
}
// 00_main.cpp
doubles eigen_sym_dbl(const doubles_matrix<>& x);
extern "C" SEXP _cpp11armadillotest_eigen_sym_dbl(SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(eigen_sym_dbl(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x)));
  END_CPP11
}
// 00_main.cpp
doubles_matrix<> eigen_gen_mat(const doubles_matrix<>& x);
extern "C" SEXP _cpp11armadillotest_eigen_gen_mat(SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(eigen_gen_mat(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x)));
  END_CPP11
}
// 00_main.cpp
doubles_matrix<> ols_mat(const doubles_matrix<>& y, const doubles_matrix<>& x);
extern "C" SEXP _cpp11armadillotest_ols_mat(SEXP y, SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(ols_mat(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(y), cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x)));
  END_CPP11
}
// 00_main.cpp
doubles ols_dbl(const doubles_matrix<>& y, const doubles_matrix<>& x);
extern "C" SEXP _cpp11armadillotest_ols_dbl(SEXP y, SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(ols_dbl(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(y), cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x)));
  END_CPP11
}

extern "C" {
static const R_CallMethodDef CallEntries[] = {
    {"_cpp11armadillotest_eigen_gen_mat", (DL_FUNC) &_cpp11armadillotest_eigen_gen_mat, 1},
    {"_cpp11armadillotest_eigen_sym_dbl", (DL_FUNC) &_cpp11armadillotest_eigen_sym_dbl, 1},
    {"_cpp11armadillotest_eigen_sym_mat", (DL_FUNC) &_cpp11armadillotest_eigen_sym_mat, 1},
    {"_cpp11armadillotest_ols_dbl",       (DL_FUNC) &_cpp11armadillotest_ols_dbl,       2},
    {"_cpp11armadillotest_ols_mat",       (DL_FUNC) &_cpp11armadillotest_ols_mat,       2},
    {NULL, NULL, 0}
};
}

extern "C" attribute_visible void R_init_cpp11armadillotest(DllInfo* dll){
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
  R_forceSymbols(dll, TRUE);
}
