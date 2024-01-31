# run this line if you want to replace all the files provided by the template
# cpp11armadillo::pkg_template()

development <- F

devtools::clean_dll()
cpp11::cpp_register()
devtools::document()

if (isTRUE(development)) {
  devtools::load_all()
} else {
  devtools::install()
}

# devtools::test()
devtools::check()
