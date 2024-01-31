# run this line if you want to replace all the files provided by the template
# cpp11armadillo::pkg_template()

development <- F

devtools::document()

if (isTRUE(development)) {
  devtools::load_all()
} else {
  devtools::install()
  pkgdown::build_site()
}

# devtools::test()
devtools::check()
