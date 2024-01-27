test_that("Sorted eigenvalues", {
  x <- cpp11armadillo::mtcars_mat$x
  y <- cpp11armadillo::mtcars_mat$y

  x <- x[, c("wt", "cyl4", "cyl6", "cyl8")]

  x <- cor(x)

  # Armadillo computation
  a <- sort(eigen_sym_mat(x))

  # Base R computation
  b <- sort(eigen(x)$values)

  expect_equal(a, b)
})
