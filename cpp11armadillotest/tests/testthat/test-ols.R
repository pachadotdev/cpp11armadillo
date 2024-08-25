test_that("Ordinary Least Squares Matrix (i.e., transposition and inverses)", {
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
})
