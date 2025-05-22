library(dplyr)
library(bench)

library(Rcpp)
library(benchcpp11armadillo)
library(benchrcpparmadillo)

n <- 10000L

set.seed(123)
m <- matrix(runif(n^2), n, n)
m <- (m + t(m)) / 2

speed_eig <- mark(
  bench_eig_r(m),
  bench_eig_cpp11armadillo(m),
  bench_eig_rcpparmadillo(m),
  iterations = 100L
)

rm(m)
gc()

set.seed(123)
p <- runif(n)
q <- runif(n)
r <- runif(n)

speed_multi <- mark(
  bench_multi_r(p, q, r),
  bench_multi_cpp11armadillo(p, q, r),
  bench_multi_rcpparmadillo(p, q, r),
  iterations = 100L
)

rm(p, q, r)
gc()

install_cpp11armadillo <- function() {
  setwd("/scratch/s/shirimb/msep/cpp11armadillopaper/paper/benchcpp11armadillo/")
  devtools::clean_dll()
  devtools::install(quiet = T, upgrade = "never")
  return(TRUE)
}

install_rcpparmadillo <- function() {
  setwd("/scratch/s/shirimb/msep/cpp11armadillopaper/paper/benchrcpparmadillo/")
  devtools::clean_dll()
  devtools::install(quiet = T, upgrade = "never")
  return(TRUE)
}

setup <- mark(
  install_cpp11armadillo(),
  install_rcpparmadillo(),
  iterations = 1L
)

setwd("/scratch/s/shirimb/msep/cpp11armadillopaper/paper")

saveRDS(speed_eig, "data/benchmark-eig.rds")
saveRDS(speed_multi, "data/benchmark-multi.rds")
saveRDS(setup, "data/benchmark-setup.rds")

# x <- speed$time[[1]]
# y <- speed$time[[2]]
# z <- speed$time[[3]]

# medianspeed <- c(median(x), median(y), median(z))

# round(medianspeed / min(medianspeed), 2)
