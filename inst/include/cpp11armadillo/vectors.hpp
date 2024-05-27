#pragma once

using namespace arma;
using namespace cpp11;
using namespace std;

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
  throw runtime_error("Cannot convert to Col");
}

template <typename T, typename U>
inline Col<T> as_Col_(const U& x) {
  const int n = x.size();
  Col<T> y((is_same<U, doubles>::value ? reinterpret_cast<T*>(REAL(x.data()))
                                       : reinterpret_cast<T*>(INTEGER(x.data()))),
           n, false);
  return y;
}

inline Col<double> as_Col(const doubles& x) { return as_Col_<double, doubles>(x); }

inline Col<int> as_Col(const integers& x) { return as_Col_<int, integers>(x); }

////////////////////////////////////////////////////////////////
// Armadillo to R
////////////////////////////////////////////////////////////////

// Double/Integer

template <typename T, typename U>
inline U Col_to_dblint_(const Col<T>& x) {
  const int n = x.n_rows;

  using dblint_vector = typename conditional<is_same<U, doubles>::value,
                                             writable::doubles, writable::integers>::type;

  dblint_vector y(n);

  using dblint_element =
      typename conditional<is_same<U, doubles>::value, double, int>::type;

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    y[i] = static_cast<dblint_element>(x[i]);
  }

  return y;
}

inline doubles as_doubles(const Col<double>& x) {
  return Col_to_dblint_<double, doubles>(x);
}

inline integers as_integers(const Col<int>& x) {
  return Col_to_dblint_<int, integers>(x);
}

template <typename T, typename U>
inline U Col_to_dblint_matrix_(const Col<T>& x) {
  const int n = x.n_rows;
  const int m = 1;

  using dblint_matrix =
      typename conditional<is_same<U, writable::doubles_matrix<>>::value,
                           writable::doubles_matrix<>, writable::integers_matrix<>>::type;

  using dblint_element =
      typename conditional<is_same<U, doubles_matrix<>>::value, double, int>::type;

  dblint_matrix Y(n, m);

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    Y(i, 0) = static_cast<dblint_element>(x[i]);
  }

  return Y;
}

inline doubles_matrix<> as_doubles_matrix(const Col<double>& x) {
  return Col_to_dblint_matrix_<double, doubles_matrix<>>(x);
}

inline integers_matrix<> as_integers_matrix(const Col<int>& x) {
  return Col_to_dblint_matrix_<int, integers_matrix<>>(x);
}

// Complex

template <typename T>
inline list Col_to_complex_dbl_(const Col<T>& x) {
  static_assert(is_same<T, complex<double>>::value, "T must be complex<double>");
  Col<double> x_real = real(x);
  Col<double> x_imag = imag(x);

  writable::list y;
  y.push_back({"real"_nm = as_doubles(x_real)});
  y.push_back({"imag"_nm = as_doubles(x_imag)});

  return y;
}

inline list as_complex_doubles(const Col<complex<double>>& x) {
  return Col_to_complex_dbl_<complex<double>>(x);
}

template <typename T>
inline list Col_to_complex_matrix_(const Col<T>& x) {
  static_assert(is_same<T, complex<double>>::value, "T must be complex<double>");
  Col<double> x_real = real(x);
  Col<double> x_imag = imag(x);

  // TODO: This is a workaround to avoid an error when the imaginary part is zero
  int n = x.n_rows;
  int m = 1;
  writable::doubles_matrix<> x_real2(n, m);
  writable::doubles_matrix<> x_imag2(n, m);

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    x_real2(i, 0) = x_real[i];
    x_imag2(i, 0) = x_imag[i];
  }

  return writable::list({"real"_nm = x_real2, "imag"_nm = x_imag2});
}

inline list as_complex_matrix(const Col<complex<double>>& x) {
  return Col_to_complex_matrix_<complex<double>>(x);
}

#endif
