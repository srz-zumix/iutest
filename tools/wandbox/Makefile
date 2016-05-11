#
# Makefile

.PHONY: sample

TOOLS=wandbox.py iuwandbox.py

#EXPAND_INCLUDE?=--expand_include

WANDBOX_COMPILER?=gcc-head

help: $(TOOLS)
	python iuwandbox.py -h
	
fused:
	make -C ../fused

sample: sample.cpp $(TOOLS) Makefile
	python iuwandbox.py sample.cpp -f"-Dx=hogefuga\n-O3" --check_config -x "warning"

save: sample.cpp $(TOOLS) Makefile
	python iuwandbox.py sample.cpp -s -x "warning" -f"-Dx=hogefuga\n-O3" -r"--iutest_color=no" $(EXPAND_INCLUDE)

local:
	g++ sample.cpp -o sample
	./sample
	
test: ../../test/syntax_tests.cpp Makefile
	python iuwandbox.py $< -c $(WANDBOX_COMPILER) -f"-DIUTEST_USE_MAIN" --encoding utf-8-sig $(EXPAND_INCLUDE)

xml: ../../test/syntax_tests.cpp Makefile
	python iuwandbox.py $< -c $(WANDBOX_COMPILER) -f"-DIUTEST_USE_MAIN" --encoding utf-8-sig $(EXPAND_INCLUDE) --xml test_result.xml

test-gcc: ../../test/syntax_tests.cpp Makefile
	python iuwandbox.py $< -c gcc-head -f"-DIUTEST_USE_MAIN" -x "warning,gnu++1y" -f"-Wsuggest-override" --encoding utf-8-sig $(EXPAND_INCLUDE)

test-clang: ../../test/syntax_tests.cpp Makefile
	python iuwandbox.py $< -c clang-head -f"-DIUTEST_USE_MAIN" -x "warning,gnu++1y" --encoding utf-8-sig $(EXPAND_INCLUDE)

test-gcc-98: ../../test/syntax_tests.cpp Makefile
	python iuwandbox.py $< -c gcc-head -f"-DIUTEST_USE_MAIN" -x "warning,c++98" --encoding utf-8-sig $(EXPAND_INCLUDE)

list-compiler:
	python iuwandbox.py --list_compiler

list-options:
	python iuwandbox.py --list_options $(WANDBOX_COMPILER)

COMPILE_ERROR_TESTS=\
	iutest_check_strict_tests \
	iutest_static_assertion_failure_tests \

COMPILE_ERROR_TESTS_SRC=$(COMPILE_ERROR_TESTS:%=../../test/%.cpp)


$(COMPILE_ERROR_TESTS) : $(COMPILE_ERROR_TESTS_SRC) Makefile
#	-python iuwandbox.py ../../test/$@.cpp -c clang-head -x "warning,gnu++1y" --encoding utf-8-sig $(EXPAND_INCLUDE)
	python iuwandbox.py ../../test/$@.cpp -c clang-head -x "warning,gnu++1y" --encoding utf-8-sig $(EXPAND_INCLUDE) | python ../python/iutest_compile_error_test.py -c clang
#	python iuwandbox.py ../../test/$@.cpp -c gcc-head -x "warning,gnu++1y" --encoding utf-8-sig $(EXPAND_INCLUDE) | python ../python/iutest_compile_error_test.py -c gcc

compile-error: $(COMPILE_ERROR_TESTS) Makefile

clean:
	$(RM) sample
