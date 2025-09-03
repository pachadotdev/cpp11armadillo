test_that("implicit conversions work", {
  M <- matrix(1:4, nrow = 4, ncol = 4)
  # storage.mode(M)

  M2 <- M
  storage.mode(M2) <- "double"

  expect_equal(M2, implicit_conversion_double(M2))
  expect_equal(M2, implicit_conversion_float(M2))
  expect_equal(M, implicit_conversion_int(M))
  expect_equal(M, implicit_conversion_uint(M))
  expect_equal(M, implicit_conversion_double(M))
})
