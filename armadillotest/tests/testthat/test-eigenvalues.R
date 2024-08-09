test_that("armadillo vs base R (sorted)", {
  x <- mtcars_mat$x
  y <- mtcars_mat$y

  x <- x[, c("wt", "cyl4", "cyl6", "cyl8")]

  x <- cor(x)

  # Armadillo computation
  a <- sort(eigen_sym_mat(x))

  # Base R computation
  b <- sort(eigen(x)$values)

  expect_equal(a, b)
})

test_that("eigen_gen wrappr works as expected", {
  x <- mtcars_mat$x
  y <- mtcars_mat$y

  x <- x[, c("wt", "cyl4", "cyl6", "cyl8")]

  x <- cor(x)

  expect_equal(eigen_gen_mat(x), eigen_gen_mat_complex_wrapper(x))

  expect_equal(eigen_gen_mat_complex_wrapper(x), eigen_gen_no_wrapper(x))
})
