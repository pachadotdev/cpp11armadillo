# run this line if you want to replace all the files provided by the template
# cpp11armadillo::pkg_template()

development <- TRUE

devtools::clean_dll()
cpp11::cpp_register()
devtools::document()

if (isTRUE(development)) {
  devtools::load_all()
} else {
  devtools::install()
  devtools::load_all()
}

# Estimate the model y ~ constant + x
# with y and x gaussian random variables

set.seed(123)
y <- matrix(rnorm(100), ncol = 1, nrow = 100)
x <- matrix(1, ncol = 1, nrow = 100)
x <- cbind(x, rnorm(100, 0, 1))

# Armadillo computation
ols_mat(y, x)
ols_double(y, x)

# Base R computation
solve(t(x) %*% x) %*% t(x) %*% y
lm(y ~ x + 0)
