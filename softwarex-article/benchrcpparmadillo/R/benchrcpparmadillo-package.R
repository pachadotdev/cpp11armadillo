#' @useDynLib benchrcpparmadillo, .registration = TRUE
#' @keywords internal
"_PACKAGE"

#' @export
bench_eig_rcpparmadillo <- function(m) {
  as.numeric(bench_eig_rcpparmadillo_(m))
}

#' @export
bench_multi_rcpparmadillo <- function(p,q,r) {
  bench_multi_rcpparmadillo_(p,q,r)
}
