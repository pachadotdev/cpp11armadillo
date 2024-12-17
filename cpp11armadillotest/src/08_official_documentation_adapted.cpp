#include "00_main.h"

[[cpp11::register]] doubles_matrix<> matrix_fun1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++

  double x = A(1, 2);  // access an element
  A = A + x;           // scalar addition

  mat B = A + A;  // matrix addition
  mat C = A * B;  // matrix multiplication
  mat D = A % B;  // element-wise matrix multiplication

  mat res = B + C + D;

  return as_doubles_matrix(res);  // convert from C++ to R
}

[[cpp11::register]] list matrix_fun2_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);
  mat B = A + A;

  cx_mat X(A, B);  // construct a complex matrix out of two real matrices

  B.zeros();           // set all elements to zero
  B.set_size(10, 10);  // resize the matrix
  B.ones(5, 6);        // same as mat B(5, 6, fill::ones)

  mat::fixed<5, 6> F;  // fixed size matrix

  double aux_mem[24];               // auxiliary memory
  mat H(&aux_mem[0], 4, 6, false);  // use auxiliary memory

  X = X + F.submat(0, 0, 4, 4) + H(1, 2);

  Mat<double> res_real = real(X);
  Mat<double> res_imag = imag(X);

  writable::list res;
  res.push_back({"real"_nm = as_doubles_matrix(res_real)});
  res.push_back({"imag"_nm = as_doubles_matrix(res_imag)});

  return res;
}

[[cpp11::register]] doubles column_fun1_(const doubles& x, const doubles& y) {
  vec X = as_Col(x);  // convert from R to C++
  vec Y = as_Col(y);

  mat A(10, 10, fill::randu);
  vec Z = A.col(5);  // extract a column vector

  Z = Z + Y + X;

  return as_doubles(Z);  // convert from C++ to R
}

[[cpp11::register]] doubles row_fun1_(const doubles& x, const doubles& y) {
  vec X = as_Col(x);  // convert from R to C++
  vec Y = as_Col(y);

  mat A(10, 10, fill::randu);

  rowvec Z = A.row(5);    // extract a row vector
  Z = Z + Y.t() + X.t();  // transpose Y and X to be able to sum

  vec res = Z.t();

  return as_doubles(res);  // convert from C++ to R
}
