#' @useDynLib cpp11armadillotest, .registration = TRUE
#' @keywords internal
"_PACKAGE"

#' Mtcars dataset in matrix form
#'
#' Reshaped dataframe to test Armadillo linear algebra functions with
#' simple linear models of the form mpg_i = a + b cyl_i or
#' mpg_i = b cyl_i + c_1 cyl4_i + c_2 cyl6_i + c_3 cyl8_i
#'
#' @format A list with two matrices: `y` and `x`, where `y` is the `mpg`
#' variable and `x` is a matrix with the rest of the dataset.
#' @source R's `mtcars` dataset.
"mtcars_mat"

#' Ordinary Least Squares (OLS) regression
#' @param y Numeric vector of dependent variable.
#' @param x Numeric matrix of independent variables.
#' @return A matrix with the estimated coefficients.
#' @name ols
#' @export
ols_mat <- function(y, x) { ols_mat_(y, x) }

#' @rdname ols
#' @return A vector with the estimated coefficients.
#' @export
ols_dbl <- function(y, x) { ols_dbl_(y, x) }

#' Eigenvalues and eigenvectors of a symmetric matrix
#' @param x Numeric matrix.
#' @return A matrix with the eigenvalues.
#' @name eigen_sym
#' @export
eigen_sym_mat <- function(x) { eigen_sym_mat_(x) }

#' @rdname eigen_sym
#' @export
eigen_sym_dbl <- function(x) { eigen_sym_dbl_(x) }

#' Eigenvalues and eigenvectors of a general matrix
#' @param x Numeric matrix.
#' @return A matrix with eigenvalues.
#' @name eigen_gen
#' @export
eigen_gen_mat <- function(x) { eigen_gen_mat_(x) }

#' @rdname eigen_gen
#' @return A matrix with eigenvalues.
#' @export
eigen_gen_mat_complex_wrapper <- function(x) {
  eigen_gen_mat_complex_wrapper_(x)
}

#' @rdname eigen_gen
#' @return A vector with eigenvalues.
#' @export
eigen_gen_dbl_complex_wrapper <- function(x) {
  eigen_gen_dbl_complex_wrapper_(x)
}

#' @rdname eigen_gen
#' @return A vector with eigenvalues.
#' @export
eigen_gen_no_wrapper <- function(x) {
  eigen_gen_no_wrapper_(x)
}

#' Cholesky decomposition
#' @param x Numeric matrix.
#' @param type Character string with the type of decomposition.
#' @return A matrix with the Cholesky decomposition.
#' @name chol
#' @export
chol_mat <- function(x, type) { chol_mat_(x, type) }

#' Ordinary Least Squares (OLS) regression using QR decomposition
#' @param y Numeric vector of dependent variable.
#' @param x Numeric matrix of independent variables.
#' @param econ Logical value indicating if the economic QR version should be used.
#' @return A matrix with the estimated coefficients.
#' @name ols_qr
#' @export
ols_qr_mat <- function(y, x, econ) { ols_qr_mat_(y, x, econ) }

#' @rdname ols_qr
#' @return A vector with the estimated coefficients.
#' @export
ols_qr_dbl <- function(y, x, econ) { ols_qr_dbl_(y, x, econ) }

#' Capital Asset Pricing Model (CAPM)
#' @param r Numeric vector of returns.
#' @param m Numeric vector of market returns.
#' @param f Numeric value of risk-free return.
#' @return A matrix with the CAPM betas.
#' @name capm
#' @export
capm <- function(r, m, f) { capm_(r, m, f) }

#' Typedefs
#' @param x Numeric vector.
#' @return A matrix with the input vector.
#' @name typedef
#' @export
typedef_Col_double <- function(x) { typedef_Col_double_(x) }

#' @rdname typedef
#' @return A matrix with the input vector.
#' @export
typedef_Col_int <- function(x) { typedef_Col_int_(x) }

#' @rdname typedef
#' @return A matrix with the input vector.
#' @export
typedef_uvec <- function(x) { typedef_uvec_(x) }

#' @rdname typedef
#' @return A matrix with the input vector.
#' @export
typedef_Mat_double <- function(x) { typedef_Mat_double_(x) }

#' @rdname typedef
#' @return A matrix with the input vector.
#' @export
typedef_Mat_int <- function(x) { typedef_Mat_int_(x) }

#' @rdname typedef
#' @return A matrix with the input vector.
#' @export
typedef_SpMat_double <- function(x) { typedef_SpMat_double_(x) }

#' @rdname typedef
#' @return A matrix with the input vector.
#' @export
typedef_SpMat_int <- function(x) { typedef_SpMat_int_(x) }
