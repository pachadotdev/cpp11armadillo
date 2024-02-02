#include "00_main.h"

doubles_matrix<> leontief_inverse(const doubles_matrix<>& x, const doubles_matrix<>& d) {
  Mat<double> X = as_Mat(x);
  Mat<double> D = as_Mat(d);

  // Check dimensions
  bool X_square = (X.n_rows == X.n_cols);
  bool compatible_dimensions = (X.n_rows == D.n_rows);

  if (X_square == false) {
    stop("x must be square.");
  }
  if (compatible_dimensions == false) {
    stop("d must have the same number of elements as the number of rows in x.");
  }

  // Input requirement matrix
  Mat<double> Y = zeros(D.n_rows, D.n_rows);
  Y.each_col() += D;
  Mat<double> A = X / Y.t();

  // Identity matrix
  Mat<double> I = eye(X.n_rows, X.n_cols);

  // Leontief inverse
  Mat<double> out = inv(I - A);

  return as_doubles_matrix(out);
}
