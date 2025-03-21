
<!-- README.md is generated from README.Rmd. Please edit that file -->

# cpp11armadillo <img src="man/figures/logo.svg" align="right" height="139" alt="" />

<!-- badges: start -->

[![R-CMD-check](https://github.com/pachadotdev/cpp11armadillo/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/pachadotdev/cpp11armadillo/actions/workflows/R-CMD-check.yaml)
[![codecov](https://codecov.io/gh/pachadotdev/cpp11armadillo/graph/badge.svg?token=mWfiUCgfNu)](https://app.codecov.io/gh/pachadotdev/cpp11armadillo)
[![BuyMeACoffee](https://raw.githubusercontent.com/pachadotdev/buymeacoffee-badges/main/bmc-donate-white.svg)](https://buymeacoffee.com/pacha)
[![CRAN
status](https://www.r-pkg.org/badges/version/cpp11armadillo)](https://CRAN.R-project.org/package=cpp11armadillo)
<!-- badges: end -->

## About

The goal of cpp11armadillo is to provide a novel approach to use the
[Armadillo C++ library](https://arma.sourceforge.net/docs.html) by using
the header-only cpp11 R package and to simplify things for the end-user.
It uses the Apache 2.0 license.

⚠️Important⚠️: cpp11armadillo was created to ease writing functions in
your own packages and does not offer on-the-fly compilation for code
snippets.

The idea is to pass matrices/vectors from R to C++, write pure
C++/Armadillo code for the computation, and then export the result back
to R with the proper data structures.

[RcppArmadillo](https://cran.r-project.org/package=RcppArmadillo) is a
popular R package used by over 1200 CRAN packages as of 2024-12-13.
RcppArmadillo uses the GPL-3 license.

cpp11armadillo has different internals, even when the goal is the same,
and it aims to:

  - Enforcing copy-on-write semantics.
  - Improving the safety of using the R API from C++ code.
  - Using UTF-8 strings everywhere.
  - Applying newer C++11 features.
  - Having a more straightforward, simpler implementation.
  - Faster compilation time with lower memory requirements.
  - Growing vectors more efficiently.

The design differences result in marginally higher speed for
cpp11armadillo, and the real difference for the end user is that
cpp11armadillo:

  - Has a smaller memory footprint.
  - Uses the Apache license instead of GPL-3 (i.e., The Apache license
    is permissive and allows commercial use with attribution, unlike the
    GPL-3, which requires open-source redistribution.)
  - Can be vendored to be used in restricted environments (i.e., servers
    with no internet access or where IT restricts the installation of
    packages).

This is expanded in our article [cpp11armadillo: An R package to use the
Armadillo C++ library](https://dx.doi.org/10.1016/j.softx.2025.102087).

If this software is useful to you, please consider donating on [Buy Me A
Coffee](https://buymeacoffee.com/pacha). All donations will be used to
continue improving cpp11armadillo.

## Getting Started

Install the released version of cpp11armadillo from CRAN:

``` r
install.packages("cpp11armadillo")
```

Or, alternatively, install the development version of cpp11armadillo
from GitHub:

``` r
remotes::install_github("pachadotdev/cpp11armadillo")
```

## Who uses cpp11armadillo?

cpp11armadillo is used by the following packages:

  - [lotri](https://github.com/nlmixr2/lotri), created by Dr. Matt
    Fidler.
  - [economiccomplexity](https://github.com/pachadotdev/economiccomplexity),
    created by me.

## Examples

I have provided a package template for RStudio that also works with VS
Code.

The idea of this package is to be as simple as possible, with the least
amount of setup to get you started.

From RStudio/VSCode, go to an empty directory of your choice and run:

``` r
# subdir + package name
# subdir can be "." to create the package in the current directory
cpp11armadillo::pkg_template("pkgtemplate", "myownpackage")
```

Then follow the instructions from README.md in the path where the new
package is. The template contains a simple Ordinary Least Squares (OLS)
example that you can run to test the package.

The vignette expands on the OLS estimator, and the [hansen
package](https://pacha.dev/hansen/) expands on how to use cpp11armadillo
for Econometric models.

The
[cpp11armadillotest](https://github.com/pachadotdev/cpp11armadillo/tree/main/cpp11armadillotest)
directory contains a package that I use to test cpp11armadillo. It
includes tests for OLS, eigenvalues, matrix decompositions (Cholesky and
QR), the Capital Asset Pricing Model (CAPM), and data consistency
between R and C++. Please note that cpp11armadillotest is a dummy
package to test the C++ build with GitHub Actions, and you do not need
to install it. You can check its code to get extra examples.

## Linear Algebra Libraries

Armadillo supports OpenBLAS, Intel MKL, and the Accelerate framework
(Mac).

Install OpenBLAS on Debian-based systems with:

``` bash
sudo apt-get install libopenblas-dev
```

Restart R and run the following command to verify:

``` r
sessionInfo()
```

R should display something like:

``` r
Matrix products: default
BLAS:   /usr/lib/x86_64-linux-gnu/openblas-pthread/libblas.so.3 
LAPACK: /usr/lib/x86_64-linux-gnu/openblas-pthread/libopenblasp-r0.3.20.so; LAPACK version 3.10.0
```
