
<!-- README.md is generated from README.Rmd. Please edit that file -->

# cpp11armadillo <img src="man/figures/logo.svg" align="right" height="139" alt="" />

<!-- badges: start -->

[![R-CMD-check](https://github.com/pachadotdev/cpp11armadillo/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/pachadotdev/cpp11armadillo/actions/workflows/R-CMD-check.yaml)
<!-- badges: end -->

The goal of cpp11armadillo is to provide a novel approach to use the
[Armadillo C++ library](https://arma.sourceforge.net/docs.html) by using
the header-only cpp11 R package and to simplify things for the end-user.

The idea is that you pass your matrices/vectors to C++ and then write
pure C++/Armadillo code for your computation, and then it returns to R
with the proper data structures.

Ideally, you’ll be only focused on writing linear algebra, as the
package already solved the BLAS/LAPACK setup on your behalf.

This follows from the same goals as cpp11:

Changes that motivated cpp11 include:

  - Enforcing copy-on-write semantics.
  - Improving the safety of using the R API from C++ code.
  - Using UTF-8 strings everywhere.
  - Applying newer C++11 features.
  - Having a more straightforward, simpler implementation.
  - Faster compilation time with lower memory requirements.
  - Growing vectors more efficiently.

## Installation

You can install the development version of cpp11armadillo like so:

``` r
remotes::install_github("pachadotdev/cpp11armadillo")
```

## Minimal example

I have provided a package template for RStudio that also works with VS
Code.

The idea of this package is to be naive and simple (like me).

From RStudio/VSCode create a new project and run:

``` r
cpp11armadillo::pkg_template()
```

Then follow the instructions from the README.

Here is a commented example from the package template:

``` cpp
#include <armadillo.hpp>
#include <cpp11.hpp>
#include <cpp11armadillo.hpp>

using namespace arma;
using namespace cpp11;
using namespace std;

[[cpp11::register]] doubles_matrix<> ols_mat(const doubles_matrix<>& y,
                                             const doubles_matrix<>& x) {
  Mat<double> Y = as_Mat(y);
  Mat<double> X = as_Mat(x);

  Mat<double> XtX = X.t() * X;
  Mat<double> XtX_inv = inv(XtX);
  Mat<double> beta = XtX_inv * X.t() * Y;

  return as_doubles_matrix(beta);
}
```

This code:

1.  Includes the Armadillo, cpp11 and cpp11armadillo libraries and
    allows interfacing C++ with R (i.e., the `#include <XYZ.hpp>`
    lines).
2.  Loads the corresponding namespaces (i.e., the `using namespace XYZ`
    lines) in order to simplify the notation (i.e., using `Mat` instead
    of `arma::Mat`).
3.  Declares a function `ols_mat()` that takes inputs from R, does the
    computation on C++ side, and it can be called from R scripts. The
    use of `const` and `&` are specific to the C++ language and allow to
    pass data from R to C++ while avoiding copying the data, therefore
    saving time and memory.
4.  `as_Mat()` is a C++ template (i.e., a “diplomat” function) that puts
    R and C++ data types in conversation and facilitates communications
    between those two. The templates for doubles/integers matrices are
    provided by `cpp11armadillo`.
5.  `XtX = X.t() * X` calculates the product of the transpose of `X` and
    `X`.
6.  `inv(XtX)` calculates the inverse of `XtX`.
7.  `XtX_inv * X.t() * Y` calculates the OLS estimator.
8.  `as_doubles_matrix()` is another template that takes `beta`,
    expressed as a C++ data structure, and converts it to a data
    structure that `cpp11` and R understand.

Certainly, the goal is to use linear algebra. This is a very simple
example and you are better-off using the `lm()` function from R for this
particular case.

For other tasks, you are better-off with C++-side computation because
C++ can address:

1.  Loops that cannot be easily vectorised because subsequent iterations
    depend on previous ones.
2.  Recursive functions, or problems which involve calling functions
    thousands/ millions of times.
3.  The overhead of calling a function in C++ is much lower than in R
    (and Python).
4.  Problems that require advanced data structures and algorithms that R
    does not provide.
5.  Through the Standard Template Library (STL), C++ has efficient
    implementations of many important data structures, from ordered maps
    to double-ended queues.
