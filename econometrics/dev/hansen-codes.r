url <- "https://www.ssc.wisc.edu/~bhansen/econometrics/Econometrics%20Programs.zip"
zipout <- "dev/econometricsprograms.zip"

if (!file.exists(zipout)) {
  download.file(url, zipout)
}

dout <- "dev/hansen-codes"

if (!dir.exists(dout)) {
  unzip(zipout, exdir = dout)
}
