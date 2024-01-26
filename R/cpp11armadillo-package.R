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
