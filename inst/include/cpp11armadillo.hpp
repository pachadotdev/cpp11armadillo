#pragma once

#ifdef _OPENMP
#include <omp.h>
#endif

#include <R.h>
#include <R_ext/Random.h>
#include <Rmath.h>
#include <armadillo.hpp>
#include <cpp11.hpp>
#include <wrappers/matrices.hpp>
#include <wrappers/sparse_matrices.hpp>
#include <wrappers/vectors.hpp>

using mat = arma::mat;
using fmat = arma::fmat;
using imat = arma::imat;
using umat = arma::umat;
using vec = arma::vec;
using ivec = arma::ivec;
using uvec = arma::uvec;
using fvec = arma::fvec;
using rowvec = arma::rowvec;
using irowvec = arma::irowvec;
using urowvec = arma::urowvec;
using frowvec = arma::frowvec;
using cube = arma::cube;
using icube = arma::icube;
using ucube = arma::ucube;
using fcube = arma::fcube;
using cx_mat = arma::cx_mat;
using cx_vec = arma::cx_vec;
using cx_rowvec = arma::cx_rowvec;
using cx_cube = arma::cx_cube;

////////////////////////////////////////////////////////////////////////////////

// Custom RNG class to ensure synchronization with R's RNG state

class arma_rng_alt {
 public:
  typedef unsigned int seed_type;

  inline static void set_seed(const seed_type val) {
    (void)val;  // No-op, cannot set seed in R from C++ code
  }

  arma_inline static int randi_val() { return static_cast<int>(::Rf_runif(0, RAND_MAX)); }

  arma_inline static double randu_val() { return ::Rf_runif(0, 1); }

  inline static double randn_val() {
    double u1, u2, s;
    do {
      u1 = 2.0 * ::Rf_runif(0, 1) - 1.0;
      u2 = 2.0 * ::Rf_runif(0, 1) - 1.0;
      s = u1 * u1 + u2 * u2;
    } while (s >= 1.0);
    return u1 * std::sqrt((-2.0 * std::log(s)) / s);
  }

  template <typename eT>
  inline static void randi_fill(eT* mem, const arma::uword N, const int a, const int b) {
    const arma::uword length = b - a + 1;
    const double scale = static_cast<double>(length) / RAND_MAX;
    for (arma::uword i = 0; i < N; ++i) {
      mem[i] = std::min(b, static_cast<int>(::Rf_runif(0, RAND_MAX) * scale) + a);
    }
  }

  inline static int randi_max_val() { return RAND_MAX; }
};

////////////////////////////////////////////////////////////////////////////////

// Main RNG class that uses arma_rng_alt for RNG operations

class arma_rng {
 public:
  typedef arma_rng_alt::seed_type seed_type;

  static constexpr int rng_method = 2;

  inline static void set_seed(const seed_type val) { arma_rng_alt::set_seed(val); }

  inline static void set_seed_random() {
    cpp11::stop(
        "When called from R, the RNG seed has to be set at the R level via set.seed()");
  }

  template <typename eT>
  struct randi {
    inline operator eT() { return eT(arma_rng_alt::randi_val()); }

    inline static int max_val() { return arma_rng_alt::randi_max_val(); }

    inline static void fill(eT* mem, const arma::uword N, const int a, const int b) {
      arma_rng_alt::randi_fill(mem, N, a, b);
    }
  };

  template <typename eT>
  struct randu {
    inline operator eT() { return eT(arma_rng_alt::randu_val()); }

    inline static void fill(eT* mem, const arma::uword N) {
      for (arma::uword i = 0; i < N; ++i) {
        mem[i] = eT(arma_rng_alt::randu_val());
      }
    }

    inline static void fill(eT* mem, const arma::uword N, const double a,
                            const double b) {
      const double r = b - a;
      for (arma::uword i = 0; i < N; ++i) {
        mem[i] = eT(arma_rng_alt::randu_val() * r + a);
      }
    }
  };

  template <typename eT>
  struct randn {
    inline operator eT() const { return eT(arma_rng_alt::randn_val()); }

    inline static void fill(eT* mem, const arma::uword N) {
      for (arma::uword i = 0; i < N; ++i) {
        mem[i] = eT(arma_rng_alt::randn_val());
      }
    }

    inline static void fill(eT* mem, const arma::uword N, const double mu,
                            const double sd) {
      for (arma::uword i = 0; i < N; ++i) {
        const eT val = eT(arma_rng_alt::randn_val());
        mem[i] = (val * sd) + mu;
      }
    }
  };
};

////////////////////////////////////////////////////////////////////////////////

namespace cpp11 {

// Specializations for as_cpp - converting from R objects to Armadillo types

template <>
inline arma::mat as_cpp<arma::mat>(SEXP x) {
  // Handle both integer and double matrices
  if (TYPEOF(x) == INTSXP) {
    cpp11::integers_matrix<> temp = cpp11::as_cpp<cpp11::integers_matrix<>>(x);
    arma::Mat<int> imat = ::as_Mat(temp);
    return arma::conv_to<arma::mat>::from(imat);
  } else {
    return ::as_Mat(cpp11::as_cpp<cpp11::doubles_matrix<>>(x));
  }
}

template <>
inline arma::fmat as_cpp<arma::fmat>(SEXP x) {
  // Handle both integer and double matrices
  if (TYPEOF(x) == INTSXP) {
    cpp11::integers_matrix<> temp = cpp11::as_cpp<cpp11::integers_matrix<>>(x);
    arma::Mat<int> imat = ::as_Mat(temp);
    return arma::conv_to<arma::fmat>::from(imat);
  } else {
    return ::as_fmat(cpp11::as_cpp<cpp11::doubles_matrix<>>(x));
  }
}

template <>
inline arma::imat as_cpp<arma::imat>(SEXP x) {
  // Handle both integer and double matrices  
  if (TYPEOF(x) == REALSXP) {
    cpp11::doubles_matrix<> temp = cpp11::as_cpp<cpp11::doubles_matrix<>>(x);
    arma::mat dmat = ::as_Mat(temp);
    return arma::conv_to<arma::imat>::from(dmat);
  } else {
    return ::as_imat(cpp11::as_cpp<cpp11::integers_matrix<>>(x));
  }
}

template <>
inline arma::umat as_cpp<arma::umat>(SEXP x) {
  // Handle both integer and double matrices
  if (TYPEOF(x) == REALSXP) {
    cpp11::doubles_matrix<> temp = cpp11::as_cpp<cpp11::doubles_matrix<>>(x);
    arma::mat dmat = ::as_Mat(temp);
    return arma::conv_to<arma::umat>::from(dmat);
  } else {
    return ::as_umat(cpp11::as_cpp<cpp11::integers_matrix<>>(x));
  }
}

template <>
inline arma::vec as_cpp<arma::vec>(SEXP x) {
  // Handle both integer and double vectors
  if (TYPEOF(x) == INTSXP) {
    cpp11::integers temp = cpp11::as_cpp<cpp11::integers>(x);
    arma::Col<int> icol = ::as_Col(temp);
    return arma::conv_to<arma::vec>::from(icol);
  } else {
    return ::as_Col(cpp11::as_cpp<cpp11::doubles>(x));
  }
}

template <>
inline arma::ivec as_cpp<arma::ivec>(SEXP x) {
  // Handle both integer and double vectors
  if (TYPEOF(x) == REALSXP) {
    cpp11::doubles temp = cpp11::as_cpp<cpp11::doubles>(x);
    arma::vec dvec = ::as_Col(temp);
    return arma::conv_to<arma::ivec>::from(dvec);
  } else {
    cpp11::integers temp = cpp11::as_cpp<cpp11::integers>(x);
    arma::Col<int> temp_col = ::as_Col(temp);
    return arma::conv_to<arma::ivec>::from(temp_col);
  }
}

template <>
inline arma::uvec as_cpp<arma::uvec>(SEXP x) {
  // Handle both integer and double vectors
  if (TYPEOF(x) == REALSXP) {
    cpp11::doubles temp = cpp11::as_cpp<cpp11::doubles>(x);
    arma::vec dvec = ::as_Col(temp);
    return arma::conv_to<arma::uvec>::from(dvec);
  } else {
    arma::ivec temp = as_cpp<arma::ivec>(x);
    return arma::conv_to<arma::uvec>::from(temp);
  }
}

template <>
inline arma::fvec as_cpp<arma::fvec>(SEXP x) {
  // Handle both integer and double vectors
  if (TYPEOF(x) == INTSXP) {
    cpp11::integers temp = cpp11::as_cpp<cpp11::integers>(x);
    arma::Col<int> icol = ::as_Col(temp);
    return arma::conv_to<arma::fvec>::from(icol);
  } else {
    arma::vec temp = as_cpp<arma::vec>(x);
    return arma::conv_to<arma::fvec>::from(temp);
  }
}

template <>
inline arma::rowvec as_cpp<arma::rowvec>(SEXP x) {
  arma::vec temp = as_cpp<arma::vec>(x);
  return temp.t();
}

template <>
inline arma::irowvec as_cpp<arma::irowvec>(SEXP x) {
  arma::ivec temp = as_cpp<arma::ivec>(x);
  return temp.t();
}

template <>
inline arma::urowvec as_cpp<arma::urowvec>(SEXP x) {
  arma::uvec temp = as_cpp<arma::uvec>(x);
  return temp.t();
}

template <>
inline arma::frowvec as_cpp<arma::frowvec>(SEXP x) {
  arma::fvec temp = as_cpp<arma::fvec>(x);
  return temp.t();
}

// Specializations for as_sexp - converting from Armadillo types to R objects

template <>
inline SEXP as_sexp(const arma::mat& x) {
  return ::as_doubles_matrix(x);
}

template <>
inline SEXP as_sexp(const arma::fmat& x) {
  arma::mat temp = arma::conv_to<arma::mat>::from(x);
  return ::as_doubles_matrix(temp);
}

template <>
inline SEXP as_sexp(const arma::imat& x) {
  return ::as_integers_matrix(x);
}

template <>
inline SEXP as_sexp(const arma::umat& x) {
  arma::Mat<int> temp = arma::conv_to<arma::Mat<int>>::from(x);
  return ::as_integers_matrix(temp);
}

template <>
inline SEXP as_sexp(const arma::vec& x) {
  return ::as_doubles_matrix(x);
}

template <>
inline SEXP as_sexp(const arma::ivec& x) {
  return ::as_integers_matrix(x);
}

template <>
inline SEXP as_sexp(const arma::uvec& x) {
  arma::Col<int> temp = arma::conv_to<arma::Col<int>>::from(x);
  return ::as_integers_matrix(temp);
}

template <>
inline SEXP as_sexp(const arma::fvec& x) {
  arma::vec temp = arma::conv_to<arma::vec>::from(x);
  return ::as_doubles_matrix(temp);
}

template <>
inline SEXP as_sexp(const arma::rowvec& x) {
  return ::as_doubles_matrix(x);
}

template <>
inline SEXP as_sexp(const arma::irowvec& x) {
  return ::as_integers_matrix(x);
}

template <>
inline SEXP as_sexp(const arma::urowvec& x) {
  arma::Row<int> temp = arma::conv_to<arma::Row<int>>::from(x);
  return ::as_integers_matrix(temp);
}

template <>
inline SEXP as_sexp(const arma::frowvec& x) {
  arma::rowvec temp = arma::conv_to<arma::rowvec>::from(x);
  return ::as_doubles_matrix(temp);
}

} // namespace cpp11
