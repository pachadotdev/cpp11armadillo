test_that("elemental tests for vectors", {
  x <- c(1.0, 2.0, 3.0)
  expect_equal(x, typedef_Col_double(x))
  
  y <- c(1L, 2L, 3L)
  expect_equal(y, typedef_Col_int(y))

  expect_equal(y, typedef_uvec(y))

  z <- c(-1L, 2L, 3L)
  expect_equal(z, typedef_uvec(z))
})

test_that("elemental tests for matrices", {
  set.seed(1234)
  x <- matrix(rnorm(4), nrow = 2)
  expect_equal(x, typedef_Mat_double(x))

  y <- matrix(rpois(4,1), nrow = 2)
  expect_equal(y, typedef_Mat_int(y))

  y2 <- y
  diag(y2) <- 0
  expect_equal(y2, typedef_SpMat_double(y2))
  expect_error(typedef_SpMat_int(y2))

  storage.mode(y2) <- "integer"
  expect_equal(y2, typedef_SpMat_int(y2))
  expect_error(typedef_SpMat_double(y2))
})
