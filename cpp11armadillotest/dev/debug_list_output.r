rebuild <- T

if (rebuild) {
  devtools::clean_dll()
  cpp11::cpp_register()
  devtools::document()
  devtools::load_all()
} else {
  devtools::load_all()
}

x <- cpp11armadillo::mtcars_mat$x
y <- cpp11armadillo::mtcars_mat$y

x <- x[, c("wt", "cyl4", "cyl6", "cyl8")]

x <- cor(x)

eigen_gen_mat(x)
eigen_gen_dbl(x)

eigen_gen_mat_complex_wrapper(x)
eigen_gen_dbl_complex_wrapper(x)

all.equal(eigen_gen_dbl(x), eigen_gen_dbl_complex_wrapper(x))
all.equal(eigen_gen_mat(x), eigen_gen_mat_complex_wrapper(x))
