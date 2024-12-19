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

  res13 <- randu_fun1_(a)
  expect_type(res13, "double")
  expect_equal(dim(res13), c(2, 2))

  res14 <- randn_fun1_(a)
  expect_type(res14, "double")
  expect_equal(dim(res14), c(2, 2))

  set.seed(123)
  res15 <- randu_fun2_(2L)

  set.seed(123)
  res15_2 <- randu_fun2_(2L)

  set.seed(321)
  res15_3 <- randu_fun2_(2L)

  expect_equal(res15, res15_2)
  res15_4 <- all.equal(res15, res15_3)
  expect_match(res15_4, "Mean relative difference")

  set.seed(123)
  res16 <- randn_fun2_(2L)

  set.seed(123)
  res16_2 <- randn_fun2_(2L)

  set.seed(321)
  res16_3 <- randn_fun2_(2L)

  expect_equal(res16, res16_2)
  res16_4 <- all.equal(res16, res16_3)
  expect_match(res16_4, "Mean relative difference")

  res17 <- fill_fun1_(a)
  expect_type(res17, "double")
  expect_equal(dim(res17), c(2, 2))

  res18 <- imbue_fun1_(a)
  expect_type(res18, "double")
  expect_equal(dim(res18), c(2, 2))

  set.seed(123)
  res19 <- imbue_fun2_(a)

  set.seed(123)
  res19_2 <- imbue_fun2_(a)

  set.seed(321)
  res19_3 <- imbue_fun2_(a)

  expect_type(res19, "double")
  expect_equal(res19, res19_2)
  res19_4 <- all.equal(res19, res19_3)
  expect_match(res19_4, "Mean relative difference")

  res20 <- clean_fun1_(2L)
  expect_type(res20, "double")
  expect_equal(diag(res20), rep(0, 2))

  res21 <- replace_fun1_(2L)
  expect_type(res21, "double")
  expect_equal(diag(res21), rep(0, 2))

  res22 <- clamp_fun1_(2L)
  expect_type(res22, "double")
  expect_equal(diag(res22), rep(0.2, 2))

  res23 <- transform_fun1_(2L)
  expect_type(res23, "double")
  expect_equal(diag(res23), rep(123, 2))
  
  res24 <- for_each_fun1_(2L)
  expect_type(res24, "double")
  expect_equal(dim(res24), c(2, 2))

  res25 <- set_size_fun1_(2L)
  expect_type(res25, "double")
  expect_equal(length(res25), 2)

  res26 <- reshape_fun1_(2L)
  expect_type(res26, "double")
  expect_equal(dim(res26), c(2 - 1, 2 + 1))

  res27 <- resize_fun1_(2L)
  expect_type(res27, "double")
  expect_equal(dim(res27), c(2 - 1, 2 + 1))

  res28 <- copy_size_fun1_(2L)
  expect_type(res28, "integer")
  expect_equal(length(res28), 2)

  res29 <- reset_fun1_(2L)
  expect_type(res29, "integer")
  expect_equal(length(res29), 2)

  res30 <- subview_fun1_(5L)
  expect_type(res30, "double")
  expect_equal(dim(res30), c(5, 5))

  res31 <- subview_fun2_(5L)
  expect_type(res31, "double")
  expect_equal(dim(res31), c(5, 3))

  res32 <- diagonal_fun1_(2L)
  expect_type(res32, "double")
  expect_equal(length(res32), 2)

  res33 <- each_col_fun1_(2L)
  expect_type(res33, "double")
  expect_equal(dim(res33), c(2, 3))
})
