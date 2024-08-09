test_that("Ordinary Least Squares Matrix via QR", {
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
})
