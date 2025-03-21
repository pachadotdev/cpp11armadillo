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
  const int n = x.nrow();
  const int m = x.ncol();

  Mat<T> y(n, m);

  if (std::is_same<U, doubles_matrix<>>::value) {
    y = Mat<T>(reinterpret_cast<T*>(REAL(x.data())), n, m, false, false);
  } else {
    y = Mat<T>(reinterpret_cast<T*>(INTEGER(x.data())), n, m, false, false);
  }

  return y;
}

template <typename T, typename U>
inline Mat<T> dblint_to_Mat_(const U& x) {
  const int n = x.size();

  Mat<T> y(n, 1);

  if (std::is_same<U, doubles>::value) {
    y = Mat<T>(reinterpret_cast<T*>(REAL(x.data())), n, 1, false, false);
  } else {
    y = Mat<T>(reinterpret_cast<T*>(INTEGER(x.data())), n, 1, false, false);
  }

  return y;
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
  const int n = x.nrow();
  const int m = x.ncol();

  TargetMatType y(n, m);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      y(i, j) = static_cast<typename TargetMatType::elem_type>(x(i, j));
    }
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
  return Mat_to_dblint_matrix_<int, integers_matrix<>>(A);
}

// Convert umat/imat to integers_matrix<>

template <typename SourceMatType>
inline integers_matrix<> as_integers_matrix(const SourceMatType& A) {
  const size_t n = A.n_rows;
  const size_t m = A.n_cols;

  writable::integers_matrix<> B(n, m);
  int* B_data = INTEGER(B);

  std::memcpy(B_data, A.memptr(), n * m * sizeof(int));

  return B;
}

inline integers_matrix<> as_integers_matrix(const umat& A) {
  return as_integers_matrix<umat>(A);
}

inline integers_matrix<> as_integers_matrix(const imat& A) {
  return as_integers_matrix<imat>(A);
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
  const size_t n = A.n_rows;
  const size_t m = A.n_cols;

  writable::integers_matrix<> B(n, m);

  // Initialize with zeros
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      B(i, j) = 0;
    }
  }

  // Copy non-zero elements
  for (typename SpMat<T>::const_iterator it = A.begin(); it != A.end(); ++it) {
    B(it.row(), it.col()) = static_cast<int>(*it);
  }

  return B;
}

inline integers_matrix<> as_integers_matrix(const SpMat<unsigned long long>& A) {
  return as_integers_matrix<unsigned long long>(A);
}

inline integers_matrix<> as_integers_matrix(const SpMat<long long>& A) {
  return as_integers_matrix<long long>(A);
}

////////////////////////////////////////////////////////////////
// as_cpp() specializations for matrices
////////////////////////////////////////////////////////////////

// this is to match the as_cpp() behavior in cpp11

// R to Armadillo

template <typename To, typename From>
inline To as_cpp(const From& x) {
  static_assert(sizeof(To) == 0,
                "No conversion available from the given type to the target type");
  return To();  // Never reached due to static_assert, but needed for compilation
}

// doubles_matrix<> -> Mat<double> / mat / fmat
template <>
inline Mat<double> as_cpp<Mat<double>>(const doubles_matrix<>& x) {
  return as_Mat(x);
}
template <>
inline fmat as_cpp<fmat>(const doubles_matrix<>& x) {
  return as_fmat(x);
}

// integers_matrix<> -> Mat<int> / imat
template <>
inline Mat<int> as_cpp<Mat<int>>(const integers_matrix<>& x) {
  return as_Mat(x);
}
template <>
inline imat as_cpp<imat>(const integers_matrix<>& x) {
  return as_imat(x);
}

// Armadillo to R

// Mat<double> / mat / fmat -> doubles_matrix<>
template <>
inline doubles_matrix<> as_cpp<doubles_matrix<>>(const Mat<double>& x) {
  return as_doubles_matrix(x);
}
template <>
inline doubles_matrix<> as_cpp<doubles_matrix<>>(const fmat& x) {
  mat temp = arma::conv_to<mat>::from(x);
  return as_doubles_matrix(temp);
}

// Mat<int> / imat -> integers_matrix<>
template <>
inline integers_matrix<> as_cpp<integers_matrix<>>(const Mat<int>& x) {
  return as_integers_matrix(x);
}
template <>
inline integers_matrix<> as_cpp<integers_matrix<>>(const imat& x) {
  return as_integers_matrix(x);
}

// umat -> integers_matrix<>
template <>
inline integers_matrix<> as_cpp<integers_matrix<>>(const umat& x) {
  return as_integers_matrix(x);
}

#endif
