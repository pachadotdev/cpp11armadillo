#' @keywords internal
"_PACKAGE"

#' Check that cpp11 can be used
#' @keywords internal
#' @return integer value
check_cpp11 <- function() {
  cpp11::cpp_source(
    code = '
    #include "cpp11/integers.hpp"

    [[cpp11::register]] int add_one() {
      int x = 0;
      x++;
      return x;
    }
    '
  )
}
