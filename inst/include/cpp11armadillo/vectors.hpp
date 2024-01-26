#pragma once

using namespace arma;
using namespace cpp11;
using namespace std;

// Note: dblint = doubles or integers

////////////////////////////////////////////////////////////////
// R to Armadillo
////////////////////////////////////////////////////////////////

template <typename T>
Col<T> as_Vec(const T& x) {
  // Generic implementation
  throw runtime_error("Cannot convert to Vec");
}

template <typename T, typename U>
Col<T> dblint_to_Vec_(const U& x) {
  int n = x.size();
  Col<T> y(
      (is_same<U, doubles>::value ? reinterpret_cast<T*>(REAL(x.data()))
                                  : reinterpret_cast<T*>(INTEGER(x.data()))),
      n, false);
  return y;
}

Col<double> dblint_to_Vec(const doubles& x) {
  return dblint_to_Vec_<double, doubles>(x);
}

Col<int> dblint_to_Vec(const integers& x) {
  return dblint_to_Vec_<int, integers>(x);
}

////////////////////////////////////////////////////////////////
// Armadillo to R
////////////////////////////////////////////////////////////////

template <typename T, typename U>
U Vec_to_dblint_(const Col<T>& x) {
  int n = x.n_rows;

  typename conditional<is_same<U, doubles>::value, writable::doubles,
                       writable::integers>::type y(n);

  for (int i = 0; i < n; ++i) {
    typename conditional<is_same<U, doubles>::value, double, int>::type x_i =
        x[i];
    y[i] = x_i;
  }

  return y;
}

doubles as_doubles(const Col<double>& x) {
  return Vec_to_dblint_<double, doubles>(x);
}

integers as_integers(const Col<int>& x) {
  return Vec_to_dblint_<int, integers>(x);
}

template <typename T, typename U>
U Vec_to_dblint_matrix_(const Col<T>& x) {
  int n = x.n_rows;
  int m = 1;

  typename conditional<is_same<U, writable::doubles_matrix<>>::value,
                       writable::doubles_matrix<>,
                       writable::integers_matrix<>>::type Y(n, m);

  for (int i = 0; i < n; ++i) {
    typename conditional<is_same<U, doubles_matrix<>>::value, double, int>::type
        x_i = x[i];
    Y(i, 0) = x_i;
  }

  return Y;
}

doubles_matrix<> as_doubles_matrix(const Col<double>& x) {
  return Vec_to_dblint_matrix_<double, doubles_matrix<>>(x);
}

integers_matrix<> as_integers_matrix(const Col<int>& x) {
  return Vec_to_dblint_matrix_<int, integers_matrix<>>(x);
}
