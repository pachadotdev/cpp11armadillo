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

clang_format=`which clang-format-14`
format: $(shell find . -name '*.hpp') $(shell find . -name '*.h') $(shell find . -name '*.cpp')
	@${clang_format} -i $?
