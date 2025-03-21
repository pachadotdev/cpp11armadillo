// SPDX-License-Identifier: Apache-2.0
//
// Copyright 2008-2016 Conrad Sanderson (http://conradsanderson.id.au)
// Copyright 2008-2016 National ICT Australia (NICTA)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ------------------------------------------------------------------------

//! \addtogroup op_logmat
//! @{

// Partly based on algorithm 11.9 (inverse scaling and squaring algorithm with Schur
// decomposition) in: Nicholas J. Higham. Functions of Matrices: Theory and Computation.
// SIAM, 2008.
// ISBN 978-0-89871-646-7

template <typename T1>
inline void op_logmat::apply(
    Mat<std::complex<typename T1::elem_type> >& out,
    const mtOp<std::complex<typename T1::elem_type>, T1, op_logmat>& in) {
  arma_debug_sigprint();

  const bool status = op_logmat::apply_direct(out, in.m, in.aux_uword_a);

  if (status == false) {
    out.soft_reset();
    arma_stop_runtime_error("logmat(): transformation failed");
  }
}

template <typename T1>
inline bool op_logmat::apply_direct(Mat<std::complex<typename T1::elem_type> >& out,
                                    const Op<T1, op_diagmat>& expr, const uword) {
  arma_debug_sigprint();

  typedef typename T1::elem_type T;

  const diagmat_proxy<T1> P(expr.m);

  arma_conform_check((P.n_rows != P.n_cols),
                     "logmat(): given matrix must be square sized");

  const uword N = P.n_rows;

  out.zeros(N, N);  // aliasing can't happen as op_logmat is defined as cx_mat = op(mat)

  for (uword i = 0; i < N; ++i) {
    const T val = P[i];

    if (val >= T(0)) {
      out.at(i, i) = std::log(val);
    } else {
      out.at(i, i) = std::log(std::complex<T>(val));
    }
  }

  return true;
}

template <typename T1>
inline bool op_logmat::apply_direct(Mat<std::complex<typename T1::elem_type> >& out,
                                    const Base<typename T1::elem_type, T1>& expr,
                                    const uword n_iters) {
  arma_debug_sigprint();

  typedef typename T1::elem_type in_T;
  typedef typename std::complex<in_T> out_T;

  const quasi_unwrap<T1> expr_unwrap(expr.get_ref());
  const Mat<in_T>& A = expr_unwrap.M;

  arma_conform_check((A.is_square() == false),
                     "logmat(): given matrix must be square sized");

  if (A.n_elem == 0) {
    out.reset();
    return true;
  } else if (A.n_elem == 1) {
    out.set_size(1, 1);
    out[0] = std::log(std::complex<in_T>(A[0]));
    return true;
  }

  if (A.is_diagmat()) {
    arma_debug_print("op_logmat: diag optimisation");

    const uword N = A.n_rows;

    out.zeros(N, N);  // aliasing can't happen as op_logmat is defined as cx_mat = op(mat)

    for (uword i = 0; i < N; ++i) {
      const in_T val = A.at(i, i);

      if (val >= in_T(0)) {
        out.at(i, i) = std::log(val);
      } else {
        out.at(i, i) = std::log(out_T(val));
      }
    }

    return true;
  }

  const bool try_sympd = arma_config::optimise_sym && sym_helper::guess_sympd(A);

  if (try_sympd) {
    arma_debug_print("op_logmat: attempting sympd optimisation");

    // if matrix A is sympd, all its eigenvalues are positive

    Col<in_T> eigval;
    Mat<in_T> eigvec;

    const bool eig_status = eig_sym_helper(eigval, eigvec, A, 'd', "logmat()");

    if (eig_status) {
      // ensure each eigenvalue is > 0

      const uword N = eigval.n_elem;
      const in_T* eigval_mem = eigval.memptr();

      bool all_pos = true;

      for (uword i = 0; i < N; ++i) {
        all_pos = (eigval_mem[i] <= in_T(0)) ? false : all_pos;
      }

      if (all_pos) {
        eigval = log(eigval);

        out = conv_to<Mat<out_T> >::from(eigvec * diagmat(eigval) * eigvec.t());

        return true;
      }
    }

    arma_debug_print("op_logmat: sympd optimisation failed");

    // fallthrough if eigen decomposition failed or an eigenvalue is <= 0
  }

  Mat<out_T> S(A.n_rows, A.n_cols, arma_nozeros_indicator());

  const in_T* Amem = A.memptr();
  out_T* Smem = S.memptr();

  const uword n_elem = A.n_elem;

  for (uword i = 0; i < n_elem; ++i) {
    Smem[i] = std::complex<in_T>(Amem[i]);
  }

  return op_logmat_cx::apply_common(out, S, n_iters);
}

template <typename T1>
inline void op_logmat_cx::apply(Mat<typename T1::elem_type>& out,
                                const Op<T1, op_logmat_cx>& in) {
  arma_debug_sigprint();

  const bool status = op_logmat_cx::apply_direct(out, in.m, in.aux_uword_a);

  if (status == false) {
    out.soft_reset();
    arma_stop_runtime_error("logmat(): transformation failed");
  }
}

template <typename T1>
inline bool op_logmat_cx::apply_direct(Mat<typename T1::elem_type>& out,
                                       const Op<T1, op_diagmat>& expr, const uword) {
  arma_debug_sigprint();

  typedef typename T1::elem_type eT;

  const diagmat_proxy<T1> P(expr.m);

  bool status = false;

  if (P.is_alias(out)) {
    Mat<eT> tmp;

    status = op_logmat_cx::apply_direct_noalias(tmp, P);

    out.steal_mem(tmp);
  } else {
    status = op_logmat_cx::apply_direct_noalias(out, P);
  }

  return status;
}

template <typename T1>
inline bool op_logmat_cx::apply_direct_noalias(Mat<typename T1::elem_type>& out,
                                               const diagmat_proxy<T1>& P) {
  arma_debug_sigprint();

  arma_conform_check((P.n_rows != P.n_cols),
                     "logmat(): given matrix must be square sized");

  const uword N = P.n_rows;

  out.zeros(N, N);

  for (uword i = 0; i < N; ++i) {
    out.at(i, i) = std::log(P[i]);
  }

  return true;
}

template <typename T1>
inline bool op_logmat_cx::apply_direct(Mat<typename T1::elem_type>& out,
                                       const Base<typename T1::elem_type, T1>& expr,
                                       const uword n_iters) {
  arma_debug_sigprint();

  typedef typename T1::pod_type T;
  typedef typename T1::elem_type eT;

  Mat<eT> S = expr.get_ref();

  arma_conform_check((S.n_rows != S.n_cols),
                     "logmat(): given matrix must be square sized");

  if (S.n_elem == 0) {
    out.reset();
    return true;
  } else if (S.n_elem == 1) {
    out.set_size(1, 1);
    out[0] = std::log(S[0]);
    return true;
  }

  if (S.is_diagmat()) {
    arma_debug_print("op_logmat_cx: diag optimisation");

    const uword N = S.n_rows;

    out.zeros(N, N);  // aliasing can't happen as S is generated

    for (uword i = 0; i < N; ++i) {
      out.at(i, i) = std::log(S.at(i, i));
    }

    return true;
  }

  const bool try_sympd = arma_config::optimise_sym && sym_helper::guess_sympd(S);

  if (try_sympd) {
    arma_debug_print("op_logmat_cx: attempting sympd optimisation");

    // if matrix S is sympd, all its eigenvalues are positive

    Col<T> eigval;
    Mat<eT> eigvec;

    const bool eig_status = eig_sym_helper(eigval, eigvec, S, 'd', "logmat()");

    if (eig_status) {
      // ensure each eigenvalue is > 0

      const uword N = eigval.n_elem;
      const T* eigval_mem = eigval.memptr();

      bool all_pos = true;

      for (uword i = 0; i < N; ++i) {
        all_pos = (eigval_mem[i] <= T(0)) ? false : all_pos;
      }

      if (all_pos) {
        eigval = log(eigval);

        out = eigvec * diagmat(eigval) * eigvec.t();

        return true;
      }
    }

    arma_debug_print("op_logmat_cx: sympd optimisation failed");

    // fallthrough if eigen decomposition failed or an eigenvalue is <= 0
  }

  return op_logmat_cx::apply_common(out, S, n_iters);
}

template <typename T>
inline bool op_logmat_cx::apply_common(Mat<std::complex<T> >& out,
                                       Mat<std::complex<T> >& S, const uword n_iters) {
  arma_debug_sigprint();

  typedef typename std::complex<T> eT;

  Mat<eT> U;

  const bool schur_ok = auxlib::schur(U, S);

  if (schur_ok == false) {
    arma_debug_print("logmat(): schur decomposition failed");
    return false;
  }

  // NOTE: theta[0] and theta[1] not really used
  double theta[] = {1.10e-5,
                    1.82e-3,
                    1.6206284795015624e-2,
                    5.3873532631381171e-2,
                    1.1352802267628681e-1,
                    1.8662860613541288e-1,
                    2.642960831111435e-1};

  const uword N = S.n_rows;

  uword p = 0;
  uword m = 6;

  uword iter = 0;

  while (iter < n_iters) {
    const T tau = norm((S - eye<Mat<eT> >(N, N)), 1);

    if (tau <= theta[6]) {
      p++;

      uword j1 = 0;
      uword j2 = 0;

      for (uword i = 2; i <= 6; ++i) {
        if (tau <= theta[i]) {
          j1 = i;
          break;
        }
      }
      for (uword i = 2; i <= 6; ++i) {
        if ((tau / 2.0) <= theta[i]) {
          j2 = i;
          break;
        }
      }

      // sanity check, for development purposes only
      arma_conform_check((j2 > j1), "internal error: op_logmat::apply_direct(): j2 > j1");

      if (((j1 - j2) <= 1) || (p == 2)) {
        m = j1;
        break;
      }
    }

    const bool sqrtmat_ok = op_sqrtmat_cx::apply_direct(S, S);

    if (sqrtmat_ok == false) {
      arma_debug_print("logmat(): sqrtmat() failed");
      return false;
    }

    iter++;
  }

  if (iter >= n_iters) {
    arma_warn(2, "logmat(): reached max iterations without full convergence");
  }

  S.diag() -= eT(1);

  if (m >= 1) {
    const bool helper_ok = op_logmat_cx::helper(S, m);

    if (helper_ok == false) {
      return false;
    }
  }

  out = U * S * U.t();

  out *= eT(eop_aux::pow(double(2), double(iter)));

  return true;
}

template <typename eT>
inline bool op_logmat_cx::helper(Mat<eT>& A, const uword m) {
  arma_debug_sigprint();

  if (A.internal_has_nonfinite()) {
    return false;
  }

  const vec indices = regspace<vec>(1, m - 1);

  mat tmp(m, m, arma_zeros_indicator());

  tmp.diag(-1) = indices / sqrt(square(2.0 * indices) - 1.0);
  tmp.diag(+1) = indices / sqrt(square(2.0 * indices) - 1.0);

  vec eigval;
  mat eigvec;

  const bool eig_ok = eig_sym_helper(eigval, eigvec, tmp, 'd', "logmat()");

  if (eig_ok == false) {
    arma_debug_print("logmat(): eig_sym() failed");
    return false;
  }

  const vec nodes = (eigval + 1.0) / 2.0;
  const vec weights = square(eigvec.row(0).t());

  const uword N = A.n_rows;

  Mat<eT> B(N, N, arma_zeros_indicator());

  Mat<eT> X;

  for (uword i = 0; i < m; ++i) {
    // B += weights(i) * solve( (nodes(i)*A + eye< Mat<eT> >(N,N)), A );

    // const bool solve_ok = solve( X, (nodes(i)*A + eye< Mat<eT> >(N,N)), A,
    // solve_opts::fast );
    const bool solve_ok =
        solve(X, trimatu(nodes(i) * A + eye<Mat<eT> >(N, N)), A, solve_opts::no_approx);

    if (solve_ok == false) {
      arma_debug_print("logmat(): solve() failed");
      return false;
    }

    B += weights(i) * X;
  }

  A = B;

  return true;
}

template <typename T1>
inline void op_logmat_sympd::apply(Mat<typename T1::elem_type>& out,
                                   const Op<T1, op_logmat_sympd>& in) {
  arma_debug_sigprint();

  const bool status = op_logmat_sympd::apply_direct(out, in.m);

  if (status == false) {
    out.soft_reset();
    arma_stop_runtime_error("logmat_sympd(): transformation failed");
  }
}

template <typename T1>
inline bool op_logmat_sympd::apply_direct(Mat<typename T1::elem_type>& out,
                                          const Base<typename T1::elem_type, T1>& expr) {
  arma_debug_sigprint();

#if defined(ARMA_USE_LAPACK)
  {
    typedef typename T1::pod_type T;
    typedef typename T1::elem_type eT;

    const unwrap<T1> U(expr.get_ref());
    const Mat<eT>& X = U.M;

    arma_conform_check((X.is_square() == false),
                       "logmat_sympd(): given matrix must be square sized");

    if ((arma_config::check_conform) && (arma_config::warn_level > 0) &&
        (is_cx<eT>::yes) && (sym_helper::check_diag_imag(X) == false)) {
      arma_warn(1, "logmat_sympd(): imaginary components on diagonal are non-zero");
    }

    if (is_op_diagmat<T1>::value || X.is_diagmat()) {
      arma_debug_print("op_logmat_sympd: diag optimisation");

      out = X;

      eT* colmem = out.memptr();

      const uword N = X.n_rows;

      for (uword i = 0; i < N; ++i) {
        eT& out_ii = colmem[i];
        T out_ii_real = access::tmp_real(out_ii);

        if (out_ii_real <= T(0)) {
          return false;
        }

        out_ii = std::log(out_ii);

        colmem += N;
      }

      return true;
    }

    Col<T> eigval;
    Mat<eT> eigvec;

    const bool status = eig_sym_helper(eigval, eigvec, X, 'd', "logmat_sympd()");

    if (status == false) {
      return false;
    }

    const uword N = eigval.n_elem;
    const T* eigval_mem = eigval.memptr();

    bool all_pos = true;

    for (uword i = 0; i < N; ++i) {
      all_pos = (eigval_mem[i] <= T(0)) ? false : all_pos;
    }

    if (all_pos == false) {
      return false;
    }

    eigval = log(eigval);

    out = eigvec * diagmat(eigval) * eigvec.t();

    return true;
  }
#else
  {
    arma_ignore(out);
    arma_ignore(expr);
    arma_stop_logic_error("logmat_sympd(): use of LAPACK must be enabled");
    return false;
  }
#endif
}

//! @}
