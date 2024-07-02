#pragma once

using namespace arma;
using namespace cpp11;

#ifndef SPARSEMATRICES
#define SPARSEMATRICES

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
  const int n = x.nrow();
  const int m = x.ncol();

  SpMat<T> y(n, m);

#ifdef _OPENMP
#pragma omp parallel for collapse(2) schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      y(i, j) = x(i, j);
    }
  }

  return y;
}

template <typename T, typename U>
inline SpMat<T> dblint_to_SpMat_(const U& x) {
  const int n = x.size();

  SpMat<T> y(n, 1);

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
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

////////////////////////////////////////////////////////////////
// Armadillo to R
////////////////////////////////////////////////////////////////

// Double/Integer

template <typename T, typename U>
inline U SpMat_to_dblint_matrix_(const SpMat<T>& A) {
  const int n = A.n_rows;
  const int m = A.n_cols;

  using dblint_matrix =
      typename std::conditional<std::is_same<U, doubles_matrix<>>::value,
                           writable::doubles_matrix<>, writable::integers_matrix<>>::type;

  dblint_matrix B(n, m);

#ifdef _OPENMP
#pragma omp parallel for collapse(2) schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      B(i, j) = A(i, j);
    }
  }

  return B;
}

inline doubles_matrix<> as_doubles_matrix(const SpMat<double>& A) {
  return SpMat_to_dblint_matrix_<double, doubles_matrix<>>(A);
}

inline integers_matrix<> as_integers_matrix(const SpMat<int>& A) {
  return SpMat_to_dblint_matrix_<int, integers_matrix<>>(A);
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
