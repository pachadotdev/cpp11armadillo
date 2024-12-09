test_that("elemental tests for quasi-random values", {
  set.seed(1234); m1 <- random_matrix_nxn(5)
  set.seed(1234); m2 <- random_matrix_nxn(5)
  set.seed(4321); m3 <- random_matrix_nxn(5)
  set.seed(4321); m4 <- random_matrix_nxn(5)

  expect_equal(m1, m2)
  expect_equal(m3, m4)
})
