#include "00_main.h"

// Symmetric case

Mat<double> eigen_sym_(const doubles_matrix<>& x) {
  Mat<double> X = as_Mat(x);
  Mat<double> y = eig_sym(X);
  return y;
}

[[cpp11::register]] doubles_matrix<> eigen_sym_mat(const doubles_matrix<>& x) {
  Mat<double> y = eigen_sym_(x);
  return as_doubles_matrix(y);
}

[[cpp11::register]] doubles eigen_sym_dbl(const doubles_matrix<>& x) {
  Mat<double> y = eigen_sym_(x);
  return as_doubles(y);
}

// General case

[[cpp11::register]] list eigen_gen_mat(const doubles_matrix<>& x) {
  Mat<double> X = as_Mat(x);
  Mat<std::complex<double>> y = eig_gen(X);

  Mat<double> y_real = real(y);
  Mat<double> y_imag = imag(y);

  writable::list out;
  out.push_back({"real"_nm = as_doubles_matrix(y_real)});
  out.push_back({"imag"_nm = as_doubles_matrix(y_imag)});

  // as_doubles() also works
  // out.push_back({"real"_nm = as_doubles(y_real)});
  // out.push_back({"imag"_nm = as_doubles(y_imag)});

  return out;
}

[[cpp11::register]] list eigen_gen_mat_complex_wrapper(const doubles_matrix<>& x) {
  Mat<double> X = as_Mat(x);
  Mat<std::complex<double>> y = eig_gen(X);
  return as_complex_matrix(y);
}

[[cpp11::register]] list eigen_gen_dbl_complex_wrapper(const doubles_matrix<>& x) {
  Mat<double> X = as_Mat(x);
  Col<std::complex<double>> y = eig_gen(X);
  return as_complex_doubles(y);
}

[[cpp11::register]] list eigen_gen_no_wrapper(const doubles_matrix<>& x) {
  Mat<double> X = as_Mat(x);

  Mat<std::complex<double>> y = eig_gen(X);

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
