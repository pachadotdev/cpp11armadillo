test_that("sparse matrices copy works", {
  if (!requireNamespace("Matrix", quietly = TRUE)) {
    skip("Matrix package is not available")
  }

  M <- Matrix::Matrix(c(0, 0, 0, 2, 6, 0, -1, 5, 0, 4, 3, 0, 0, 0, 5, 0),
    nrow = 4, ncol = 4, sparse = TRUE
  )

  N <- test_dgCMatrix_to_SpMat(M)

  expect_equal(N, M)
})
