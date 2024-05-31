test_that("QR decomposition", {
  # from https://en.wikipedia.org/wiki/QR_decomposition#Example
  x <- matrix(c(12, -51, 4, 6, 167, -68, -4, 24, -41),
    nrow = 3, ncol = 3, byrow = TRUE
  )
  y <- qr_mat(x, econ = FALSE)
  z <- qr_mat(x, econ = TRUE)

  expect_equal(y$Q %*% y$R, x)
  expect_equal(z$Q %*% z$R, x)
  
  expect_error(eigen_gen_dbl(matrix(c(1.0, NA, 3.0, 4.0), nrow = 2)))
  expect_error(eigen_gen_dbl(matrix(c(1.0, NaN, 3.0, 4.0), nrow = 2)))
  expect_error(eigen_gen_dbl(matrix(c(1.0,Inf,3.0,4.0), nrow = 2)))
})
