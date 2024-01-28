# cpp_vendor() # run only when updating C++ headers
devtools::clean_dll()
cpp11::cpp_register()
devtools::document()
pkgdown::build_site()
devtools::install()
# devtools::load_all()
