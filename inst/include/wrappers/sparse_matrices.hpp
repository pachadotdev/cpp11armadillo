#pragma once

using namespace arma;
using namespace cpp11;

#ifndef SPARSEMATRICES_HPP
#define SPARSEMATRICES_HPP

////////////////////////////////////////////////////////////////
// R to Armadillo
////////////////////////////////////////////////////////////////

template <typename T>
inline SpMat<T> as_SpMat(const T& x) {
  // Generic implementation
  throw std::runtime_error("Cannot convert to SpMat");
}

template <typename T, typename U>
inline SpMat<T> dblint_matrix_to_SpMat_(const U& x) {
  const size_t n = x.nrow();
  const size_t m = x.ncol();

  SpMat<T> y(n, m);

  std::vector<std::pair<size_t, size_t>> non_zero_positions;

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      if (x(i, j) != 0) {
        non_zero_positions.emplace_back(i, j);
      }
    }
  }

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (size_t k = 0; k < non_zero_positions.size(); ++k) {
    const auto& pos = non_zero_positions[k];
    y(pos.first, pos.second) = x(pos.first, pos.second);
  }

  return y;
}

template <typename T, typename U>
inline SpMat<T> dblint_to_SpMat_(const U& x) {
  const size_t n = x.size();

  SpMat<T> y(n, 1);

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (size_t i = 0; i < n; ++i) {
    y(i, 0) = x[i];
  }

  return y;
}

inline SpMat<double> as_SpMat(const doubles_matrix<>& x) {
  return dblint_matrix_to_SpMat_<double, doubles_matrix<>>(x);
}

inline SpMat<int> as_SpMat(const integers_matrix<>& x) {
  return dblint_matrix_to_SpMat_<int, integers_matrix<>>(x);
}

inline SpMat<double> as_SpMat(const doubles& x) {
  return dblint_to_SpMat_<double, doubles>(x);
}

inline SpMat<int> as_SpMat(const integers& x) {
  return dblint_to_SpMat_<int, integers>(x);
}

inline SpMat<double> as_sp_dmat(const doubles_matrix<>& x) { return as_SpMat(x); }
inline SpMat<float> as_sp_fmat(const doubles_matrix<>& x) {
  SpMat<double> y = dblint_matrix_to_SpMat_<double, doubles_matrix<>>(x);
  return arma::conv_to<SpMat<float>>::from(y);
}

inline SpMat<uword> as_sp_umat(const integers_matrix<>& x) {
  SpMat<int> y = dblint_matrix_to_SpMat_<int, integers_matrix<>>(x);
  return arma::conv_to<SpMat<uword>>::from(y);
}

inline SpMat<sword> as_sp_imat(const integers_matrix<>& x) {
  SpMat<int> y = dblint_matrix_to_SpMat_<int, integers_matrix<>>(x);
  return arma::conv_to<SpMat<sword>>::from(y);
}

////////////////////////////////////////////////////////////////
// Armadillo to R
////////////////////////////////////////////////////////////////

// Double/Integer

template <typename T, typename U>
inline U SpMat_to_dblint_matrix_(const SpMat<T>& A) {
  const size_t n = A.n_rows;
  const size_t m = A.n_cols;

  using dblint_matrix =
      typename std::conditional<std::is_same<U, doubles_matrix<>>::value,
                                writable::doubles_matrix<>,
                                writable::integers_matrix<>>::type;

  dblint_matrix B(n, m);

#ifdef _OPENMP
#pragma omp parallel for collapse(2) schedule(static)
#endif
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      B(i, j) = A(i, j);
    }
  }

  return B;
}

inline doubles_matrix<> as_doubles_matrix(const SpMat<double>& A) {
  return SpMat_to_dblint_matrix_<double, doubles_matrix<>>(A);
}

// Always provide for SpMat<int>
inline integers_matrix<> as_integers_matrix(const SpMat<int>& A) {
  return SpMat_to_dblint_matrix_<int, integers_matrix<>>(A);
}

// On 64-bit word systems, SpMat<sword> is SpMat<long>
#if defined(ARMA_64BIT_WORD)
inline integers_matrix<> as_integers_matrix(const SpMat<long>& A) {
  return SpMat_to_dblint_matrix_<long, integers_matrix<>>(A);
}
#endif

inline doubles_matrix<> as_doubles_matrix(const SpMat<float>& A) {
  SpMat<double> B = arma::conv_to<SpMat<double>>::from(A);
  return as_doubles_matrix(B);
}

// Complex

template <typename T>
inline list SpMat_to_complex_matrix_(const SpMat<T>& A) {
  SpMat<double> A_real = real(A);
  SpMat<double> A_imag = imag(A);

  writable::list B;
  B.push_back({"real"_nm = as_doubles_matrix(A_real)});
  B.push_back({"imag"_nm = as_doubles_matrix(A_imag)});

  return B;
}

inline list as_complex_matrix(const SpMat<std::complex<double>>& A) {
  return SpMat_to_complex_matrix_<std::complex<double>>(A);
}

#endif

////////////////////////////////////////////////////////////////
// dgCMatrix to Armadillo
////////////////////////////////////////////////////////////////

// reference:
// https://www.r-bloggers.com/2020/03/what-is-a-dgcmatrix-object-made-of-sparse-matrix-format-in-r/
// http://adv-r.had.co.nz/OO-essentials.html#s4

inline bool is_dgCMatrix(SEXP x) { return Rf_inherits(x, "dgCMatrix"); }

inline SpMat<double> as_SpMat(SEXP x) {
  if (!is_dgCMatrix(x)) {
    stop("Input is not a dgCMatrix");
  }

  // Extract the slots from dgCMatrix
  SEXP i_slot = R_do_slot(x, Rf_mkString("i"));      // Row indices
  SEXP p_slot = R_do_slot(x, Rf_mkString("p"));      // Column pointers
  SEXP x_slot = R_do_slot(x, Rf_mkString("x"));      // Values
  SEXP dim_slot = R_do_slot(x, Rf_mkString("Dim"));  // Dimensions

  // Dimensions
  int n_rows = INTEGER(dim_slot)[0];
  int n_cols = INTEGER(dim_slot)[1];

  // Row indices, column pointers and values
  int* row_indices = INTEGER(i_slot);
  int* col_ptrs = INTEGER(p_slot);
  double* values = REAL(x_slot);

  // Number of non-zero elements
  int nnz = LENGTH(x_slot);

  // Create a temporary array for row indices and column pointers
  arma::umat locations(2, nnz);
  arma::vec vals(nnz);

  // Convert CSC format to coordinate list format
  int k = 0;
  for (int j = 0; j < n_cols; j++) {
    for (int p = col_ptrs[j]; p < col_ptrs[j + 1]; p++) {
      locations(0, k) = row_indices[p];  // Row
      locations(1, k) = j;               // Column
      vals(k) = values[p];               // Value
      k++;
    }
  }

  // Create sparse matrix from locations and values
  return SpMat<double>(locations, vals, n_rows, n_cols);
}

////////////////////////////////////////////////////////////////
// SpMat to dgCMatrix
////////////////////////////////////////////////////////////////

inline SEXP as_dgCMatrix(const SpMat<double>& A) {
  // Create data in triplet format (COO)
  std::vector<int> i_vec, j_vec;
  std::vector<double> x_vec;

  i_vec.reserve(A.n_nonzero);
  j_vec.reserve(A.n_nonzero);
  x_vec.reserve(A.n_nonzero);

  // Extract non-zero elements
  for (uword col = 0; col < A.n_cols; col++) {
    for (SpMat<double>::const_iterator it = A.begin_col(col); it != A.end_col(col);
         ++it) {
      i_vec.push_back(it.row() + 1);  // 1-based indexing for R
      j_vec.push_back(col + 1);       // 1-based indexing for R
      x_vec.push_back(*it);
    }
  }

  // Create R vectors using cpp11 instead of low-level SEXP manipulation
  writable::integers i(i_vec.begin(), i_vec.end());
  writable::integers j(j_vec.begin(), j_vec.end());
  writable::doubles x(x_vec.begin(), x_vec.end());
  writable::integers dims = {static_cast<int>(A.n_rows), static_cast<int>(A.n_cols)};

  // Get R functions from base environment
  function getNamespace = function(Rf_findFun(Rf_install("getNamespace"), R_GlobalEnv));
  SEXP Matrix_ns = getNamespace("Matrix");

  function get = function(Rf_findFun(Rf_install("get"), R_GlobalEnv));
  SEXP sparseMatrix_fn = get("sparseMatrix", Matrix_ns);

  function sparseMatrix = function(sparseMatrix_fn);

  // Call sparseMatrix directly with named arguments
  return sparseMatrix(named_arg("i") = i, named_arg("j") = j, named_arg("x") = x,
                      named_arg("dims") = dims);
}
