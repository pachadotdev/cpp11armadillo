library(cpp11armadillotest)

# CAPM Model ----

set.seed(200100)
f <- 0.02
m <- matrix(rnorm(3, 0, 0.1), nrow = 3, ncol = 1)
r <- matrix(rnorm(6, 0, 0.1), nrow = 3, ncol = 2)

beta <- cov(r, m) / as.double(var(m))
m_avg <- mean(m)

capm_r <- f + beta * (m_avg - f)
capm_cpp <- capm(r, m, f)

expect_equal(capm_r, capm_cpp)

# Cholesky decomposition ----

set.seed(200100)
x <- matrix(runif(25, 0, 1), nrow = 5, ncol = 5)
x <- t(x) %*% x
y <- chol_mat(x, type = "upper")
z <- chol_mat(x, type = "lower")

expect_true(all(y[lower.tri(y)] == 0))
expect_true(all(z[upper.tri(z)] == 0))

expect_true(all.equal(x, t(y) %*% y))
expect_true(all.equal(x, z %*% t(z)))

# cpp11armadillo vs base R (sorted) ----

x <- mtcars_mat$x
y <- mtcars_mat$y

x <- x[, c("wt", "cyl4", "cyl6", "cyl8")]

x <- cor(x)

# Armadillo computation
a <- sort(eigen_sym_mat(x))

# Base R computation
b <- sort(eigen(x)$values)

expect_equal(a, b)

# eigen_gen wrapper works as expected
x <- mtcars_mat$x
y <- mtcars_mat$y

x <- x[, c("wt", "cyl4", "cyl6", "cyl8")]

x <- cor(x)

expect_equal(eigen_gen_mat(x), eigen_gen_mat_complex_wrapper(x))

expect_equal(eigen_gen_mat_complex_wrapper(x), eigen_gen_no_wrapper(x))

# case where the imaginary part is not zero

x <- matrix(c(4 / 5, 3 / 5, 1, -3 / 5, 4 / 5, 2, 0, 0, 2), 3, 3)

a <- eigen_gen_mat_complex_wrapper(x)

b <- c()
for (i in 1:3) {
  b[i] <- complex(real = a$real[i], imaginary = a$imag[i])
}
b <- sort(b)

c <- sort(eigen(x)$values)

expect_equal(b, c)

# Ordinary Least Squares Matrix (i.e., transposition and inverses) ----

x <- mtcars_mat$x
y <- mtcars_mat$y

x <- x[, c("wt", "cyl4", "cyl6", "cyl8")]

# Armadillo computation
a <- ols_mat(y, x)
b <- matrix(ols_dbl(y, x), ncol = 1)

# Base R computation
c <- matrix(solve(t(x) %*% x) %*% t(x) %*% y, ncol = 1)

expect_equal(a, c)
expect_equal(b, c)

# Ordinary Least Squares Matrix via QR ----

x <- mtcars_mat$x
y <- mtcars_mat$y

x <- x[, c("wt", "cyl4", "cyl6", "cyl8")]

# Armadillo computation
a <- ols_qr_mat(y, x, econ = TRUE)
b <- matrix(ols_qr_dbl(y, x, econ = TRUE), ncol = 1)
c <- ols_qr_mat(y, x, econ = FALSE)
d <- matrix(ols_qr_dbl(y, x, econ = FALSE), ncol = 1)

# Base R computation
e <- matrix(solve(t(x) %*% x) %*% t(x) %*% y, ncol = 1)

expect_equal(a, e)
expect_equal(b, e)
expect_equal(c, e)
expect_equal(d, e)

# Elemental tests for vectors ----

x <- c(1.0, 2.0, 3.0)
expect_equal(x, typedef_Col_double(x))

x[1] <- NA
expect_equal(x, typedef_Col_double(x))

x[1] <- 1.0
x[2] <- Inf
expect_equal(x, typedef_Col_double(x))

x[2] <- -Inf
expect_equal(x, typedef_Col_double(x))

x[2] <- NaN
expect_equal(x, typedef_Col_double(x))

y <- c(1L, 2L, 3L)
expect_equal(y, typedef_Col_int(y))

y[3] <- NA
expect_equal(y, typedef_Col_int(y))

y[3] <- Inf
# class(y) is numeric now!
expect_error(typedef_Col_int(y), "expected 'integer' actual 'double'")

y[3] <- -Inf
expect_error(typedef_Col_int(y), "expected 'integer' actual 'double'")

y[3] <- NaN
expect_error(typedef_Col_int(y), "expected 'integer' actual 'double'")

y <- c(1L, 2L, 3L)
expect_equal(y, typedef_uvec(y))

y[1] <- -1L
expect_equal(y, typedef_uvec(y))

# Elemental tests for matrices ----

set.seed(1234)
x <- matrix(rnorm(4), nrow = 2)
expect_equal(x, typedef_Mat_double(x))

y <- matrix(rpois(4, 1), nrow = 2)
expect_equal(y, typedef_Mat_int(y))

y2 <- y
diag(y2) <- 0
expect_equal(y2, typedef_SpMat_double(y2))
expect_error(typedef_SpMat_int(y2))

storage.mode(y2) <- "integer"
expect_equal(y2, typedef_SpMat_int(y2))
expect_error(typedef_SpMat_double(y2))

y[1, 1] <- NA
expect_equal(y, typedef_Mat_int(y))

y[1, 1] <- Inf
expect_error(typedef_Mat_int(y), "expected 'integer' actual 'double'")
expect_equal(y, typedef_Mat_double(y))

y[1, 1] <- -Inf
expect_error(typedef_Mat_int(y), "expected 'integer' actual 'double'")
expect_equal(y, typedef_Mat_double(y))

y[1, 1] <- NaN
expect_error(typedef_Mat_int(y), "expected 'integer' actual 'double'")
expect_equal(y, typedef_Mat_double(y))
