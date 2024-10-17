balassa_r <- function(X) {
  B <- t(t(X / rowSums(X)) / (colSums(X) / sum(X)))
  B[B < 1] <- 0
  B[B >= 1] <- 1
  dimnames(B) <- NULL
  B
}
