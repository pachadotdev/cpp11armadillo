setwd("~/github/cpp11armadillo")

devtools::document()
# pkgdown::build_site()
devtools::check()
devtools::install()

setwd("~/github/cpp11armadillo/cpp11armadillotest")

devtools::clean_dll()
devtools::document()
devtools::check()
