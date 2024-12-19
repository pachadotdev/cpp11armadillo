test_that("examples derived from official documentation", {
  set.seed(123)
  a <- matrix(runif(4), nrow = 2, ncol = 2)
  b <- matrix(runif(4), nrow = 2, ncol = 2)

  res1 <- matrix_fun1_(a)
  expect_type(res1, "double")
  expect_equal(dim(res1), c(2, 2))

  res2 <- matrix_fun2_(a)
  expect_type(res2, "list")
  expect_type(res2[[1]], "double")
  expect_type(res2[[2]], "double")
  expect_equal(dim(res2[[1]]), c(2, 2))
  expect_equal(dim(res2[[2]]), c(2, 2))

  set.seed(123)
  x <- runif(10)
  y <- rep(1, 10)

  res3 <- column_fun1_(x, y)
  expect_type(res3, "double")
  expect_equal(length(res3), 10)

  res4 <- row_fun1_(x, y)
  expect_type(res4, "double")

  res2 <- cube_fun1_(a, b)
  expect_type(res2, "double")
  expect_equal(res2, (2 * a) + (b * b))

  res6 <- field_fun1_(a, b)
  expect_type(res6, "double")
  expect_equal(res6, a + b + t(a) + t(b))

  res7 <- attr_fun1_(a)
  expect_type(res7, "integer")
  expect_equal(res7, c("n_rows" = 2, "n_cols" = 2, "n_elem" = 4))

  res8 <- access_fun1_(a)
  expect_type(res8, "double")
  expect_equal(dim(res8), c(2, 2))

  res9 <- initialization_fun1_(a)
  expect_type(res9, "double")
  expect_equal(dim(res9), c(2, 2))

  res10 <- zeros_fun1_(a)
  expect_type(res10, "double")
  expect_equal(res10, matrix(0, nrow = 2, ncol = 2))

  res11 <- ones_fun1_(a)
  expect_type(res11, "double")
  expect_equal(res11, matrix(3, nrow = 2, ncol = 2))

  res12 <- eye_fun1_(a)
  expect_type(res12, "double")
  expect_equal(res12, 3 * diag(2))
})
