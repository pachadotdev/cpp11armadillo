#include "00_main.hpp"

[[cpp11::register]] doubles_matrix<> eigen_sym_mat(const doubles_matrix<>& x);
[[cpp11::register]] doubles eigen_sym_dbl(const doubles_matrix<>& x);
[[cpp11::register]] list eigen_gen_mat(const doubles_matrix<>& x);
[[cpp11::register]] list eigen_gen_dbl(const doubles_matrix<>& x);
[[cpp11::register]] list eigen_gen_mat_complex_wrapper(
    const doubles_matrix<>& x);
[[cpp11::register]] list eigen_gen_dbl_complex_wrapper(
    const doubles_matrix<>& x);

[[cpp11::register]] doubles_matrix<> ols_mat(const doubles_matrix<>& y,
                                             const doubles_matrix<>& x);
[[cpp11::register]] doubles ols_dbl(const doubles_matrix<>& y,
                                    const doubles_matrix<>& x);
