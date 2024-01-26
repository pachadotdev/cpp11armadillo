# Copy the template ----

cpp11armadillo::pkg_template() # comment out this line after running it once

# Load the package for development ----

devtools::clean_dll()
cpp11::cpp_register()
devtools::document()

devtools::load_all()

# Test your code ----

# Armadillo computation
ols_(gapminder_am07$y, gapminder_am07$x)

# Base R computation
X <- gapminder_am07$x
y <- gapminder_am07$y
solve(t(X) %*% X) %*% t(X) %*% y

# Install the package ----

# devtools::install()
