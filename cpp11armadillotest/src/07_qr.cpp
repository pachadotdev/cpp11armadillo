#include "00_main.h"

list qr_mat(const doubles_matrix<>& x, bool econ) {
  Mat<double> X = as_Mat(x);

  // no need to define the dimensions of Q and R
  // qr() will automatically initialize them
  Mat<double> Q;
  Mat<double> R;

  bool computable;

  if (!econ) {
    computable = qr(Q, R, X);
  } else {
    computable = qr_econ(Q, R, X);
  }

  if (!computable) {
    stop("QR decomposition failed");
  } else {
    writable::list out;
    out.push_back({"Q"_nm = as_doubles_matrix(Q)});
    out.push_back({"R"_nm = as_doubles_matrix(R)});
    return out;
  }
}
