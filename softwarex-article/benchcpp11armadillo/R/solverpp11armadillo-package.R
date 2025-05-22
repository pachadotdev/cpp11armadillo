#' @useDynLib benchcpp11armadillo, .registration = TRUE
#' @keywords internal
"_PACKAGE"

#' @export
bench_eig_r <- function(m) {
  eigen(m)$values
}

#' @export
bench_eig_cpp11armadillo <- function(m) {
  bench_eig_cpp11armadillo_(m)
}

#' @export
bench_multi_r <- function(p,q,r) {
  as.numeric(t(p) %*% solve(diag(q)) %*% r)
}

#' @export
bench_multi_cpp11armadillo <- function(p,q,r) {
  bench_multi_cpp11armadillo_(p,q,r)
}
