// Generated by cpp11: do not edit by hand
// clang-format off


#include "cpp11/declarations.hpp"
#include <R_ext/Visibility.h>

// 01_ols.cpp
doubles_matrix<> ols_mat(const doubles_matrix<>& y, const doubles_matrix<>& x);
extern "C" SEXP _cpp11armadillotest_ols_mat(SEXP y, SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(ols_mat(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(y), cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x)));
  END_CPP11
}
// 01_ols.cpp
doubles ols_dbl(const doubles_matrix<>& y, const doubles_matrix<>& x);
extern "C" SEXP _cpp11armadillotest_ols_dbl(SEXP y, SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(ols_dbl(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(y), cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x)));
  END_CPP11
}
// 02_eigen.cpp
doubles_matrix<> eigen_sym_mat(const doubles_matrix<>& x);
extern "C" SEXP _cpp11armadillotest_eigen_sym_mat(SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(eigen_sym_mat(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x)));
  END_CPP11
}
// 02_eigen.cpp
doubles eigen_sym_dbl(const doubles_matrix<>& x);
extern "C" SEXP _cpp11armadillotest_eigen_sym_dbl(SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(eigen_sym_dbl(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x)));
  END_CPP11
}
// 02_eigen.cpp
list eigen_gen_mat(const doubles_matrix<>& x);
extern "C" SEXP _cpp11armadillotest_eigen_gen_mat(SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(eigen_gen_mat(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x)));
  END_CPP11
}
// 02_eigen.cpp
list eigen_gen_mat_complex_wrapper(const doubles_matrix<>& x);
extern "C" SEXP _cpp11armadillotest_eigen_gen_mat_complex_wrapper(SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(eigen_gen_mat_complex_wrapper(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x)));
  END_CPP11
}
// 02_eigen.cpp
list eigen_gen_dbl_complex_wrapper(const doubles_matrix<>& x);
extern "C" SEXP _cpp11armadillotest_eigen_gen_dbl_complex_wrapper(SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(eigen_gen_dbl_complex_wrapper(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x)));
  END_CPP11
}
// 02_eigen.cpp
list eigen_gen_no_wrapper(const doubles_matrix<>& x);
extern "C" SEXP _cpp11armadillotest_eigen_gen_no_wrapper(SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(eigen_gen_no_wrapper(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x)));
  END_CPP11
}
// 03_chol.cpp
doubles_matrix<> chol_mat(const doubles_matrix<>& x, std::string type);
extern "C" SEXP _cpp11armadillotest_chol_mat(SEXP x, SEXP type) {
  BEGIN_CPP11
    return cpp11::as_sexp(chol_mat(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x), cpp11::as_cpp<cpp11::decay_t<std::string>>(type)));
  END_CPP11
}
// 04_qr.cpp
doubles_matrix<> ols_qr_mat(const doubles_matrix<>& y, const doubles_matrix<>& x, const bool econ);
extern "C" SEXP _cpp11armadillotest_ols_qr_mat(SEXP y, SEXP x, SEXP econ) {
  BEGIN_CPP11
    return cpp11::as_sexp(ols_qr_mat(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(y), cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x), cpp11::as_cpp<cpp11::decay_t<const bool>>(econ)));
  END_CPP11
}
// 04_qr.cpp
doubles ols_qr_dbl(const doubles_matrix<>& y, const doubles_matrix<>& x, const bool econ);
extern "C" SEXP _cpp11armadillotest_ols_qr_dbl(SEXP y, SEXP x, SEXP econ) {
  BEGIN_CPP11
    return cpp11::as_sexp(ols_qr_dbl(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(y), cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x), cpp11::as_cpp<cpp11::decay_t<const bool>>(econ)));
  END_CPP11
}
// 05_capm.cpp
doubles_matrix<> capm(const doubles_matrix<>& r, const doubles_matrix<>& m, double f);
extern "C" SEXP _cpp11armadillotest_capm(SEXP r, SEXP m, SEXP f) {
  BEGIN_CPP11
    return cpp11::as_sexp(capm(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(r), cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(m), cpp11::as_cpp<cpp11::decay_t<double>>(f)));
  END_CPP11
}
// 06_typedefs.cpp
doubles typedef_Col_double(const doubles& x);
extern "C" SEXP _cpp11armadillotest_typedef_Col_double(SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(typedef_Col_double(cpp11::as_cpp<cpp11::decay_t<const doubles&>>(x)));
  END_CPP11
}
// 06_typedefs.cpp
integers typedef_Col_int(const integers& x);
extern "C" SEXP _cpp11armadillotest_typedef_Col_int(SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(typedef_Col_int(cpp11::as_cpp<cpp11::decay_t<const integers&>>(x)));
  END_CPP11
}
// 06_typedefs.cpp
integers typedef_uvec(const integers& x);
extern "C" SEXP _cpp11armadillotest_typedef_uvec(SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(typedef_uvec(cpp11::as_cpp<cpp11::decay_t<const integers&>>(x)));
  END_CPP11
}
// 06_typedefs.cpp
doubles_matrix<> typedef_Mat_double(const doubles_matrix<>& x);
extern "C" SEXP _cpp11armadillotest_typedef_Mat_double(SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(typedef_Mat_double(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x)));
  END_CPP11
}
// 06_typedefs.cpp
integers_matrix<> typedef_Mat_int(const integers_matrix<>& x);
extern "C" SEXP _cpp11armadillotest_typedef_Mat_int(SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(typedef_Mat_int(cpp11::as_cpp<cpp11::decay_t<const integers_matrix<>&>>(x)));
  END_CPP11
}
// 06_typedefs.cpp
doubles_matrix<> typedef_SpMat_double(const doubles_matrix<>& x);
extern "C" SEXP _cpp11armadillotest_typedef_SpMat_double(SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(typedef_SpMat_double(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(x)));
  END_CPP11
}
// 06_typedefs.cpp
integers_matrix<> typedef_SpMat_int(const integers_matrix<>& x);
extern "C" SEXP _cpp11armadillotest_typedef_SpMat_int(SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(typedef_SpMat_int(cpp11::as_cpp<cpp11::decay_t<const integers_matrix<>&>>(x)));
  END_CPP11
}
// 07_reproducibility.cpp
integers_matrix<> random_matrix_nxn(const int& n);
extern "C" SEXP _cpp11armadillotest_random_matrix_nxn(SEXP n) {
  BEGIN_CPP11
    return cpp11::as_sexp(random_matrix_nxn(cpp11::as_cpp<cpp11::decay_t<const int&>>(n)));
  END_CPP11
}
// 08_official_documentation_adapted.cpp
doubles_matrix<> matrix_fun1_(const doubles_matrix<>& a);
extern "C" SEXP _cpp11armadillotest_matrix_fun1_(SEXP a) {
  BEGIN_CPP11
    return cpp11::as_sexp(matrix_fun1_(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(a)));
  END_CPP11
}
// 08_official_documentation_adapted.cpp
list matrix_fun2_(const doubles_matrix<>& a);
extern "C" SEXP _cpp11armadillotest_matrix_fun2_(SEXP a) {
  BEGIN_CPP11
    return cpp11::as_sexp(matrix_fun2_(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(a)));
  END_CPP11
}
// 08_official_documentation_adapted.cpp
doubles column_fun1_(const doubles& x, const doubles& y);
extern "C" SEXP _cpp11armadillotest_column_fun1_(SEXP x, SEXP y) {
  BEGIN_CPP11
    return cpp11::as_sexp(column_fun1_(cpp11::as_cpp<cpp11::decay_t<const doubles&>>(x), cpp11::as_cpp<cpp11::decay_t<const doubles&>>(y)));
  END_CPP11
}
// 08_official_documentation_adapted.cpp
doubles row_fun1_(const doubles& x, const doubles& y);
extern "C" SEXP _cpp11armadillotest_row_fun1_(SEXP x, SEXP y) {
  BEGIN_CPP11
    return cpp11::as_sexp(row_fun1_(cpp11::as_cpp<cpp11::decay_t<const doubles&>>(x), cpp11::as_cpp<cpp11::decay_t<const doubles&>>(y)));
  END_CPP11
}
// 08_official_documentation_adapted.cpp
doubles_matrix<> cube_fun1_(const doubles_matrix<>& a, const doubles_matrix<>& b);
extern "C" SEXP _cpp11armadillotest_cube_fun1_(SEXP a, SEXP b) {
  BEGIN_CPP11
    return cpp11::as_sexp(cube_fun1_(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(a), cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(b)));
  END_CPP11
}
// 08_official_documentation_adapted.cpp
doubles_matrix<> field_fun1_(const doubles_matrix<>& a, const doubles_matrix<>& b);
extern "C" SEXP _cpp11armadillotest_field_fun1_(SEXP a, SEXP b) {
  BEGIN_CPP11
    return cpp11::as_sexp(field_fun1_(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(a), cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(b)));
  END_CPP11
}
// 08_official_documentation_adapted.cpp
integers attr_fun1_(const doubles_matrix<>& a);
extern "C" SEXP _cpp11armadillotest_attr_fun1_(SEXP a) {
  BEGIN_CPP11
    return cpp11::as_sexp(attr_fun1_(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(a)));
  END_CPP11
}
// 08_official_documentation_adapted.cpp
doubles_matrix<> access_fun1_(const doubles_matrix<>& a);
extern "C" SEXP _cpp11armadillotest_access_fun1_(SEXP a) {
  BEGIN_CPP11
    return cpp11::as_sexp(access_fun1_(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(a)));
  END_CPP11
}
// 08_official_documentation_adapted.cpp
doubles_matrix<> initialization_fun1_(const doubles_matrix<>& a);
extern "C" SEXP _cpp11armadillotest_initialization_fun1_(SEXP a) {
  BEGIN_CPP11
    return cpp11::as_sexp(initialization_fun1_(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(a)));
  END_CPP11
}
// 08_official_documentation_adapted.cpp
doubles_matrix<> zeros_fun1_(const doubles_matrix<>& a);
extern "C" SEXP _cpp11armadillotest_zeros_fun1_(SEXP a) {
  BEGIN_CPP11
    return cpp11::as_sexp(zeros_fun1_(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(a)));
  END_CPP11
}
// 08_official_documentation_adapted.cpp
doubles_matrix<> ones_fun1_(const doubles_matrix<>& a);
extern "C" SEXP _cpp11armadillotest_ones_fun1_(SEXP a) {
  BEGIN_CPP11
    return cpp11::as_sexp(ones_fun1_(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(a)));
  END_CPP11
}
// 08_official_documentation_adapted.cpp
doubles_matrix<> eye_fun1_(const doubles_matrix<>& a);
extern "C" SEXP _cpp11armadillotest_eye_fun1_(SEXP a) {
  BEGIN_CPP11
    return cpp11::as_sexp(eye_fun1_(cpp11::as_cpp<cpp11::decay_t<const doubles_matrix<>&>>(a)));
  END_CPP11
}

extern "C" {
static const R_CallMethodDef CallEntries[] = {
    {"_cpp11armadillotest_access_fun1_",                  (DL_FUNC) &_cpp11armadillotest_access_fun1_,                  1},
    {"_cpp11armadillotest_attr_fun1_",                    (DL_FUNC) &_cpp11armadillotest_attr_fun1_,                    1},
    {"_cpp11armadillotest_capm",                          (DL_FUNC) &_cpp11armadillotest_capm,                          3},
    {"_cpp11armadillotest_chol_mat",                      (DL_FUNC) &_cpp11armadillotest_chol_mat,                      2},
    {"_cpp11armadillotest_column_fun1_",                  (DL_FUNC) &_cpp11armadillotest_column_fun1_,                  2},
    {"_cpp11armadillotest_cube_fun1_",                    (DL_FUNC) &_cpp11armadillotest_cube_fun1_,                    2},
    {"_cpp11armadillotest_eigen_gen_dbl_complex_wrapper", (DL_FUNC) &_cpp11armadillotest_eigen_gen_dbl_complex_wrapper, 1},
    {"_cpp11armadillotest_eigen_gen_mat",                 (DL_FUNC) &_cpp11armadillotest_eigen_gen_mat,                 1},
    {"_cpp11armadillotest_eigen_gen_mat_complex_wrapper", (DL_FUNC) &_cpp11armadillotest_eigen_gen_mat_complex_wrapper, 1},
    {"_cpp11armadillotest_eigen_gen_no_wrapper",          (DL_FUNC) &_cpp11armadillotest_eigen_gen_no_wrapper,          1},
    {"_cpp11armadillotest_eigen_sym_dbl",                 (DL_FUNC) &_cpp11armadillotest_eigen_sym_dbl,                 1},
    {"_cpp11armadillotest_eigen_sym_mat",                 (DL_FUNC) &_cpp11armadillotest_eigen_sym_mat,                 1},
    {"_cpp11armadillotest_eye_fun1_",                     (DL_FUNC) &_cpp11armadillotest_eye_fun1_,                     1},
    {"_cpp11armadillotest_field_fun1_",                   (DL_FUNC) &_cpp11armadillotest_field_fun1_,                   2},
    {"_cpp11armadillotest_initialization_fun1_",          (DL_FUNC) &_cpp11armadillotest_initialization_fun1_,          1},
    {"_cpp11armadillotest_matrix_fun1_",                  (DL_FUNC) &_cpp11armadillotest_matrix_fun1_,                  1},
    {"_cpp11armadillotest_matrix_fun2_",                  (DL_FUNC) &_cpp11armadillotest_matrix_fun2_,                  1},
    {"_cpp11armadillotest_ols_dbl",                       (DL_FUNC) &_cpp11armadillotest_ols_dbl,                       2},
    {"_cpp11armadillotest_ols_mat",                       (DL_FUNC) &_cpp11armadillotest_ols_mat,                       2},
    {"_cpp11armadillotest_ols_qr_dbl",                    (DL_FUNC) &_cpp11armadillotest_ols_qr_dbl,                    3},
    {"_cpp11armadillotest_ols_qr_mat",                    (DL_FUNC) &_cpp11armadillotest_ols_qr_mat,                    3},
    {"_cpp11armadillotest_ones_fun1_",                    (DL_FUNC) &_cpp11armadillotest_ones_fun1_,                    1},
    {"_cpp11armadillotest_random_matrix_nxn",             (DL_FUNC) &_cpp11armadillotest_random_matrix_nxn,             1},
    {"_cpp11armadillotest_row_fun1_",                     (DL_FUNC) &_cpp11armadillotest_row_fun1_,                     2},
    {"_cpp11armadillotest_typedef_Col_double",            (DL_FUNC) &_cpp11armadillotest_typedef_Col_double,            1},
    {"_cpp11armadillotest_typedef_Col_int",               (DL_FUNC) &_cpp11armadillotest_typedef_Col_int,               1},
    {"_cpp11armadillotest_typedef_Mat_double",            (DL_FUNC) &_cpp11armadillotest_typedef_Mat_double,            1},
    {"_cpp11armadillotest_typedef_Mat_int",               (DL_FUNC) &_cpp11armadillotest_typedef_Mat_int,               1},
    {"_cpp11armadillotest_typedef_SpMat_double",          (DL_FUNC) &_cpp11armadillotest_typedef_SpMat_double,          1},
    {"_cpp11armadillotest_typedef_SpMat_int",             (DL_FUNC) &_cpp11armadillotest_typedef_SpMat_int,             1},
    {"_cpp11armadillotest_typedef_uvec",                  (DL_FUNC) &_cpp11armadillotest_typedef_uvec,                  1},
    {"_cpp11armadillotest_zeros_fun1_",                   (DL_FUNC) &_cpp11armadillotest_zeros_fun1_,                   1},
    {NULL, NULL, 0}
};
}

extern "C" attribute_visible void R_init_cpp11armadillotest(DllInfo* dll){
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
  R_forceSymbols(dll, TRUE);
}
