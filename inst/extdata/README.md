# How to use cpp11armadillo?

## Read the documentation

The basic examples should be enough to get you started. If you need more
information, you can read the rest of the documentation, which is quite
comprehensive.

1. [Basic examples[(https://pacha.dev/cpp11armadillo/articles/basic-usage.html)
2. [Member functions and variables](https://pacha.dev/cpp11armadillo/articles/member-functions-and-variables.html)
3. [Matrix, vector, cube and field classes](https://pacha.dev/cpp11armadillo/articles/matrix-vector-cube-and-field-classes.html)
4. [Generated vectors, matrices, and cubes](https://pacha.dev/cpp11armadillo/articles/generated-vectors-matrices-cubes.html)
5. [Functions of vectors, matrices, and cubes](https://pacha.dev/cpp11armadillo/articles/functions-of-vector-matrices-cubes.html)
6. [Porting R codes from Hansen's Econometrics to C++](https://pacha.dev/hansen/)
7. [Fitting regressions with Armadillo](https://pacha.dev/cpp11armadillo/articles/linear-model.html)

## Test the package

1. Open `./dev/01_load_or_install.R` and run it.
2. Open `./src/01_ols.cpp`, inspect the OLS functions.
3. Create your own functions in `./02_your_functions.cpp`.
4. Run `devtools::load_all()` before testing your functions, and then add tests
   to `./dev/02_test.R` and run it.
5. Run `./dev/03_readme_and_license.R` to add a README and license.
6. Run `devtools::install()` in `./dev/01_load_or_install.R` to install the
   package locally when you are ready.
7. The package template includes a configuration with a predefined number of
   cores to use. You can change this value by doing this:

   Unix: Edit `./src/Makevars.in` to set `DARMA_OPENMP_THREADS` to another
         value or edit `./configure` to change `PKG_NCORES` to another value.
   
   Windows: Edit `./src/Makevars.win` to set `DARMA_OPENMP_THREADS` to another
            value.
