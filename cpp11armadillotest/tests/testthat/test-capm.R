test_that("CAPM Model", {
  set.seed(200100)
  f <- 0.02
  m <- matrix(rnorm(3, 0, 0.1), nrow = 3, ncol = 1)
  r <- matrix(rnorm(6, 0, 0.1), nrow = 3, ncol = 2)

  beta <- cov(r, m) / as.double(var(m))
  m_avg <- mean(m)

  capm_r <- f + beta * (m_avg - f)
  capm_cpp <- capm(r, m, f)

  expect_equal(capm_r, capm_cpp)
})
