all:
	@echo "make: Entering directory 'cpp11armadillotest/src'"
	@Rscript -e 'devtools::load_all("cpp11armadillotest")'
	@echo "make: Leaving directory 'cpp11armadillotest/src'"

test: all
	@echo "make: Entering directory 'cpp11armadillotest/tests/testthat'"
	@Rscript -e 'devtools::test("cpp11armadillotest")'
	@echo "make: Leaving directory 'cpp11armadillotest/tests/testthat'"

clean:
	@Rscript -e 'devtools::clean_dll()'
	@Rscript -e 'devtools::clean_dll("cpp11armadillotest")'

document:
  @Rscript -e 'devtools::document()'

build_site:
	@Rscript -e 'pkgdown::build_site()'

install:
	@Rscript -e 'devtools::install()'
