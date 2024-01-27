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

# Estimate the model mpg ~ wt + cyl{4,6,8} ----

x <- cpp11armadillo::mtcars_mat$x
y <- cpp11armadillo::mtcars_mat$y

x <- x[, c("wt", "cyl4", "cyl6", "cyl8")]

# Armadillo computation
ols_mat(y, x)
ols_double(y, x)

# Base R computation
solve(t(x) %*% x) %*% t(x) %*% y
lm(mpg ~ wt + as.factor(cyl) + 0, data = mtcars)
