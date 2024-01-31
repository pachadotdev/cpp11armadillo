devel <- F
pkgdown <- T

devtools::document()

if (isTRUE(devel)) {
  devtools::load_all()
} else {
  if (pkgdown) {
    pkgdown::build_site()
  }
  devtools::install()
}
