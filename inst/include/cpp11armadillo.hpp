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
