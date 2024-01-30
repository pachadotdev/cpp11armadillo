devtools::load_all()
x <- cpp11armadillo::mtcars_mat$x
y <- cpp11armadillo::mtcars_mat$y

x <- x[, c("wt", "cyl4", "cyl6", "cyl8")]

x <- cor(x)

eigen_gen_dbl_2(x)
