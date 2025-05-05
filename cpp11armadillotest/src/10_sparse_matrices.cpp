#include "00_main.h"

[[cpp11::register]] SEXP test_dgCMatrix_to_SpMat(SEXP x) {
  // Convert from dgCMatrix to SpMat
  SpMat<double> A = as_SpMat(x);

  // Optional: perform some operation on A
  // For example, multiply each element by 2
  A *= 1.0;

  // Convert back to dgCMatrix and return
  return as_dgCMatrix(A);
}

// [[cpp11::register]] SEXP sum_matrices_(SEXP x) {
//   // Convert from dgCMatrix to SpMat
//   SpMat<double> A = as_SpMat(x);

//   // Create a matrix B with a diagonal of random numbers
//   SpMat<double> B(A.n_rows, A.n_cols);
//   for (uword i = 0; i < A.n_rows; ++i) {
//     B(i, i) = randu<double>();
//   }

//   A += B;  // Add the two matrices

//   // Convert back to dgCMatrix and return
//   return as_dgCMatrix(A);
// }
