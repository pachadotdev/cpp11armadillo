development <- F

devtools::document()

if (isTRUE(development)) {
  devtools::load_all()
} else {
  devtools::install()
}

# devtools::test()
devtools::check()
