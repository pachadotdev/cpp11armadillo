test_that("examples derived from official documentation", {
  x <- model.matrix(mpg ~ wt, data = mtcars)
  y <- model.response(model.frame(mpg ~ wt, data = mtcars))
  betas <- ols_(x, y)
  expect_equal(betas, unname(coef(lm(mpg ~ wt, data = mtcars))))

  betas2 <- poisson_(x, y)

  betas3 <- suppressWarnings(
    glm(mpg ~ wt, data = mtcars, family = poisson)$coefficients)

  expect_equal(betas2, unname(betas3))
})
