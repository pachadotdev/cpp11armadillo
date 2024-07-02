devel <- F
pkgdown <- F

setwd("~/github/cpp11armadillo")

devtools::document()

if (isTRUE(devel)) {
  devtools::load_all()
} else {
  if (pkgdown) {
    pkgdown::build_site()
  }
  devtools::install()
}

setwd("~/github/cpp11armadillo/cpp11armadillotest")

devtools::check()
