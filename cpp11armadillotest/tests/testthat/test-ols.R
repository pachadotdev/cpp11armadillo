test_that("Ordinary Least Squares Matrix (i.e., transposition and inverses)", {
  x <- cpp11armadillo::mtcars_mat$x
  y <- cpp11armadillo::mtcars_mat$y

  x <- x[, c("wt", "cyl4", "cyl6", "cyl8")]

  # Armadillo computation
  a <- ols_mat(y, x)

  # Base R computation
  b <- matrix(solve(t(x) %*% x) %*% t(x) %*% y, ncol = 1)

  expect_equal(a, b)
})

test_that("Ordinary Least Squares Doubles (i.e., transposition and inverses)", {
  x <- cpp11armadillo::mtcars_mat$x
  y <- cpp11armadillo::mtcars_mat$y

  x <- x[, c("wt", "cyl4", "cyl6", "cyl8")]

  # Armadillo computation
  a <- matrix(ols_dbl(y, x), ncol = 1)

  # Base R computation
  b <- matrix(solve(t(x) %*% x) %*% t(x) %*% y, ncol = 1)

  expect_equal(a, b)
})
