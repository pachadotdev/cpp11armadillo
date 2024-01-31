test_that("pkg-template", {
  dir <- tempdir()
  if (!dir.exists(dir)) {
    dir.create(dir)
  }
  expect_true(pkg_template("testname", dir))
})
