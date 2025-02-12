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

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      B(i, j) = static_cast<int>(A(i, j));
    }
  }

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

#endif
