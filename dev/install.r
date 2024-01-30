devel <- F
pkgdown <- F

# cpp_vendor() # run only when updating C++ headers
devtools::clean_dll()
cpp11::cpp_register()
devtools::document()

if (isTRUE(devel)) {
  devtools::load_all()
} else {
  if (pkgdown) {
    pkgdown::build_site()
  }
  devtools::install()
}
