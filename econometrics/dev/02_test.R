# Estimate the model y ~ constant + x
# with y and x gaussian random variables

set.seed(123)
y <- matrix(rnorm(100), ncol = 1, nrow = 100)
x <- matrix(1, ncol = 1, nrow = 100)
x <- cbind(x, rnorm(100, 0, 1))

# Armadillo computation
ols_mat(y, x)
ols_dbl(y, x)

# Base R computation
solve(t(x) %*% x) %*% t(x) %*% y
lm(y ~ x + 0)

# Test your own functions now
