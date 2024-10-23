library(cpp11armadillo)

local_package <- function() {
  dir <- tempfile()
  if (!dir.exists(dir)) {
    dir.create(dir)
  }

  withr::defer(unlink(dir, recursive = TRUE), parent.frame())

  writeLines("Package: testPkg", file.path(dir, "DESCRIPTION"))
  writeLines("useDynLib(testPkg, .registration = TRUE)", file.path(dir, "NAMESPACE"))
  desc::desc(dir)
}

pkg_path <- function(pkg) {
  dirname(pkg$.__enclos_env__$private$path)
}

# pkg-template"
dir <- tempdir()
if (!dir.exists(dir)) {
  dir.create(dir)
}
expect_silent(pkg_template(dir, "testname"))

# cpp_vendor errors if cpp11 is already vendored
pkg <- local_package()
cpp_vendor(pkg_path(pkg))

expect_error(
  cpp_vendor(pkg_path(pkg)),
  "already exists"
)

# cpp_vendor vendors cpp11
pkg <- local_package()
p <- pkg_path(pkg)

cpp_vendor(pkg_path(pkg))

expect_true(dir.exists(file.path(p, "inst", "include", "cpp11")))
expect_true(file.exists(file.path(p, "inst", "include", "cpp11.hpp")))
expect_true(file.exists(file.path(p, "inst", "include", "cpp11", "declarations.hpp")))

# version name+number
expect_equal(armadillo_version(), "Stochastic Parrot 14.0.2")
