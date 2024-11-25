
<!-- README.md is generated from README.Rmd. Please edit that file -->

# cpp11armadillo <img src="man/figures/logo.svg" align="right" height="139" alt="" />

<!-- badges: start -->

[![R-CMD-check](https://github.com/pachadotdev/cpp11armadillo/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/pachadotdev/cpp11armadillo/actions/workflows/R-CMD-check.yaml)
[![codecov](https://codecov.io/gh/pachadotdev/cpp11armadillo/graph/badge.svg?token=mWfiUCgfNu)](https://app.codecov.io/gh/pachadotdev/cpp11armadillo)
[![BuyMeACoffee](https://raw.githubusercontent.com/pachadotdev/buymeacoffee-badges/main/bmc-donate-white.svg)](https://buymeacoffee.com/pacha)
[![CRAN
status](https://www.r-pkg.org/badges/version/cpp11armadillo)](https://CRAN.R-project.org/package=cpp11armadillo)
<!-- badges: end -->

The goal of cpp11armadillo is to provide a novel approach to use the
[Armadillo C++ library](https://arma.sourceforge.net/docs.html) by using
the header-only cpp11 R package and to simplify things for the end-user.

⚠️Important⚠️: cpp11armadillo was created to ease writing functions in
your own package and it does not offer on-the-fly compilation for code
snippets.

The idea is to pass matrices/vectors from R to C++, write pure
C++/Armadillo code for the computation, and then export the result back
to R with the proper data structures.

This follows from the same goals as cpp11:

  - Enforcing copy-on-write semantics.
  - Improving the safety of using the R API from C++ code.
  - Using UTF-8 strings everywhere.
  - Applying newer C++11 features.
  - Having a more straightforward, simpler implementation.
  - Faster compilation time with lower memory requirements.
  - Growing vectors more efficiently.

If this software is useful to you, please consider donating on [Buy Me A
Coffee](https://buymeacoffee.com/pacha). All donations will be used to
continue improving `cpp11armadillo`.

## Installation

You can install the released version of cpp11armadillo from CRAN:

``` r
install.packages("cpp11armadillo")
```

You can install the development version of cpp11armadillo from GitHub:

``` r
remotes::install_github("pachadotdev/cpp11armadillo")
```

## Examples

I have provided a package template for RStudio that also works with VS
Code.

The idea of this package is to be as simple as possible, with the least
amount of setup to get you started.

From RStudio/VSCode, go to an empty directory of your choice and run:

``` r
cpp11armadillo::pkg_template(".", "packagename")
```

Then follow the instructions from the README. The template contains a
simple Ordinary Least Squares (OLS) example that you can run to test the
package.

The `cpp11armadillotest` directory contains a package that I use to test
`cpp11armadillo`. It includes tests for OLS, eigenvalues, matrix
decompositions (Cholesky and QR), the Capital Asset Pricing Model
(CAPM), and data consistency between R and C++.

The vignette expand on the OLS estimator, and the `econometrics`
directory contains additional examples for the OLS estimator and other
statistical models implemented in C++.

## Linear Algebra Libraries

Armadillo supports OpenBLAS, Intel MKL, and the Accelerate framework
(Mac).

You can install OpenBLAS on Debian-based systems with:

``` sh
sudo apt-get install libopenblas-dev
```

You can also use other commands for your specific operating system.

To verify that R is using OpenBLAS, you can run `sessionInfo()` after
restarting R to check the BLAS/LAPACK libraries in use:

``` r
Matrix products: default
BLAS:   /usr/lib/x86_64-linux-gnu/openblas-pthread/libblas.so.3 
LAPACK: /usr/lib/x86_64-linux-gnu/openblas-pthread/libopenblasp-r0.3.20.so; LAPACK version 3.10.0
```
