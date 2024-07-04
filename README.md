
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

You can install the development version of cpp11armadillo like so:

``` r
remotes::install_github("pachadotdev/cpp11armadillo")
```

## Examples

I have provided a package template for RStudio that also works with VS
Code.

The idea of this package is to be naive and simple (like me).

From RStudio/VSCode create a new project and run:

``` r
cpp11armadillo::pkg_template()
```

Then follow the instructions from the README.

The vignettes contains detailed examples that I use to test
`cpp11armadillo`, these include Ordinary Least Squares, Leontief
inverse, eigenvalues, and the Capital Asset Pricing Model (CAPM).
