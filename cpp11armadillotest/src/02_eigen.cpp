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

// list eigen_gen_mat(const doubles_matrix<>& x) {
//   Mat<double> X = as_Mat(x);

//   Mat<complex<double>> y = eig_gen(X);

//   Mat<double> y_real = real(y);
//   Mat<double> y_imag = imag(y);

//   cout << "y_real: " << y_real << endl;
//   cout << "y_imag: " << y_imag << endl;

//   writable::list out;
//   out.push_back({"real"_nm = as_doubles(y_real)});
//   // out.push_back({"imag"_nm = as_doubles(y_imag)});

//   return out;
// }

// [[cpp11::register]] doubles eigen_gen_dbl(const doubles_matrix<>& x) {
//   Mat<double> X = as_Mat(x);

//   Mat<complex<double>> y = eig_gen(X);

//   return as_doubles(y);
// }
