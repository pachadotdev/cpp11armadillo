test_that("elemental tests for vectors", {
  x <- c(1.0, 2.0, 3.0)
  expect_equal(x, typedef_Col_double(x))

  x[1] <- NA
  expect_equal(x, typedef_Col_double(x))

  x[1] <- 1.0
  x[2] <- Inf
  expect_equal(x, typedef_Col_double(x))

  x[2] <- -Inf
  expect_equal(x, typedef_Col_double(x))

  x[2] <- NaN
  expect_equal(x, typedef_Col_double(x))

  y <- c(1L, 2L, 3L)
  expect_equal(y, typedef_Col_int(y))

  y[3] <- NA
  expect_equal(y, typedef_Col_int(y))

  y[3] <- Inf
  # class(y) is numeric now!
  expect_error(typedef_Col_int(y), "expected 'integer' actual 'double'")

  y[3] <- -Inf
  expect_error(typedef_Col_int(y), "expected 'integer' actual 'double'")

  y[3] <- NaN
  expect_error(typedef_Col_int(y), "expected 'integer' actual 'double'")

  y <- c(1L, 2L, 3L)
  expect_equal(y, typedef_uvec(y))

  y[1] <- -1L
  expect_equal(y, typedef_uvec(y))
})

test_that("elemental tests for matrices", {
  set.seed(1234)
  x <- matrix(rnorm(4), nrow = 2)
  expect_equal(x, typedef_Mat_double(x))

  y <- matrix(rpois(4, 1), nrow = 2)
  expect_equal(y, typedef_Mat_int(y))

  y2 <- y
  diag(y2) <- 0
  expect_equal(y2, typedef_SpMat_double(y2))
  expect_error(typedef_SpMat_int(y2))

  storage.mode(y2) <- "integer"
  expect_equal(y2, typedef_SpMat_int(y2))
  expect_error(typedef_SpMat_double(y2))

  y[1, 1] <- NA
  expect_equal(y, typedef_Mat_int(y))

  y[1, 1] <- Inf
  expect_error(typedef_Mat_int(y), "expected 'integer' actual 'double'")
  expect_equal(y, typedef_Mat_double(y))

  y[1, 1] <- -Inf
  expect_error(typedef_Mat_int(y), "expected 'integer' actual 'double'")
  expect_equal(y, typedef_Mat_double(y))

  y[1, 1] <- NaN
  expect_error(typedef_Mat_int(y), "expected 'integer' actual 'double'")
  expect_equal(y, typedef_Mat_double(y))
})

test_that("compatible casting for matrices", {
  set.seed(123)
  x <- round(matrix(rnorm(4), nrow = 2), 3)
  res <- typedef_dblmat_exchangeability(x)
  n <- length(res)
  for (i in seq_len(n - 1)) {
    expect_true(all.equal(res[[n]], res[[i]]))
  }

  set.seed(200100)
  y <- matrix(rbinom(25, 1, 0.5), 5, 5)
  storage.mode(y) <- "double"
  res <- typedef_spmat_exchangeability(y)
  n <- length(res)
  for (i in seq_len(n - 1)) {
    expect_true(all.equal(res[[n]], res[[i]]))
  }

  set.seed(200200)
  y <- matrix(rbinom(25, 1, 0.5), 5, 5)
  res <- typedef_spmat_int_exchangeability(y)
  n <- length(res)
  for (i in seq_len(n - 1)) {
    expect_true(all.equal(res[[n]], res[[i]]))
  }

  set.seed(200100)
  x <- matrix(rnorm(4), 2, 2)
  expect_true(typedef_equivalences(x))
})
