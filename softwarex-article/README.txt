# How to build the manuscript

1. Put the extracted data and qmd file in the same directory.
2. Install the "PLOS ONE" extension with `quarto add quarto-journals/plos`
3. Render the QMD file with `quarto render cpp11armadillo.qmd --to plos-pdf`,
   this will create a PDF and a TEX file besides a directory for the plots.
   