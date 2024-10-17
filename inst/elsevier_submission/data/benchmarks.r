library(dplyr)
library(bench)

# source("balassa-data.r")
X <- readRDS("balassa-index.rds")

source("balassa.r")
library(balassacpp11armadillo)
library(balassarcpparmadillo)

base_r <- function(Y) {
  for (i in seq_along(Y)) {
    balassa_r(Y[[i]])
  }
  return(TRUE)
}

balassa_cpp11 <- function(Y) {
  for (i in seq_along(Y)) {
    balassa_cpp11armadillo(Y[[i]])
  }
  return(TRUE)
}

balassa_rcpp <- function(Y) {
  for (i in seq_along(Y)) {
    balassa_rcpparmadillo(Y[[i]])
  }
  return(TRUE)
}

speed <- mark(
  base_r(X),
  balassa_cpp11(X),
  balassa_rcpp(X),
  iterations = 100L
)

install_cpp11armadillo <- function() {
  setwd("~/github/cpp11armadillo/inst/rjournal_submission/balassacpp11armadillo/")
  devtools::clean_dll()
  devtools::install(quiet = T, upgrade = "never")
  return(TRUE)
}

install_rcpparmadillo <- function() {
  setwd("~/github/cpp11armadillo/inst/rjournal_submission/balassarcpparmadillo/")
  devtools::clean_dll()
  devtools::install(quiet = T, upgrade = "never")
  return(TRUE)
}

setup <- mark(
  install_cpp11armadillo(),
  install_rcpparmadillo(),
  iterations = 1L
)

setwd("~/github/cpp11armadillo/inst/rjournal_submission/")

saveRDS(speed, "data/benchmark-speed.rds")
saveRDS(setup, "data/benchmark-setup.rds")
