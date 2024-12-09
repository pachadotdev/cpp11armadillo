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

////////////////////////////////////////////////////////////////////////////////

// Glue layer for the RNG to make sure it is sync'd with R's set.seed() for
// reproducibility

class arma_rng_alt {
 public:
  typedef unsigned int seed_type;

  inline static void set_seed(const seed_type val);

  arma_inline static int randi_val();
  arma_inline static double randu_val();
  inline static double randn_val();

  template <typename eT>
  inline static void randn_dual_val(eT& out1, eT& out2);

  template <typename eT>
  inline static void randi_fill(eT* mem, const arma::uword N, const int a, const int b);

  inline static int randi_max_val();
};

inline void arma_rng_alt::set_seed(const arma_rng_alt::seed_type val) {
  (void)val;
  static int n_warnings = 0;
  if (n_warnings++ == 0) {
    cpp11::warning(
        "When called from R, the RNG seed has to be set at the R level via set.seed()");
  }
}

arma_inline int arma_rng_alt::randi_val() {
  return static_cast<int>(::Rf_runif(0, RAND_MAX));
}

arma_inline double arma_rng_alt::randu_val() { return ::Rf_runif(0, 1); }

inline double arma_rng_alt::randn_val() {
  double tmp1;
  double tmp2;
  double w;

  do {
    tmp1 = 2.0 * ::Rf_runif(0, 1) - 1.0;
    tmp2 = 2.0 * ::Rf_runif(0, 1) - 1.0;
    w = tmp1 * tmp1 + tmp2 * tmp2;
  } while (w >= 1.0);

  return tmp1 * std::sqrt((-2.0 * std::log(w)) / w);
}

template <typename eT>
inline void arma_rng_alt::randn_dual_val(eT& out1, eT& out2) {
  typedef typename arma::promote_type<eT, float>::result eTp;

  eTp tmp1;
  eTp tmp2;
  eTp w;

  do {
    tmp1 = 2.0 * ::Rf_runif(0, 1) - 1.0;
    tmp2 = 2.0 * ::Rf_runif(0, 1) - 1.0;
    w = tmp1 * tmp1 + tmp2 * tmp2;
  } while (w >= 1.0);

  const eTp k = std::sqrt((-2.0 * std::log(w)) / w);

  out1 = eT(tmp1 * k);
  out2 = eT(tmp2 * k);
}

template <typename eT>
inline void arma_rng_alt::randi_fill(eT* mem, const arma::uword N, const int a,
                                     const int b) {
  if ((a == 0) && (b == RAND_MAX)) {
    for (arma::uword i = 0; i < N; ++i) {
      mem[i] = static_cast<int>(::Rf_runif(0, RAND_MAX));
    }
  } else {
    const arma::uword length = b - a + 1;
    const double scale = static_cast<double>(length) / RAND_MAX;

    for (arma::uword i = 0; i < N; ++i) {
      mem[i] = std::min(b, static_cast<int>(::Rf_runif(0, RAND_MAX) * scale) + a);
    }
  }
}

inline int arma_rng_alt::randi_max_val() { return RAND_MAX; }

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

    inline static void dual_val(eT& out1, eT& out2) {
      arma_rng_alt::randn_dual_val(out1, out2);
    }

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

  template <typename T>
  struct randu<std::complex<T>> {
    inline operator std::complex<T>() {
      const T a = T(arma_rng_alt::randu_val());
      const T b = T(arma_rng_alt::randu_val());
      return std::complex<T>(a, b);
    }

    inline static void fill(std::complex<T>* mem, const arma::uword N) {
      for (arma::uword i = 0; i < N; ++i) {
        const T a = T(arma_rng_alt::randu_val());
        const T b = T(arma_rng_alt::randu_val());
        mem[i] = std::complex<T>(a, b);
      }
    }

    inline static void fill(std::complex<T>* mem, const arma::uword N, const double a,
                            const double b) {
      const double r = b - a;
      for (arma::uword i = 0; i < N; ++i) {
        const T tmp1 = T(arma_rng_alt::randu_val() * r + a);
        const T tmp2 = T(arma_rng_alt::randu_val() * r + a);
        mem[i] = std::complex<T>(tmp1, tmp2);
      }
    }
  };

  template <typename T>
  struct randn<std::complex<T>> {
    inline operator std::complex<T>() const {
      T a(0);
      T b(0);
      arma_rng_alt::randn_dual_val(a, b);
      return std::complex<T>(a, b);
    }

    inline static void dual_val(std::complex<T>& out1, std::complex<T>& out2) {
      T a(0);
      T b(0);
      arma_rng_alt::randn_dual_val(a, b);
      out1 = std::complex<T>(a, b);
      arma_rng_alt::randn_dual_val(a, b);
      out2 = std::complex<T>(a, b);
    }

    inline static void fill(std::complex<T>* mem, const arma::uword N) {
      for (arma::uword i = 0; i < N; ++i) {
        mem[i] = std::complex<T>(arma_rng_alt::randn_val());
      }
    }

    inline static void fill(std::complex<T>* mem, const uword N, const double mu,
                            const double sd) {
      for (uword i = 0; i < N; ++i) {
        const std::complex<T>& val = mem[i];
        mem[i] = std::complex<T>(((val.real() * sd) + mu), ((val.imag() * sd) + mu));
      }
    }
  };

  template <typename eT>
  struct randg {
    inline static void fill(eT* mem, const uword N, const double a, const double b) {
      for (uword i = 0; i < N; ++i) {
        mem[i] = eT(::Rf_rgamma(a, b));
      }
    }
  };
};
