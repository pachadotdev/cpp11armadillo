test_that("Cholesky decomposition 1", {
  set.seed(200100)
  x <- matrix(runif(25, 0, 1), nrow = 5, ncol = 5)
  x <- t(x) %*% x
  y <- chol_mat(x, type = "upper")
  z <- chol_mat(x, type = "lower")

  expect_true(all(y[lower.tri(y)] == 0))
  expect_true(all(z[upper.tri(z)] == 0))

  expect_true(all.equal(x, t(y) %*% y))
  expect_true(all.equal(x, z %*% t(z)))
})
