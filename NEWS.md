# cpp11armadillo 0.4.4

* Provides wrappers to avoid CRAN notes with Armadillo functions that use
  `std::cout` (#05a342b).
* Allows to convert `uword` to `integers`.

# cpp11armadillo 0.4.3

* Expanded documentation.
* Added a new vignettes:
  * Functions of vectors, matrices, and cubes.
  * Statistics and clustering.
  * Syntax comparison for MATLAB/Octave users.
* New package template.
* Provides `as_mat()` and `as_col()` as wrappers for `as_Mat()` and `as_Col()`.

# cpp11armadillo 0.4.2

* Expands the package internals to convert `umat` to `integers_matrix<>`.
* Expands the package internals to convert `ivec` to `integers`.

# cpp11armadillo 0.4.1

* Modified configure file to fix Fedora errors.
* Includes parts of the official Armadillo documentation in the vignettes but
  adapted to working with R.
* Thanks a lot to @barracuda156 and @bastistician for reporting the issue.

# cpp11armadillo 0.4.0

* Uses Armadillo 14.2.2 for C++15 compatibility.
* Adds a configure file to check the compatibility between the C++ compiler and
  Armadillo.

# cpp11armadillo 0.3.5

* The example package now includes a configure file to set the number of cores
  when compiling the package.
* The package template includes instructions to alter the default number of
  cores (50% of the available cores).

# cpp11armadillo 0.3.4

* Uses `std::copy` and `std::memcpy` to convert between R and C++.

# cpp11armadillo 0.3.3

* Rewritten vignettes.

# cpp11armadillo 0.3.2

* Includes `armadillo.hpp` only once in the headers.
* Improved package template.

# cpp11armadillo 0.3.1

* Adds Jonathan as a contributor.
* Includes the working paper for arXiv.
* Avoids duplicating `mtcars_mat` for the tests.

# cpp11armadillo 0.3.0

* Uses Armadillo version "Stochastic Parrot 14.0.2".

# cpp11armadillo 0.2.9

* Uses Armadillo version Cortisol Retox 12.6.7.
* Removes leontief dependency to test the functions.
* Adds minimal documentation to use OpenBLAS with R and Armadillo.
* New examples, which are clearer and more informative.
* New `Makevars` template with commented debbuging flags and that allows to set the number of cores.
* Adds `armadillo_version()` to get the version of Armadillo from R.

# cpp11armadillo 0.2.8

* Provides templates to convert to and from sparse matrices.
* Removes `using namespace std;` from headers (see https://www.reddit.com/r/cpp_questions/comments/160eivk/is_using_namespace_std_really_considered_bad/).

# cpp11armadillo 0.2.7

* Provides wrappers for `arma::uvec` used to subset vectors.
* Minimal optimizations in R to/from C++ templates.

# cpp11armadillo 0.2.6

* Fewer implicit conversions.
* Using balanced parallelization in OpenMP.

# cpp11armadillo 0.2.5

* Uses messages that do not generate warnings in the R API (#379d8d6).
* Skips OpenMP on Mac hardware (#13e805b).
* Provides a template to convert vectors to column matrices (#6138a35),
* First version on CRAN.

# cpp11armadillo 0.2.0

* Uses OpenMP.
* Sticks to Clang format.

# cpp11armadillo 0.1.2

* Improves vendoring (i.e., does the same as `cpp11`)

# cpp11armadillo 0.1.1

* Includes more formal tests in the `cpp11armadillotest` directory.
* Provides a conversion from complex vector/matrix to a list of double
  vectors/matrices.

# cpp11armadillo 0.1

* First public version. Elemental vector/matrix conversion from/to R and C++.
