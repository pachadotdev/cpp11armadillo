cpp11armadillo::pkg_template()

devtools::clean_dll()
cpp11::cpp_register()
devtools::document()

devtools::load_all()
# devtools::install()

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
