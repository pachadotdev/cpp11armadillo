test_that("examples derived from official documentation", {
  set.seed(123)
  a <- matrix(runif(4), nrow = 2, ncol = 2)
  b <- matrix(runif(4), nrow = 2, ncol = 2)

  res1 <- matrix1_(a)
  expect_type(res1, "double")
  expect_equal(dim(res1), c(2, 2))

  res2 <- matrix2_(a)
  expect_type(res2, "list")
  expect_type(res2[[1]], "double")
  expect_type(res2[[2]], "double")
  expect_equal(dim(res2[[1]]), c(2, 2))
  expect_equal(dim(res2[[2]]), c(2, 2))

  set.seed(123)
  x <- runif(10)
  y <- rep(1, 10)

  res3 <- column1_(x, y)
  expect_type(res3, "double")
  expect_equal(length(res3), 10)

  res4 <- row1_(x, y)
  expect_type(res4, "double")

  res2 <- cube1_(a, b)
  expect_type(res2, "double")
  expect_equal(res2, (2 * a) + (b * b))

  res6 <- field1_(a, b)
  expect_type(res6, "double")
  expect_equal(res6, a + b + t(a) + t(b))

  res7 <- attr1_(a)
  expect_type(res7, "integer")
  expect_equal(res7, c("n_rows" = 2, "n_cols" = 2, "n_elem" = 4))

  res8 <- access1_(a)
  expect_type(res8, "double")
  expect_equal(dim(res8), c(2, 2))

  res9 <- initialization1_(a)
  expect_type(res9, "double")
  expect_equal(dim(res9), c(2, 2))

  res10 <- zeros1_(a)
  expect_type(res10, "double")
  expect_equal(res10, matrix(0, nrow = 2, ncol = 2))

  res11 <- ones1_(a)
  expect_type(res11, "double")
  expect_equal(res11, matrix(3, nrow = 2, ncol = 2))

  res12 <- eye1_(a)
  expect_type(res12, "double")
  expect_equal(res12, 3 * diag(2))

  res13 <- randu1_(a)
  expect_type(res13, "double")
  expect_equal(dim(res13), c(2, 2))

  res14 <- randn1_(a)
  expect_type(res14, "double")
  expect_equal(dim(res14), c(2, 2))

  set.seed(123)
  res15 <- randu2_(2L)

  set.seed(123)
  res15_2 <- randu2_(2L)

  set.seed(321)
  res15_3 <- randu2_(2L)

  expect_equal(res15, res15_2)
  res15_4 <- all.equal(res15, res15_3)
  expect_match(res15_4, "Mean relative difference")

  set.seed(123)
  res16 <- randn2_(2L)

  set.seed(123)
  res16_2 <- randn2_(2L)

  set.seed(321)
  res16_3 <- randn2_(2L)

  expect_equal(res16, res16_2)
  res16_4 <- all.equal(res16, res16_3)
  expect_match(res16_4, "Mean relative difference")

  res17 <- fill1_(a)
  expect_type(res17, "double")
  expect_equal(dim(res17), c(2, 2))

  res18 <- imbue1_(a)
  expect_type(res18, "double")
  expect_equal(dim(res18), c(2, 2))

  set.seed(123)
  res19 <- imbue2_(a)

  set.seed(123)
  res19_2 <- imbue2_(a)

  set.seed(321)
  res19_3 <- imbue2_(a)

  expect_type(res19, "double")
  expect_equal(res19, res19_2)
  res19_4 <- all.equal(res19, res19_3)
  expect_match(res19_4, "Mean relative difference")

  res20 <- clean1_(2L)
  expect_type(res20, "double")
  expect_equal(diag(res20), rep(0, 2))

  res21 <- replace1_(2L)
  expect_type(res21, "double")
  expect_equal(diag(res21), rep(0, 2))

  res22 <- clamp1_(2L)
  expect_type(res22, "double")
  expect_equal(diag(res22), rep(0.2, 2))

  res23 <- transform1_(2L)
  expect_type(res23, "double")
  expect_equal(diag(res23), rep(123, 2))
  
  res24 <- for_each1_(2L)
  expect_type(res24, "double")
  expect_equal(dim(res24), c(2, 2))

  res25 <- set_size1_(2L)
  expect_type(res25, "double")
  expect_equal(length(res25), 2)

  res26 <- reshape1_(2L)
  expect_type(res26, "double")
  expect_equal(dim(res26), c(2 - 1, 2 + 1))

  res27 <- resize1_(2L)
  expect_type(res27, "double")
  expect_equal(dim(res27), c(2 - 1, 2 + 1))

  res28 <- copy_size1_(2L)
  expect_type(res28, "integer")
  expect_equal(length(res28), 2)

  res29 <- reset1_(2L)
  expect_type(res29, "integer")
  expect_equal(length(res29), 2)

  res30 <- subview1_(5L)
  expect_type(res30, "double")
  expect_equal(dim(res30), c(5, 5))

  res31 <- subview2_(5L)
  expect_type(res31, "double")
  expect_equal(dim(res31), c(5, 3))

  res32 <- diagonal1_(2L)
  expect_type(res32, "double")
  expect_equal(length(res32), 2)

  res33 <- each_col1_(2L)
  expect_type(res33, "double")
  expect_equal(dim(res33), c(2, 3))

  res34 <- each_row1_(2L)
  expect_type(res34, "double")
  expect_equal(dim(res34), c(3, 2))

  res35 <- each_slice1_(2L)
  expect_type(res35, "double")
  expect_equal(dim(res35), c(2, 3))

  res36 <- set_real1_(2L)
  expect_type(res36, "list")
  expect_type(res36[[1]], "double")
  expect_equal(dim(res36[[1]]), c(3, 1))

  res37 <- set_real2_(2L)
  expect_type(res37, "list")
  expect_type(res37[[1]], "double")
  expect_equal(dim(res37[[1]]), c(1, 3))

  res38 <- set_imag1_(2L)
  expect_type(res38, "list")
  expect_type(res38[[1]], "double")
  expect_equal(dim(res38[[1]]), c(3, 1))

  res39 <- insert_columns1_(2L)
  expect_type(res39, "double")
  expect_equal(dim(res39), c(2, 5))

  res40 <- insert_rows1_(2L)
  expect_type(res40, "double")
  expect_equal(dim(res40), c(5, 2))

  res41 <- insert_slices1_(2L)
  expect_type(res41, "double")
  expect_equal(dim(res41), c(2, 2))

  res42 <- shed_columns1_(2L)
  expect_type(res42, "double")
  expect_equal(dim(res42), c(2, 5))

  res42 <- shed_rows1_(2L)
  expect_type(res42, "double")
  expect_equal(dim(res42), c(5, 2))

  res43 <- shed_slices1_(2L)
  expect_type(res43, "double")
  expect_equal(dim(res43), c(2, 2))

  res44 <- swap_columns1_(2L)
  expect_type(res44, "double")
  expect_equal(dim(res44), c(2, 10))

  res45 <- swap_rows1_(2L)
  expect_type(res45, "double")
  expect_equal(dim(res45), c(10, 2))

  res46 <- swap1_(2L)
  expect_type(res46, "double")
  expect_equal(dim(res46), c(4, 1))

  res47 <- memptr1_(2L)
  expect_type(res47, "double")
  expect_equal(dim(res47), c(2, 2))

  res48 <- colptr1_(2L)
  expect_type(res48, "double")
  expect_equal(dim(res48), c(2, 2))
})
