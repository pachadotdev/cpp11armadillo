test_that("cpp11armadillo vs base R (sorted)", {
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

test_that("eigen_gen wrapper works as expected", {
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
})
