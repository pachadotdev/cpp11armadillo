#' Get Armadillo version
#' 
#' Provides the Armadillo C++ library version name and number included in the
#' package.
#' 
#' @export
#' @return A string with the Armadillo version name and number
#' @examples 
#' armadillo_version()
armadillo_version <- function() {
  # finp <- system.file("include/armadillo/arma_version.hpp", package = "cpp11armadillo")
  # lines <- readLines(finp)
 
  # number <- c(
  #   grep("ARMA_VERSION_MAJOR", lines, value = T)[[1]],
  #   grep("ARMA_VERSION_MINOR", lines, value = T)[[1]],
  #   grep("ARMA_VERSION_PATCH", lines, value = T)[[1]]
  # )
  # number <- gsub("[^0-9]", "", number)

  # name <- grep("ARMA_VERSION_NAME", lines, value = T)[[1]]
  # name <- gsub(".*\"(.*)\".*", "\\1", name)

  # paste(name, paste(number, collapse = "."))

  return("Stochastic Parrot 14.0.2")
}
