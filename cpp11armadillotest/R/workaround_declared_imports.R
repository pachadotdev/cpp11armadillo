#' @keywords internal
workaround_declared_imports <- function() {
  # just to avoid a warning because testthat requires me to add cpp11
  # and cpp11armadillotest to the Imports field of DESCRIPTION
  # besides the LinkingTo field

  cpp11::cpp_source(
    code = "
      #include <cpp11.hpp>

      using namespace cpp11;

      [[cpp11::register]] int one_plus_one() {
        return 1 + 1;
      }
    "
  )

  sum(cpp11armadillo::mtcars_mat$y)
}
