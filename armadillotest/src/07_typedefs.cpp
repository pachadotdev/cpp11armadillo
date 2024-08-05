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
