test_that("examples derived from official documentation", {
  set.seed(123)
  a <- matrix(runif(25), nrow = 5, ncol = 5)
  b <- matrix(runif(25), nrow = 5, ncol = 5)

  res1 <- matrix_fun1_(a)
  expect_type(res1, "double")
  expect_equal(dim(res1), c(5, 5))

  res2 <- matrix_fun2_(a)
  expect_type(res2, "list")
  expect_type(res2[[1]], "double")
  expect_type(res2[[2]], "double")
  expect_equal(dim(res2[[1]]), c(5, 5))
  expect_equal(dim(res2[[2]]), c(5, 5))

  set.seed(123)
  x <- runif(10)
  y <- rep(1, 10)

  res3 <- column_fun1_(x, y)
  expect_type(res3, "double")
  expect_equal(length(res3), 10)

  res4 <- row_fun1_(x, y)
  expect_type(res4, "double")

  res5 <- cube_fun1_(a, b)
  expect_type(res5, "double")
  expect_equal(res5, (2 * a) + (b * b))

  res6 <- field_fun1_(a, b)
  expect_type(res6, "double")
  expect_equal(res6, a + b + t(a) + t(b))
})
