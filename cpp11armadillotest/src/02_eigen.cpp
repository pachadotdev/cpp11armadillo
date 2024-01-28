#include "00_main.hpp"

doubles_matrix<> eigen_sym_mat(const doubles_matrix<>& x) {
  Mat<double> X = as_Mat(x);

  Mat<double> y = eig_sym(X);

  return as_doubles_matrix(y);
}

doubles eigen_sym_dbl(const doubles_matrix<>& x) {
  Mat<double> X = as_Mat(x);

  Mat<double> y = eig_sym(X);

  return as_doubles(y);
}

list eigen_gen_mat(const doubles_matrix<>& x) {
  Mat<double> X = as_Mat(x);

  Mat<complex<double>> y = eig_gen(X);

  Mat<double> y_real = real(y);
  Mat<double> y_imag = imag(y);

  writable::list out;
  out.push_back({"real"_nm = as_doubles_matrix(y_real)});
  out.push_back({"imag"_nm = as_doubles_matrix(y_imag)});

  return out;
}

list eigen_gen_mat_complex_wrapper(const doubles_matrix<>& x) {
  Mat<double> X = as_Mat(x);

  Mat<complex<double>> y = eig_gen(X);

  list out = as_complex_matrix(y);

  return out;
}

list eigen_gen_dbl(const doubles_matrix<>& x) {
  Mat<double> X = as_Mat(x);

  Mat<complex<double>> y = eig_gen(X);

  Col<double> y_real = real(y);
  Col<double> y_imag = imag(y);

  writable::list out;
  out.push_back({"real"_nm = as_doubles(y_real)});
  out.push_back({"imag"_nm = as_doubles(y_imag)});

  return out;
}

list eigen_gen_dbl_complex_wrapper(const doubles_matrix<>& x) {
  Mat<double> X = as_Mat(x);

  Col<complex<double>> y = eig_gen(X);

  list out = as_complex_doubles(y);

  return out;
}
