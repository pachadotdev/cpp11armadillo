#pragma once

using namespace arma;
using namespace cpp11;

#ifndef VECTORS_HPP
#define VECTORS_HPP

// Note: dblint = doubles or integers

////////////////////////////////////////////////////////////////
// R to Armadillo
////////////////////////////////////////////////////////////////

// vector or doubles/integers to Col<double/int>

template <typename T>
inline Col<T> as_Col(const T& x) {
  // Generic implementation
  throw std::runtime_error("Cannot convert to Col");
}

template <typename T, typename U>
inline Col<T> as_Col_(const U& x) {
  const int n = x.size();

  Col<T> y(n);

  if (std::is_same<U, doubles>::value) {
    y = Col<T>(reinterpret_cast<T*>(REAL(x.data())), n, false);
  } else {
    y = Col<T>(reinterpret_cast<T*>(INTEGER(x.data())), n, false);
  }

  return y;
}

inline Col<double> as_Col(const doubles& x) { return as_Col_<double, doubles>(x); }

inline Col<int> as_Col(const integers& x) { return as_Col_<int, integers>(x); }

inline uvec as_uvec(const cpp11::integers& x) {
  uvec res(x.size());
  // the binary representation of int and uword are not the same
  // reinterpret_cast fails
  std::copy(x.begin(), x.end(), res.begin());
  return res;
}

////////////////////////////////////////////////////////////////
// Armadillo to R
////////////////////////////////////////////////////////////////

// Double/Integer to vector

template <typename T, typename U>
inline U Col_to_dblint_(const Col<T>& x) {
  const int n = x.n_rows;

  using dblint = typename std::conditional<std::is_same<U, doubles>::value,
                                           writable::doubles, writable::integers>::type;

  dblint y(n);

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    y[i] = x[i];
  }

  return y;
}

inline integers as_integers(const Col<int>& x) {
  return Col_to_dblint_<int, integers>(x);
}

inline doubles as_doubles(const Col<double>& x) {
  return Col_to_dblint_<double, doubles>(x);
}

inline integers as_integers(const uvec& x) {
  const int n = x.n_elem;
  writable::integers y(n);

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    y[i] = x[i];
  }

  return y;
}

// same as above, but for matrices

template <typename T, typename U>
inline U Col_to_dblint_matrix_(const Col<T>& x) {
  const int n = x.n_rows;
  const int m = 1;

  using dblint_matrix =
      typename std::conditional<std::is_same<U, doubles_matrix<>>::value,
                                writable::doubles_matrix<>,
                                writable::integers_matrix<>>::type;

  dblint_matrix y(n, m);

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    y(i, 0) = x[i];
  }

  return y;
}

inline doubles_matrix<> as_doubles_matrix(const Col<double>& x) {
  return Col_to_dblint_matrix_<double, doubles_matrix<>>(x);
}

inline integers_matrix<> as_integers_matrix(const Col<int>& x) {
  return Col_to_dblint_matrix_<int, integers_matrix<>>(x);
}

// Complex

inline list as_complex_doubles(const Col<std::complex<double>>& x) {
  Col<double> x_real = real(x);
  Col<double> x_imag = imag(x);

  return writable::list({"real"_nm = as_doubles(x_real), "imag"_nm = as_doubles(x_imag)});
}

inline list as_complex_matrix(const Col<std::complex<double>>& x) {
  Col<double> x_real = real(x);
  Col<double> x_imag = imag(x);

  return writable::list(
      {"real"_nm = as_doubles_matrix(x_real), "imag"_nm = as_doubles_matrix(x_imag)});
}

#endif
