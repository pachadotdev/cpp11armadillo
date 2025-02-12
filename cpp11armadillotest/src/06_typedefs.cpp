#include "00_main.h"

// vec = colvec = Col<double>

[[cpp11::register]] doubles typedef_Col_double(const doubles& x) {
  Col<double> y = as_Col(x);
  return as_doubles(y);
}

[[cpp11::register]] integers typedef_Col_int(const integers& x) {
  Col<int> y = as_Col(x);
  return as_integers(y);
}

[[cpp11::register]] integers typedef_uvec(const integers& x) {
  uvec y = as_uvec(x);
  return as_integers(y);
}

[[cpp11::register]] doubles_matrix<> typedef_Mat_double(const doubles_matrix<>& x) {
  Mat<double> y = as_Mat(x);
  return as_doubles_matrix(y);
}

[[cpp11::register]] integers_matrix<> typedef_Mat_int(const integers_matrix<>& x) {
  Mat<int> y = as_Mat(x);
  return as_integers_matrix(y);
}

[[cpp11::register]] doubles_matrix<> typedef_SpMat_double(const doubles_matrix<>& x) {
  SpMat<double> y = as_SpMat(x);
  return as_doubles_matrix(y);
}

[[cpp11::register]] integers_matrix<> typedef_SpMat_int(const integers_matrix<>& x) {
  SpMat<int> y = as_SpMat(x);
  return as_integers_matrix(y);
}

// shortcuts

// mat 	   =  	Mat<double>
// dmat 	 =  	Mat<double>
// fmat 	 =  	Mat<float>
// cx_mat  =  	Mat<cx_double>
// cx_dmat =  	Mat<cx_double>
// cx_fmat =  	Mat<cx_float>
// umat 	 =  	Mat<uword>
// imat 	 =  	Mat<sword>

// round decimals because of precision
[[cpp11::register]] list typedef_dblmat_exchangeability(const doubles_matrix<>& x) {
  Mat<double> x1 = as_Mat(x);
  Mat<double> x2 = as_Mat(x);
  mat x3 = as_Mat(x);
  mat x4 = as_mat(x);
  dmat x5 = as_Mat(x);
  dmat x6 = as_mat(x);
  // fmat x7 = as_Mat(x);
  // fmat x8 = as_mat(x);
  fmat x9 = as_fmat(x);
  Mat<float> x10 = as_fmat(x);

  writable::list res(8);

  res[0] = as_doubles_matrix(x1);
  res[1] = as_doubles_matrix(x2);
  res[2] = as_doubles_matrix(x3);
  res[3] = as_doubles_matrix(x4);
  res[4] = as_doubles_matrix(x5);
  res[5] = as_doubles_matrix(x6);
  res[6] = as_doubles_matrix(x9);
  res[7] = as_doubles_matrix(x10);

  return res;
}

[[cpp11::register]] list typedef_intmat_exchangeability(const integers_matrix<>& x) {
  Mat<int> x1 = as_Mat(x);
  Mat<int> x2 = as_mat(x);
  umat x3 = as_umat(x);
  imat x4 = as_imat(x);

  writable::list res(4);

  res[0] = as_integers_matrix(x1);
  res[1] = as_integers_matrix(x2);
  res[2] = as_integers_matrix(x3);
  res[3] = as_integers_matrix(x4);

  return res;
}
