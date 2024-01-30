#include "00_main.h"

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

list eigen_gen_dbl_2(const doubles_matrix<>& x) {
  Mat<double> X = as_Mat(x);

  Mat<complex<double>> y = eig_gen(X);

  Col<double> y_real = real(y);
  Col<double> y_imag = imag(y);

  int n = y_real.n_rows;
  int m = 1;
  writable::doubles_matrix<> y_real2(n, m);
  writable::doubles_matrix<> y_imag2(n, m);

  for (int i = 0; i < n; ++i) {
    y_real2(i, 0) = y_real[i];
    y_imag2(i, 0) = y_imag[i];
  }

  writable::list out;
  out.push_back({"real"_nm = y_real2});
  out.push_back({"imag"_nm = y_imag2});

  return out;
}

list eigen_gen_mat_complex_wrapper_2(const doubles_matrix<>& x) {
  Mat<double> X = as_Mat(x);

  Col<complex<double>> y = eig_gen(X);

  list out = as_complex_matrix(y);

  return out;
}
