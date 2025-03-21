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

// sp_mat 	  =  	SpMat<double>
// sp_dmat 	  =  	SpMat<double>
// sp_fmat 	  =  	SpMat<float>
// sp_cx_mat 	=  	SpMat<cx_double>
// sp_cx_dmat =  	SpMat<cx_double>
// sp_cx_fmat =  	SpMat<cx_float>
// sp_umat 	  =  	SpMat<uword>
// sp_imat 	  =  	SpMat<sword>

// round decimals because of precision for the float type

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

// round decimals because of precision for the float type

[[cpp11::register]] list typedef_spmat_exchangeability(const doubles_matrix<>& x) {
  SpMat<double> x1 = as_SpMat(x);
  sp_dmat x2 = as_sp_dmat(x);
  sp_fmat x3 = as_sp_fmat(x);
  // sp_cx_mat x4 = as_sp_cx_mat(x);
  // sp_cx_dmat x5 = as_sp_cx_dmat(x);
  // sp_cx_fmat x6 = as_sp_cx_fmat(x);

  writable::list res(3);

  res[0] = as_doubles_matrix(x1);
  res[1] = as_doubles_matrix(x2);
  res[2] = as_doubles_matrix(x3);
  // res[3] = as_complex_matrix(x4);
  // res[4] = as_complex_matrix(x5);
  // res[5] = as_complex_matrix(x6);

  return res;
}

[[cpp11::register]] list typedef_spmat_int_exchangeability(const integers_matrix<>& x) {
  SpMat<int> x1 = as_SpMat(x);
  sp_umat x2 = as_sp_umat(x);
  sp_imat x3 = as_sp_imat(x);

  writable::list res(3);

  res[0] = as_integers_matrix(x1);
  res[1] = as_integers_matrix(x2);
  res[2] = as_integers_matrix(x3);

  return res;
}

[[cpp11::register]] bool typedef_equivalences(const doubles_matrix<>& x) {
  Mat<double> y1 = as_Mat(x);
  mat y2 = as_mat(x);
  Mat<double> y3 = as_cpp<Mat<double>>(x);
  mat y4 = as_cpp<mat>(x);

  return all(vectorise(y1 == y2)) && all(vectorise(y1 == y3)) && all(vectorise(y1 == y4));
}
