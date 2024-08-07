devel <- F
pkgdown <- F

setwd("~/github/armadillo")

devtools::document()

if (isTRUE(devel)) {
  devtools::load_all()
} else {
  if (pkgdown) {
    pkgdown::build_site()
  }
  devtools::install()
}

setwd("~/github/armadillo/armadillotest")

devtools::check()
