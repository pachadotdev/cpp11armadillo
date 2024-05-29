#include "00_main.h"

[[cpp11::register]] doubles_matrix<> chol_mat(const doubles_matrix<>& x,
                                              std::string type) {
  Mat<double> X = as_Mat(x);

  Mat<double> res;

  if (type == "upper") {
    res = chol(X);
  } else if (type == "lower") {
    res = chol(X, "lower");
  } else {
    stop("Invalid type");
  }

  return as_doubles_matrix(res);
}
