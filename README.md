
<!-- README.md is generated from README.Rmd. Please edit that file -->

# cpp11armadillo

<!-- badges: start -->

<!-- badges: end -->

The goal of cpp11armadillo is to provide a novel approach to use the
Armadillo C++ library by using the header-only cpp11 R package and to
simplify things for the end-user.

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
cpp11::pkg_template()
```

Then follow the instructions from the README.

On the C++ side, you have to be very explicit, here is an example from
the package template:

``` cpp
#include <armadillo.hpp>
#include <cpp11.hpp>
#include <cpp11armadillo.hpp>

using namespace arma;
using namespace cpp11;
using namespace std;

[[cpp11::register]] doubles_matrix<> ols_(const doubles_matrix<>& y,
                                          const doubles_matrix<>& x) {
  Mat<double> Y = doubles_matrix_to_Mat_(y);
  Mat<double> X = doubles_matrix_to_Mat_(x);

  Mat<double> XtX = X.t() * X;
  Mat<double> XtX_inv = inv(XtX);
  Mat<double> beta = XtX_inv * X.t() * Y;

  return Mat_to_doubles_matrix_(beta);
}
```

This code:

1.  Includes the Armadillo, cpp11 and cpp11armadillo libraries and
    allows interfacing C++ with R (i.e., the `#include <XYZ.hpp>`
    lines).
2.  Loads the corresponding namespaces (i.e., the `using namespace XYZ`
    lines) in order to simplify the notation (i.e., using `Mat` instead
    of `arma::Mat`).
3.  Declares a function `ols_()` that takes inputs from R, does the
    computation on C++ side, and it can be called from R scripts. The
    use of `const` and `&` are specific to the C++ language and allow to
    pass data from R to C++ while avoiding copying the data, therefore
    saving time and memory.
4.  `doubles_matrix_to_Mat_()` is “diplomat” function that puts R and C+
    data types in conversation and facilitates communications between
    those two. This function is provided by `cpp11armadillo`.
5.  `XtX = X.t() * X` calculates the product of the transpose of `X` and
    `X`.
6.  `inv(XtX)` calculates the inverse of `XtX`.
7.  `XtX_inv * X.t() * Y` calculates the OLS estimator.
8.  `Mat_to_doubles_matrix_()` is another “diplomat” function that takes
    `beta`, expressed as a C++ data structure, and converts it to a data
    structure that R understands.

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
