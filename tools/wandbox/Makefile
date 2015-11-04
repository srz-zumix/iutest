#
# Makefile

.PHONY: sample

TOOLS=wandbox.py iuwandbox.py

WANDBOX_COMPILER?=gcc-head

help: $(TOOLS)
	python iuwandbox.py -h
	
fused:
	make -C ../fused

sample: sample.cpp $(TOOLS) Makefile
	python iuwandbox.py sample.cpp -f"-Dx=hogefuga\n-O3" --check_config

save: sample.cpp $(TOOLS) Makefile
	python iuwandbox.py sample.cpp -s -x "warning" -f"-Dx=hogefuga\n-O3" -r"--iutest_color=no" --expand_include

local:
	g++ sample.cpp -o sample
	./sample
	
test: ../../test/syntax_tests.cpp Makefile
	python iuwandbox.py $< -c $(WANDBOX_COMPILER) -f"-DIUTEST_USE_MAIN" --expand_include --encoding utf-8-sig

test-gcc: ../../test/syntax_tests.cpp Makefile
	python iuwandbox.py $< -c gcc-head -f"-DIUTEST_USE_MAIN" -x "warning,gnu++1y" -f"-Wsuggest-override" --expand_include --encoding utf-8-sig

test-clang: ../../test/syntax_tests.cpp Makefile
	python iuwandbox.py $< -c clang-head -f"-DIUTEST_USE_MAIN" -x "warning,gnu++1y" --expand_include --encoding utf-8-sig

test-gcc-98: ../../test/syntax_tests.cpp Makefile
	python iuwandbox.py $< -c gcc-head -f"-DIUTEST_USE_MAIN" -x "warning,c++98" --expand_include --encoding utf-8-sig

list-compiler:
	python iuwandbox.py --list_compiler

list-options:
	python iuwandbox.py --list_options $(WANDBOX_COMPILER)

COMPILE_ERROR_TESTS=\
	iutest_check_strict_tests \
	iutest_static_assertion_failure_tests \

COMPILE_ERROR_TESTS_SRC=$(COMPILE_ERROR_TESTS:%=../../test/%.cpp)


$(COMPILE_ERROR_TESTS) : $(COMPILE_ERROR_TESTS_SRC) Makefile
#	-python iuwandbox.py ../../test/$@.cpp -c clang-head -x "warning,gnu++1y" --expand_include --encoding utf-8-sig
	python iuwandbox.py ../../test/$@.cpp -c clang-head -x "warning,gnu++1y" --expand_include --encoding utf-8-sig | python ../python/iutest_compile_error_test.py -c clang
#	python iuwandbox.py ../../test/$@.cpp -c gcc-head -x "warning,gnu++1y" --expand_include --encoding utf-8-sig | python ../python/iutest_compile_error_test.py -c gcc

compile-error: $(COMPILE_ERROR_TESTS) Makefile
