test_that("QR decomposition", {
  # from https://en.wikipedia.org/wiki/QR_decomposition#Example
  x <- matrix(c(12, -51, 4, 6, 167, -68, -4, 24, -41),
    nrow = 3, ncol = 3, byrow = TRUE
  )
  y <- qr_mat(x, econ = FALSE)
  z <- qr_mat(x, econ = TRUE)

  expect_equal(y$Q %*% y$R, x)
  expect_equal(z$Q %*% z$R, x)
})
