test_that("vendor", {
  dir <- tempdir()
  if (dir.exists(dir)) {
    expect_false(cpp_vendor(dir))
  } else {
    dir.create(dir)
    expect_true(cpp_vendor(dir))
  }
})
