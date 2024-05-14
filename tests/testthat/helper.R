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
