# Contributing to cpp11eigen

This outlines how to propose a change to cpp11eigen. For more detailed info about contributing to this, please see the [**development contributing guide**](https://rstd.io/tidy-contrib). 

## Fixing typos

You can fix typos, spelling mistakes, or grammatical errors in the documentation directly using the GitHub web interface, as long as the changes are made in the _source_ file. 
This generally means you'll need to edit  [roxygen2 comments](https://roxygen2.r-lib.org/articles/roxygen2.html) in an `.R`, not a `.Rd` file. 
You can find the `.R` file that generates the `.Rd` by reading the comment in the first line.

## Bigger changes

If you want to make a bigger change, it's a good idea to first file an issue and make sure the maintainer agrees that it’s needed. 
If you’ve found a bug, please file an issue that illustrates the bug with a minimal  [reprex](https://www.tidyverse.org/help/#reprex) (this will also help you write a unit test, if needed).

### Pull request process

*   Fork the repository and clone onto your computer. If you haven't done this before, use `usethis::create_from_github("pachadotdev/cpp11eigen", fork = TRUE)`.

*   Install all development dependences with `devtools::install_dev_deps()`, and then make sure the package passes R CMD check by running `devtools::check()`. Even better, use `make check` from the command line to run the checks in a clean environment. If `R CMD check` doesn't pass cleanly, it's a good idea to ask for help before continuing. What I do to be extra sure is to run `make clean && make install && make test` to discard that I don't have outdated binaries.
*   Create a Git branch for your pull request (PR). Use `usethis::pr_init("brief-description-of-change")`.

*   Make your changes, commit to git, and then create a PR by running `usethis::pr_push()`, and following the prompts in your browser. The title of your PR should briefly describe the change. The body of your PR should contain `Fixes #issue-number`.

*   Add a description of the changes at the top of `NEWS.md` (i.e. just below the first header). Follow the style described in <https://style.tidyverse.org/news.html>.

### Code style

*   New code should follow the tidyverse [style guide](https://style.tidyverse.org). You can use the [styler](https://CRAN.R-project.org/package=styler) package to apply these styles, but please don't restyle code that has nothing to do with your PR. If you edit C++ code, please run `make format` to apply the clang format style or the CI will fail.

*   Use [roxygen2](https://cran.r-project.org/package=roxygen2), with [Markdown syntax](https://cran.r-project.org/web/packages/roxygen2/vignettes/rd-formatting.html), for documentation.

*  Use [testthat](https://cran.r-project.org/package=testthat) for unit tests. Contributions with test cases included are easier to understand and accept.

## Code of Conduct

Please note that the cpp11eigen project is released with a [Contributor Code of Conduct](CODE_OF_CONDUCT.md). By contributing to this project you agree to abide by its terms.
