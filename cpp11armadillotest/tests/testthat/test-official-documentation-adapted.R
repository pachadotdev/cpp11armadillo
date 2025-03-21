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

  res49 <- iterators1_(2L)
  expect_type(res49, "double")
  expect_equal(dim(res49), c(2, 3))

  res50 <- iterators2_(2L)
  expect_type(res50, "double")
  expect_equal(dim(res50), c(2, 3))

  res51 <- iterators3_(2L)
  expect_type(res51, "double")
  expect_equal(dim(res51), c(2, 4))

  res52 <- iterators4_(2L)
  expect_type(res52, "double")
  expect_equal(dim(res52), c(2, 2))

  res53 <- compatibility1_(2L)
  expect_type(res53, "double")
  expect_equal(length(res53), 2)

  res54 <- compatibility2_(2L)
  expect_type(res54, "integer")
  expect_equal(length(res54), 2)

  res55 <- as_col1_(2L)
  expect_type(res55, "double")
  expect_equal(length(res55), 6)

  res56 <- as_row1_(2L)
  expect_type(res56, "double")
  expect_equal(length(res56), 6)

  res57 <- col_as_mat1_(2L)
  expect_type(res57, "list")
  expect_equal(cbind(
    res57[[1]][, 1], res57[[2]][, 1], res57[[3]][, 1],
    res57[[4]][, 1]
  ), res57[[5]])

  res58 <- row_as_mat1_(2L)
  expect_type(res58, "list")
  expect_equal(rbind(
    res58[[1]][1, ], res58[[2]][1, ], res58[[3]][1, ],
    res58[[4]][1, ]
  ), res58[[5]])

  res59 <- as_dense1_(2L)
  expect_type(res59, "double")
  expect_equal(length(res59), 2)

  res60 <- transpose1_(2L)
  expect_type(res60, "double")
  expect_equal(dim(res60), c(3, 2))

  res61 <- transpose2_(2L)
  expect_type(res61, "double")
  expect_equal(dim(res61), c(3, 2))

  A <- matrix(c(1, 0, 0, 1, 1, 0, 0, 1, 1), nrow = 3, ncol = 3, byrow = TRUE)
  b <- c(6.50, 7.50, 8.50)
  res62 <- inverse1_(A, b)
  expect_type(res62, "double")
  expect_equal(res62, solve(A, b))

  res63 <- maxmin1_(2)
  expect_type(res63, "double")
  expect_equal(length(res63), 2)

  res64 <- index_maxmin1_(2)
  expect_type(res64, "double")
  expect_equal(length(res64), 6)

  res65 <- in_range1_(2)
  expect_type(res65, "logical")
  expect_equal(length(res65), 3)

  res66 <- is_empty1_(2)
  expect_type(res66, "logical")
  expect_equal(length(res66), 2)

  res67 <- is_vec1_(2)
  expect_type(res67, "logical")
  expect_equal(length(res67), 5)

  res68 <- is_sorted1_(2)
  expect_type(res68, "logical")
  expect_equal(length(res68), 4)

  res69 <- is_triangular1_(2)
  expect_type(res69, "logical")
  expect_equal(length(res69), 3)

  res70 <- is_diagonal1_(2)
  expect_type(res70, "logical")
  expect_equal(length(res70), 3)

  res71 <- is_square1_(2)
  expect_type(res71, "logical")
  expect_equal(length(res71), 3)

  res72 <- is_symmetric1_(2)
  expect_type(res72, "logical")
  expect_equal(length(res72), 3)

  res73 <- is_hermitian1_(2)
  expect_type(res73, "logical")
  expect_equal(length(res73), 3)

  res74 <- is_sympd1_(2)
  expect_type(res74, "logical")
  expect_equal(length(res74), 3)

  res75 <- is_zero1_(2)
  expect_type(res75, "logical")
  expect_equal(length(res75), 3)

  res76 <- is_finite1_(2)
  expect_type(res76, "logical")
  expect_equal(length(res76), 3)

  res77 <- has_inf1_(2)
  expect_type(res77, "logical")
  expect_equal(length(res77), 3)

  res78 <- has_nan1_(2)
  expect_type(res78, "logical")
  expect_equal(length(res78), 3)

  res79 <- linspace1_(10)
  expect_type(res79, "double")
  expect_equal(length(res79), 10)

  res80 <- logspace1_(10)
  expect_type(res80, "double")
  expect_equal(length(res80), 10)

  res81 <- regspace1_(0.1)
  expect_type(res81, "double")
  expect_equal(length(res81), 11)

  res82 <- randperm1_(5, 3)
  expect_type(res82, "integer")
  expect_equal(length(res82), 5 + 3)

  res83 <- eye2_(2)
  expect_type(res83, "double")
  expect_equal(dim(res83), c(2, 2))

  res84 <- ones2_(2)
  expect_type(res84, "double")
  expect_equal(dim(res84), c(2, 2))

  res85 <- zeros2_(2)
  expect_type(res85, "double")
  expect_equal(dim(res85), c(2, 2))

  res86 <- randu3_(2)
  expect_type(res86, "double")
  expect_equal(dim(res86), c(2, 2))

  res87 <- randn3_(2)
  expect_type(res87, "double")
  expect_equal(dim(res87), c(2, 2))

  res88 <- randg3_(2)
  expect_type(res88, "double")
  expect_equal(dim(res88), c(2, 2))

  res89 <- speye1_(2)
  expect_type(res89, "double")
  expect_equal(dim(res89), c(2, 2))

  res90 <- spones1_(2)
  expect_type(res90, "double")
  expect_equal(dim(res90), c(2, 2))

  res91 <- sprandu1_(2)
  expect_type(res91, "double")
  expect_equal(dim(res91), c(2, 2))

  res91 <- sprandn1_(2)
  expect_type(res91, "double")
  expect_equal(dim(res91), c(2, 2))

  res92 <- toeplitz1_(2)
  expect_type(res92, "double")
  expect_equal(dim(res92), c(2, 2))

  res93 <- abs1_(2)
  expect_type(res93, "double")
  expect_equal(dim(res93), c(2, 2))

  res94 <- accu1_(2)
  expect_type(res94, "double")
  expect_equal(length(res94), 1)

  res95 <- affmul1_(2)
  expect_type(res95, "double")
  expect_equal(length(res95), 2)

  res96 <- all1_(2)
  expect_type(res96, "logical")
  expect_equal(length(res96), 4)

  res97 <- any1_(2)
  expect_type(res97, "logical")
  expect_equal(length(res97), 4)

  res98 <- approx_equal1_(2)
  expect_type(res98, "logical")
  expect_equal(length(res98), 1)

  res99 <- arg1_(2)
  expect_type(res99, "double")
  expect_equal(dim(res99), c(2, 2))

  res100 <- as_scalar1_(2)
  expect_type(res100, "double")
  expect_equal(length(res100), 1)

  res101 <- clamp2_(2)
  expect_type(res101, "double")
  expect_equal(dim(res101), c(2, 2))

  res102 <- cond1_(2)
  expect_type(res102, "double")
  expect_equal(length(res102), 1)

  res103 <- conj1_(2)
  expect_type(res103, "list")
  expect_type(res103[[1]], "double")
  expect_equal(dim(res103[[1]]), c(2, 2))

  res104 <- conv_to1_(2)
  expect_type(res104, "double")
  expect_equal(length(res104), 4)

  res105 <- cross1_(3)
  expect_type(res105, "double")
  expect_equal(length(res105), 3)

  res106 <- cumsum1_(2)
  expect_type(res106, "double")
  expect_equal(length(res106), 3)

  res107 <- cumprod1_(2)
  expect_type(res107, "double")
  expect_equal(length(res107), 3)

  res108 <- det1_(2)
  expect_type(res108, "double")
  expect_equal(length(res108), 3)

  res109 <- diagmat1_(2)
  expect_type(res109, "double")
  expect_equal(dim(res109), c(2, 2))

  res110 <- diagvec1_(3)
  expect_type(res110, "double")
  expect_equal(length(res110), 2)

  res111 <- diags1_(2)
  expect_type(res111, "double")
  expect_equal(dim(res111), c(2, 2))

  res112 <- spdiags1_(2)
  expect_type(res112, "double")
  expect_equal(dim(res112), c(2, 2))

  res113 <- diff1_(3)
  expect_type(res113, "double")
  expect_equal(dim(res113), c(3, 2))

  res114 <- dot1_(2)
  expect_type(res114, "double")
  expect_equal(length(res114), 3)

  res115 <- eps1_(2)
  expect_type(res115, "double")
  expect_equal(dim(res115), c(2, 2))

  res116 <- expmat1_(2)
  expect_type(res116, "double")
  expect_equal(dim(res116), c(2, 2))

  res117 <- expmat_sym1_(2)
  expect_type(res117, "double")
  expect_equal(dim(res117), c(2, 2))

  res118 <- find1_(2)
  expect_type(res118, "list")

  res119 <- find_finite1_(2)
  expect_type(res119, "integer")
  expect_equal(length(res119), 4)

  res120 <- find_nonfinite1_(2)
  expect_type(res120, "integer")

  res121 <- find_nan1_(2)
  expect_type(res121, "integer")

  res122 <- find_unique1_(2)
  expect_type(res122, "integer")

  res123 <- flip1_(2)
  expect_type(res123, "list")
  expect_type(res123[[1]], "double")

  res124 <- imag1_(2)
  expect_type(res124, "list")
  expect_type(res124[[1]], "double")

  res125 <- ind2sub1_(2)
  expect_type(res125, "list")

  res126 <- index_min1_(2)
  expect_type(res126, "double")
  expect_equal(length(res126), 2)

  res127 <- inplace_trans1_(2)
  expect_type(res127, "double")
  expect_equal(dim(res127), c(2, 2))

  res128 <- inplace_strans1_(2)
  expect_type(res128, "list")
  expect_equal(length(res128), 2)

  res129 <- intersect1_(5)
  expect_type(res129, "integer")
  expect_equal(res129, 2:5)

  res130 <- join_rows1_(2)
  expect_type(res130, "list")
  expect_equal(length(res130), 5)

  res131 <- join_cubes1_(2)
  expect_type(res131, "list")
  expect_equal(length(res131), 7)

  res132 <- kron1_(2)
  expect_type(res132, "double")
  expect_equal(dim(res132), c(6, 6))

  res133 <- log_det1_(2)
  expect_type(res133, "list")
  expect_equal(length(res133), 2)

  res134 <- log_det_sympd1_(2)
  expect_type(res134, "list")
  expect_equal(length(res134), 2)

  res135 <- logmat1_(2)
  expect_type(res135, "list")
  expect_equal(length(res135), 2)

  res136 <- logmat_sympd1_(2)
  expect_type(res136, "list")
  expect_equal(length(res136), 2)

  res137 <- max1_(2)
  expect_type(res137, "list")
  expect_equal(length(res137), 4)

  res138 <- nonzeros1_(2)
  expect_type(res138, "double")

  res139 <- norm1_(2)
  expect_type(res139, "double")
  expect_equal(length(res139), 5)

  res140 <- norm2est1_(2)
  expect_type(res140, "double")
  expect_equal(length(res140), 1)

  res141 <- normalise1_(2)
  expect_type(res141, "list")
  expect_equal(length(res141), 2)

  res142 <- pow1_(2)
  expect_type(res142, "list")
  expect_equal(length(res142), 2)

  res143 <- powmat1_(2)
  expect_type(res143, "list")
  expect_equal(length(res143), 2)

  res144 <- prod1_(2)
  expect_type(res144, "list")
  expect_equal(length(res144), 2)

  res145 <- rank1_(2)
  expect_type(res145, "list")
  expect_equal(length(res145), 2)

  res146 <- rcond1_(2)
  expect_type(res146, "double")
  expect_equal(length(res146), 1)

  res147 <- repelem1_(2)
  expect_type(res147, "list")
  expect_equal(length(res147), 2)

  res148 <- repmat1_(2)
  expect_type(res148, "list")
  expect_equal(length(res148), 2)

  res149 <- reshape2_(2)
  expect_type(res149, "list")
  expect_equal(length(res149), 3)

  res150 <- resize2_(2)
  expect_type(res150, "list")
  expect_equal(length(res150), 3)

  res151 <- reverse1_(2)
  expect_type(res151, "list")
  expect_equal(length(res151), 3)

  res152 <- roots1_(2)
  expect_type(res152, "list")
  expect_equal(length(res152), 2)

  res153 <- shift1_(2)
  expect_type(res153, "list")
  expect_equal(length(res153), 3)

  res154 <- shuffle1_(2)
  expect_type(res154, "list")
  expect_equal(length(res154), 2)

  res155 <- size1_(2)
  expect_type(res155, "list")
  expect_equal(length(res155), 7)

  res156 <- sort1_(2)
  expect_type(res156, "list")
  expect_equal(length(res156), 5)

  res157 <- sort_index1_(2)
  expect_type(res157, "list")
  expect_equal(length(res157), 3)

  res158 <- sqrtmat1_(2)
  expect_type(res158, "list")
  expect_equal(length(res158), 4)

  res159 <- sqrtmat_sympd1_(2)
  expect_type(res159, "double")
  expect_equal(dim(res159), c(2, 2))

  res160 <- sum2_(2)
  expect_type(res160, "list")
  expect_equal(length(res160), 3)

  res161 <- sub2ind1_(2)
  expect_type(res161, "integer")
  expect_equal(length(res161), 1)

  res162 <- trace1_(2)
  expect_type(res162, "double")
  expect_equal(length(res162), 1)

  res163 <- trans1_(2)
  expect_type(res163, "list")
  expect_equal(length(res163), 2)

  res164 <- trapz1_(2)
  expect_type(res164, "double")
  expect_equal(length(res164), 1)

  set.seed(123)
  X <- matrix(rnorm(4), nrow = 2, ncol = 2)
  Y <- matrix(rnorm(4), nrow = 2, ncol = 2)

  res165 <- mean1_(X, Y)
  res166 <- median1_(X, Y)
  res167 <- stddev1_(X, Y)
  res168 <- var1_(X, Y)
  res169 <- range1_(X, Y)
  res170 <- cov1_(X, Y)
  res171 <- cor1_(X, Y)

  expect_type(res165, "list")
  expect_equal(length(res165), 3)

  expect_type(res166, "list")
  expect_equal(length(res166), 3)
  expect_equal(res165, res166)

  expect_type(res167, "list")
  expect_equal(length(res167), 3)

  expect_type(res168, "list")
  expect_equal(length(res168), 3)

  expect_type(res169, "list")
  expect_equal(length(res169), 2)

  expect_type(res170, "list")
  expect_equal(length(res170), 2)

  expect_type(res171, "list")
  expect_equal(length(res171), 2)

  res172 <- normpdf1_(5)
  expect_type(res172, "list")
  expect_equal(length(res172), 5)

  res173 <- lognormpdf1_(5)
  expect_type(res173, "list")
  expect_equal(length(res173), 5)

  res174 <- normcdf1_(5)
  expect_type(res174, "list")
  expect_equal(length(res174), 5)

  res175 <- mvnrnd1_(3, 5)
  expect_type(res175, "double")
  expect_equal(dim(res175), c(3, 5))

  res176 <- chi2rnd1_(3, 5)
  expect_type(res176, "list")
  expect_equal(length(res176), 2)
  expect_equal(dim(res176[[1]]), c(3, 5))

  res177 <- wishrnd1_(3)
  expect_type(res177, "double")
  expect_equal(dim(res177), c(3, 3))

  res178 <- iwishrnd1_(3, 4)
  expect_type(res178, "double")
  expect_equal(dim(res178), c(3, 3))

  res179 <- kmeans1_(4, 3)
  expect_type(res179, "list")
  # expect_equal(res179[[1]], TRUE)
  # expect_type(res179[[2]], "double")
  # expect_equal(dim(res179[[2]]), c(3, 2))
  # TODO: add RNG later

  set.seed(321)
  x <- rnorm(10, 0, 1)
  y <- rnorm(10, 2, 3)
  res180 <- conv1_(x, y)
  expect_type(res180, "list")
  expect_equal(length(res180[[1]]), length(x) + length(y) - 1)
  expect_equal(length(res180[[2]]), length(x))

  set.seed(213)
  x <- matrix(rnorm(100, 0, 1), 10, 10)
  y <- matrix(rnorm(100, 2, 3), 10, 10)
  res181 <- conv2_(x, y)
  expect_type(res181, "list")
  expect_equal(nrow(res181[[1]]), nrow(x) + nrow(y) - 1)
  expect_equal(nrow(res181[[2]]), nrow(x))

  set.seed(123)
  x <- rnorm(10)
  res182 <- fft1_(x)
  expect_type(res182, "list")
  expect_equal(length(res182), 2)
  expect_equal(length(res182[[1]][[1]]), 10)
  expect_equal(res182[[2]][[1]], x)

  set.seed(321)
  x <- matrix(rnorm(20), 10, 2)
  res183 <- fft2_(x)
  expect_type(res183, "list")
  expect_equal(length(res183), 2)
  expect_equal(dim(res183[[1]][[1]]), c(10, 2))
  expect_equal(res183[[2]][[1]], x)

  res184 <- interp1_(5)
  expect_type(res184, "double")
  expect_equal(length(res184), 10)

  n <- 10
  res185 <- interp2_(n)
  expect_type(res185, "double")
  expect_equal(nrow(res185), 2 * n + (n - 2))
  expect_equal(ncol(res185), 2 * n - 1)

  res186 <- polyfit1_(10, 2)
  expect_type(res186, "double")
  expect_equal(res186, c(2, 2, 1))

  res187 <- polyval1_(10, 2)
  expect_type(res187, "double")

  set.seed(123)
  X <- matrix(rnorm(25), 5, 5)

  set.seed(321)
  Y <- matrix(rnorm(25), 5, 5)

  res188 <- chol1_(X, "upper", "matrix")
  
  set.seed(123)
  res189 <- eig_sym1_(matrix(rpois(25, 2), 5, 5) + 0.05, "std")

  res190 <- eig_gen1_(X, "nobalance")
  res191 <- eig_pair1_(X, Y)
  res192 <- hess1_(X)
  res193 <- inv1_(X)

  set.seed(123)
  res194 <- inv_sympd1_(matrix(rpois(25, 2), 5, 5) + 0.05)
  
  res195 <- lu1_(X)

  expect_type(res188, "list")
  expect_type(res189, "list")
  expect_type(res190, "list")
  expect_type(res191, "list")
  expect_type(res192, "list")
  expect_type(res193, "list")
  expect_type(res194, "list")
  expect_type(res195, "list")

  set.seed(321)
  Z <- matrix(rnorm(30), 5, 6)
  res196 <- null1_(Z)
  expect_type(res196, "list")

  res197 <- orth1_(Z)
  expect_type(res197, "list")

  res198 <- pinv1_(Z)
  expect_type(res198, "list")

  res199 <- qr1_(X)
  res200 <- qr_econ1_(X)
  expect_type(res199, "list")
  expect_type(res200, "list")
  q1 <- res199[[2]]
  r1 <- res199[[3]]
  q2 <- res200[[2]]
  r2 <- res200[[3]]
  expect_equal(q1 %*% r1, X)
  expect_equal(q2 %*% r2, X)

  set.seed(123)
  X <- matrix(rnorm(25), 5, 5)
  Y <- matrix(rnorm(25), 5, 5)

  res201 <- qz1_(X, Y, "none")
  expect_type(res201, "list")

  res202 <- schur1_(X)
  expect_type(res202, "list")

  res203 <- solve1_(X, Y)
  expect_type(res203, "double")

  res204 <- svd1_(X)
  U <- res204[[2]]
  S <- diag(res204[[3]])
  V <- res204[[4]]
  expect_type(res204, "list")
  expect_equal(U %*% S %*% t(V), X)

  res205 <- svd_econ1_(X)
  U <- res205[[1]]
  S <- diag(res205[[2]])
  V <- res205[[3]]
  expect_type(res205, "list")
  expect_equal(U %*% S %*% t(V), X)

  set.seed(123)
  A <- matrix(rnorm(25), 5, 5)
  B <- matrix(rnorm(25), 5, 5)
  C <- matrix(rnorm(25), 5, 5)
  res206 <- syl1_(A,B,C)
  expect_type(res206, "double")

  res207 <- eig_sym2_(A, "lm", 3)
  expect_type(res207, "list")

  res208 <- eig_gen2_(A, "lm", 2)
  expect_type(res208, "list")

  res209 <- svds1_(A, 2)
  expect_type(res209, "list")

  set.seed(123)
  b <- rnorm(5)
  res210 <- spsolve1_(A, b, "lapack")
})
