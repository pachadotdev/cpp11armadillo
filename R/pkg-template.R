# The function itself just echos its inputs and outputs to a file called INDEX,
# which is then opened by RStudio when the new project is opened.
#' Start a new project with the cpp11armadillo package template
#' @param pkgname Name of the new package (defaults to the name of the current
#'  working directory)
#' @param path Path to the new project (defaults to working directory)
#' @export
pkg_template <- function(pkgname = NULL, path = NULL) {
  # get current working directory
  cwd <- getwd()
  if (is.null(path)) {
    path <- cwd
  }
  if (is.null(pkgname)) {
    pkgname <- basename(path)
  }

  # ensure path exists
  dir.create(path, recursive = TRUE, showWarnings = FALSE)

  # copy files
  file.copy(
    list.files(
      system.file("extdata", "", package = "cpp11armadillo"),
      full.names = TRUE
    ),
    path,
    recursive = TRUE
  )

  lines <- c(
    "^.*\\.Rproj$",
    "^\\.Rproj\\.user$",
    "^\\.Renviron$",
    "^docs$",
    "^vignettes/images$",
    "^\\.github$",
    "^\\.vscode$",
    "^dev$",
    "^LICENSE\\.md$",
    "^README$",
    "^README\\.Rmd$"
  )

  writeLines(lines, con = ".Rbuildignore")

  lines <- c(
    paste0("#' @useDynLib ", pkgname, ", .registration = TRUE"),
    "#' @keywords internal",
    "\"_PACKAGE\""
  )

  writeLines(lines, con = paste0("R/", pkgname, "-package.R"))

  lines <- c(
    paste("Package:", pkgname),
    "Type: Package",
    "Title: ADD TITLE",
    "Version: 0.1",
    "Authors@R: c(",
    "    person(",
    "        given = \"YOUR\",",
    "        family = \"NAME\",",
    "        role = c(\"aut\", \"cre\"),",
    "        email = \"YOUR@EMAIL.COM\",",
    "        comment = c(ORCID = \"0000-0001-0002-0003\"))",
    "    )",
    "Suggests: ",
    "    knitr,",
    "    rmarkdown",
    "Depends: R(>= 3.5.0)",
    "Description: ADD DESCRIPTION. TWO OR MORE LINES",
    "License: MIT + file LICENSE",
    "BugReports: https://github.com/USERNAME/PKGNAME/issues",
    "URL: https://WEBSITE.COM",
    "RoxygenNote: 7.3.0",
    "Encoding: UTF-8",
    "NeedsCompilation: yes",
    "VignetteBuilder: knitr",
    "LinkingTo: cpp11, cpp11armadillo"
  )

  writeLines(lines, con = "DESCRIPTION")

  return(invisible())
}
