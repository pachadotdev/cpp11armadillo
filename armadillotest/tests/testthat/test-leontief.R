test_that("Input-Output Model", {
  X <- leontief::transaction_matrix
  d <- leontief::wage_demand_matrix[, "final_total_demand"]

  L <- leontief_inverse(X, d)

  expect_equal(L, leontief::leontief_inverse(leontief::input_requirement(X, d)))
})
