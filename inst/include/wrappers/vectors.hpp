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

template <typename T>
inline Col<T> as_Col(const Col<T>& x) {
  return x;
}

template <typename T, typename U>
inline Col<T> as_Col_(const U& x) {
  const size_t n = x.size();

  if (std::is_same<U, doubles>::value) {
    return Col<T>(reinterpret_cast<T*>(REAL(x.data())), n, false);
  } else {
    return Col<T>(reinterpret_cast<T*>(INTEGER(x.data())), n, false);
  }
}

inline Col<double> as_Col(const doubles& x) { return as_Col_<double, doubles>(x); }

inline Col<int> as_Col(const integers& x) { return as_Col_<int, integers>(x); }

inline Col<double> as_Col(const doubles_matrix<>& x) {
  if (x.ncol() != 1) {
    throw std::runtime_error("Cannot convert matrix with multiple columns to Col");
  }

  const size_t n = x.nrow();
  return Col<double>(reinterpret_cast<double*>(REAL(x.data())), n, false);
}

inline Col<int> as_Col(const integers_matrix<>& x) {
  // Only convert if it's a column vector (1 column)
  if (x.ncol() != 1) {
    throw std::runtime_error("Cannot convert matrix with multiple columns to Col");
  }

  const size_t n = x.nrow();
  return Col<int>(reinterpret_cast<int*>(INTEGER(x.data())), n, false);
}

inline Col<double> as_col(const doubles_matrix<>& x) { return as_Col(x); }
inline Col<int> as_col(const integers_matrix<>& x) { return as_Col(x); }

// cpp11armadillo 0.4.3
// as_vec() = alias for as_Col()

template <typename T>
inline Col<T> as_col(const T& x) {
  return as_Col(x);
}

template <typename T>
inline Col<T> as_col(const Col<T>& x) {
  return as_Col(x);
}

inline Col<double> as_col(const doubles& x) { return as_Col(x); }

inline Col<int> as_col(const integers& x) { return as_Col(x); }

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
  const size_t n = x.n_rows;

  using dblint = typename std::conditional<std::is_same<U, doubles>::value,
                                           writable::doubles, writable::integers>::type;

  dblint y(n);

  if (std::is_same<U, doubles>::value) {
    double* y_data = REAL(y);
    std::memcpy(y_data, x.memptr(), n * sizeof(double));
  } else {
    int* y_data = INTEGER(y);
    std::memcpy(y_data, x.memptr(), n * sizeof(int));
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
  const size_t n = x.n_elem;

  writable::integers y(n);

  std::copy(x.begin(), x.end(), y.begin());

  return y;
}

// On 64-bit word systems, ivec is Col<long>
#if defined(ARMA_64BIT_WORD)
inline integers as_integers(const Col<long>& x) {
  return Col_to_dblint_<long, integers>(x);
}
#endif

inline integers as_integers(const uword& x) {
  writable::integers y(1);

  y[0] = static_cast<int>(x);

  return y;
}

// same as above, but for matrices

template <typename T, typename U>
inline U Col_to_dblint_matrix_(const Col<T>& x) {
  const size_t n = x.n_rows;
  const size_t m = 1;

  using dblint_matrix =
      typename std::conditional<std::is_same<U, doubles_matrix<>>::value,
                                writable::doubles_matrix<>,
                                writable::integers_matrix<>>::type;

  using dblint =
      typename std::conditional<std::is_same<U, cpp11::writable::doubles_matrix<>>::value,
                                double, int>::type;

  dblint_matrix y(n, m);

  std::memcpy(y.data(), x.memptr(), n * m * sizeof(dblint));

  return y;
}

inline doubles_matrix<> as_doubles_matrix(const Col<double>& x) {
  return Col_to_dblint_matrix_<double, doubles_matrix<>>(x);
}

inline integers_matrix<> as_integers_matrix(const Col<int>& x) {
  return Col_to_dblint_matrix_<int, integers_matrix<>>(x);
}

// Specialization for fmat
inline doubles_matrix<> as_doubles_matrix(const fmat& x) {
  Mat<double> temp = conv_to<Mat<double>>::from(x);
  return Mat_to_dblint_matrix_<double, doubles_matrix<>>(temp);
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
