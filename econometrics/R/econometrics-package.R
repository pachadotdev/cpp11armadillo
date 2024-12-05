#' @useDynLib econometrics, .registration = TRUE
#' @keywords internal
"_PACKAGE"

#' Chapter 3 data
#' @format Data frame
#' @source Hansen (2022)
"ch3"

#' Chapter 4 data
#' @format Data frame
#' @source Hansen (2022)
"ch4"

#' Chapter 4 data
#' @format Data frame
#' @source Hansen (2022)
"ch4_2"

#' OLS Estimator
#' @param y numeric vector of dependent variable
#' @param X numeric matrix of independent variables
#' @export
ols_mat <- function(y, X) {
  ols_mat_(y, X)
}

#' Influence
#' @inheritParams ols_mat
#' @export
influence_dbl <- function(y, X) {
  influence_dbl_(y, X)
}
