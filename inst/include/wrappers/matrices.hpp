#pragma once

using namespace arma;
using namespace cpp11;

#ifndef MATRICES_HPP
#define MATRICES_HPP

////////////////////////////////////////////////////////////////
// R to Armadillo
////////////////////////////////////////////////////////////////

template <typename T>
inline Mat<T> as_Mat(const T& x) {
  // Generic implementation
  throw std::runtime_error("Cannot convert to Mat");
}

template <typename T>
inline Mat<T> as_Mat(const Mat<T>& x) {
  return x;
}

template <typename T, typename U>
inline Mat<T> dblint_matrix_to_Mat_(const U& x) {
  const size_t n = x.nrow();
  const size_t m = x.ncol();

  if (std::is_same<U, doubles_matrix<>>::value) {
    return Mat<T>(reinterpret_cast<T*>(REAL(x.data())), n, m, false, false);
  } else {
    return Mat<T>(reinterpret_cast<T*>(INTEGER(x.data())), n, m, false, false);
  }
}

template <typename T, typename U>
inline Mat<T> dblint_to_Mat_(const U& x) {
  const int n = x.size();

  if (std::is_same<U, doubles>::value) {
    return Mat<T>(reinterpret_cast<T*>(REAL(x.data())), n, 1, false, false);
  } else {
    return Mat<T>(reinterpret_cast<T*>(INTEGER(x.data())), n, 1, false, false);
  }
}

inline Mat<double> as_Mat(const doubles_matrix<>& x) {
  return dblint_matrix_to_Mat_<double, doubles_matrix<>>(x);
}

inline Mat<int> as_Mat(const integers_matrix<>& x) {
  return dblint_matrix_to_Mat_<int, integers_matrix<>>(x);
}

inline Mat<double> as_Mat(const doubles& x) { return dblint_to_Mat_<double, doubles>(x); }

inline Mat<int> as_Mat(const integers& x) { return dblint_to_Mat_<int, integers>(x); }

// Convert integers_matrix<> to umat/imat

template <typename TargetMatType>
inline TargetMatType as_target_mat(const integers_matrix<>& x) {
  const uword n = x.nrow();
  const uword m = x.ncol();
  const uword nm = n * m;

  // Allocate our Armadillo matrix once
  TargetMatType y(n, m);

  // Raw pointers into R's data and Armadillo's storage
  const int* src = INTEGER(x.data());
  typename TargetMatType::elem_type* dst = y.memptr();

// Copy all entries in one flat loop (faster than y(i,j) indexing)
#pragma omp parallel for if (nm > 10000)
  for (uword idx = 0; idx < nm; ++idx) {
    dst[idx] = static_cast<typename TargetMatType::elem_type>(src[idx]);
  }

  return y;
}

inline umat as_umat(const integers_matrix<>& x) { return as_target_mat<umat>(x); }

inline imat as_imat(const integers_matrix<>& x) { return as_target_mat<imat>(x); }

inline fmat as_fmat(const doubles_matrix<>& x) {
  Mat<double> y = dblint_matrix_to_Mat_<double, doubles_matrix<>>(x);
  return arma::conv_to<fmat>::from(y);
}

// cpp11armadillo 0.4.3
// as_mat() = alias for as_Mat()

template <typename T>
inline Mat<T> as_mat(const T& x) {
  return as_Mat(x);
}

template <typename T>
inline Mat<T> as_mat(const Mat<T>& x) {
  return as_Mat(x);
}

inline Mat<double> as_mat(const doubles_matrix<>& x) { return as_Mat(x); }

inline Mat<int> as_mat(const integers_matrix<>& x) { return as_Mat(x); }

inline Mat<double> as_mat(const doubles& x) { return as_Mat(x); }

inline Mat<int> as_mat(const integers& x) { return as_Mat(x); }

////////////////////////////////////////////////////////////////
// Armadillo to R
////////////////////////////////////////////////////////////////

// Double/Integer

template <typename T, typename U>
inline U Mat_to_dblint_matrix_(const Mat<T>& A) {
  const int n = A.n_rows;
  const int m = A.n_cols;

  using dblint_matrix =
      typename std::conditional<std::is_same<U, doubles_matrix<>>::value,
                                writable::doubles_matrix<>,
                                writable::integers_matrix<>>::type;

  dblint_matrix B(n, m);

  if (std::is_same<U, doubles_matrix<>>::value) {
    double* B_data = REAL(B);
    std::memcpy(B_data, A.memptr(), n * m * sizeof(double));
  } else {
    int* B_data = INTEGER(B);
    std::memcpy(B_data, A.memptr(), n * m * sizeof(int));
  }

  return B;
}

inline doubles_matrix<> as_doubles_matrix(const Mat<double>& A) {
  return Mat_to_dblint_matrix_<double, doubles_matrix<>>(A);
}

inline integers_matrix<> as_integers_matrix(const Mat<int>& A) {
  // Fast path: int to int
  return Mat_to_dblint_matrix_<int, integers_matrix<>>(A);
}

inline integers_matrix<> as_integers_matrix(const Mat<long long>& A) {
  // Explicit cast for long long to int
  const int n = A.n_rows;
  const int m = A.n_cols;
  writable::integers_matrix<> B(n, m);
  int* B_data = INTEGER(B);
  const long long* A_data = A.memptr();
  for (int i = 0; i < n * m; ++i) {
    B_data[i] = static_cast<int>(A_data[i]);
  }
  return B;
}

// Convert umat/imat to integers_matrix<>

template <typename T>
inline integers_matrix<> as_integers_matrix_template(const Mat<T>& A) {
  const size_t n = A.n_rows;
  const size_t m = A.n_cols;
  const size_t nm = n * m;

  writable::integers_matrix<> B(n, m);
  int* B_data = INTEGER(B);

  // Convert element by element to handle different types
  //   const T* A_data = A.memptr();

  // #pragma omp parallel for if (nm > 10000)
  //   for (size_t idx = 0; idx < nm; ++idx) {
  //     B_data[idx] = static_cast<int>(A_data[idx]);
  //   }

  std::memcpy(B_data, A.memptr(), nm * sizeof(int));

  return B;
}

inline integers_matrix<> as_integers_matrix(const umat& A) {
  return as_integers_matrix_template(A);
}

// Complex

template <typename T>
inline list Mat_to_complex_matrix_(const Mat<T>& A) {
  Mat<double> A_real = real(A);
  Mat<double> A_imag = imag(A);

  writable::list B;
  B.push_back({"real"_nm = as_doubles_matrix(A_real)});
  B.push_back({"imag"_nm = as_doubles_matrix(A_imag)});

  return B;
}

inline list as_complex_matrix(const Mat<std::complex<double>>& A) {
  return Mat_to_complex_matrix_<std::complex<double>>(A);
}

// Specialized version for sparse matrices

template <typename T>
inline integers_matrix<> as_integers_matrix(const SpMat<T>& A) {
  const uword n = A.n_rows;
  const uword m = A.n_cols;
  const size_t nm = n * m;

  writable::integers_matrix<> B(n, m);
  int* B_data = INTEGER(B);

  // Initialize with zeros
  std::memset(B_data, 0, nm * sizeof(int));

  // Copy non-zero elements
  // for (typename SpMat<T>::const_iterator it = A.begin(); it != A.end(); ++it) {
  //   B(it.row(), it.col()) = static_cast<int>(*it);
  // }

  const auto& col_ptrs = A.col_ptrs;     // length m+1
  const auto& row_inds = A.row_indices;  // length nnz
  const auto& values = A.values;         // length nnz

  uword i, j, start, end, idx;

  for (j = 0; j < m; ++j) {
    start = col_ptrs[j];
    end = col_ptrs[j + 1];
    for (idx = start; idx < end; ++idx) {
      i = row_inds[idx];
      // linear index = row + col * n
      B_data[i + j * n] = static_cast<int>(values[idx]);
    }
  }

  return B;
}

inline integers_matrix<> as_integers_matrix(const SpMat<unsigned long long>& A) {
  return as_integers_matrix<unsigned long long>(A);
}

inline integers_matrix<> as_integers_matrix(const SpMat<long long>& A) {
  return as_integers_matrix<long long>(A);
}

#endif
