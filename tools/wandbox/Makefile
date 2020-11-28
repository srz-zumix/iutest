#
# Makefile

include ../../test/CommonMakefile.in

.PHONY: sample

TOOLS=wandbox.py iuwandbox.py

#EXPAND_INCLUDE?=--expand-include

# TEST_SRC=../../test/syntax_tests.cpp
TEST_SRC=../../test/assertion_tests.cpp

WANDBOX_COMPILER?=gcc-head

help: $(TOOLS)
	python iuwandbox.py -h

fused:
	make -C ../fused

sample: sample.cpp $(TOOLS) Makefile
	python iuwandbox.py sample.cpp -f"-Dx=hogefuga -O3" --check-config -x "warning"

sample2: sample.cpp sample2.cpp $(TOOLS) Makefile
	python iuwandbox.py sample.cpp sample2.cpp -f"-Dx=hogefuga -O3 -DSAMPLE2" --check-config -x "warning"

save: sample.cpp $(TOOLS) Makefile
	python iuwandbox.py sample.cpp -s -x "warning" -f"-Dx=hogefuga -O3" -r"--iutest_color=no" $(EXPAND_INCLUDE)

local:
	g++ sample.cpp sample2.cpp -o sample
	./sample

test: $(TEST_SRC) Makefile
	python iuwandbox.py $< -c $(WANDBOX_COMPILER) -f"-DIUTEST_USE_MAIN" --encoding utf-8-sig $(EXPAND_INCLUDE)

xml: $(TEST_SRC) Makefile
	python iuwandbox.py $< -c $(WANDBOX_COMPILER) -f"-DIUTEST_USE_MAIN" --encoding utf-8-sig $(EXPAND_INCLUDE) --xml test_result.xml

junit: $(TEST_SRC) Makefile
	python iuwandbox.py $< -c $(WANDBOX_COMPILER) -f"-DIUTEST_USE_MAIN" --encoding utf-8-sig $(EXPAND_INCLUDE) --junit junit_test_result.xml

experimental: $(TEST_SRC) Makefile
	python iuwandbox.py $< -c $(WANDBOX_COMPILER) -f"-DIUTEST_USE_MAIN" --encoding utf-8-sig $(EXPAND_INCLUDE) --iutest-use-wandbox-min

full: $(TEST_SRC) Makefile
	python iuwandbox.py $< -c $(WANDBOX_COMPILER) -f"-DIUTEST_USE_MAIN" --encoding utf-8-sig $(EXPAND_INCLUDE) --no-iutest-use-wandbox-min

test-gcc: $(TEST_SRC) Makefile
	python iuwandbox.py $< -c gcc-head -f"-DIUTEST_USE_MAIN" -x "warning,gnu++1y" -f"-Wsuggest-override" --encoding utf-8-sig $(EXPAND_INCLUDE)

test-clang: $(TEST_SRC) Makefile
	python iuwandbox.py $< -c clang-head -f"-DIUTEST_USE_MAIN" -x "warning,gnu++1y" --encoding utf-8-sig $(EXPAND_INCLUDE)

test-gcc-98: $(TEST_SRC) Makefile
	python iuwandbox.py $< -c gcc-head -f"-DIUTEST_USE_MAIN" -x "warning,c++98" --encoding utf-8-sig $(EXPAND_INCLUDE)

test-make: $(TEST_SRC) Makefile
	python iuwandbox.py $< -c $(WANDBOX_COMPILER) -f"-DIUTEST_USE_MAIN" --encoding utf-8-sig $(EXPAND_INCLUDE) --make

save-make: $(TEST_SRC) Makefile
	python iuwandbox.py $< -c gcc-head -f"-DIUTEST_USE_MAIN" --encoding utf-8-sig $(EXPAND_INCLUDE) --make -s

test-no-min: $(TEST_SRC) Makefile
	python iuwandbox.py $< -f"-DIUTEST_USE_MAIN" --encoding utf-8-sig $(EXPAND_INCLUDE) --no-iutest-use-wandbox-min

sample-no-min: sample.cpp $(TOOLS) Makefile
	python iuwandbox.py $< -f"-DIUTEST_USE_MAIN" --encoding utf-8-sig $(EXPAND_INCLUDE) --no-iutest-use-wandbox-min

boost: $(TEST_SRC) Makefile
	python iuwandbox.py $< -c $(WANDBOX_COMPILER) --boost 1.60 -f"-DIUTEST_USE_MAIN" --encoding utf-8-sig $(EXPAND_INCLUDE) --verbose --dryrun

dryrun-test: $(TEST_SRC) Makefile
	# boost option test
	python iuwandbox.py $< -c $(WANDBOX_COMPILER) --boost 1.60 -f"-DIUTEST_USE_MAIN" --encoding utf-8-sig $(EXPAND_INCLUDE) --verbose --dryrun
	python iuwandbox.py $< -c $(WANDBOX_COMPILER) --default --boost 1.60 -f"-DIUTEST_USE_MAIN" --encoding utf-8-sig $(EXPAND_INCLUDE) --verbose --dryrun

test-all-compiler: $(TEST_SRC) Makefile fused
	@for compiler in $(shell python iuwandbox.py --list-compiler); do \
		echo $${compiler}; \
		python iuwandbox.py $< -c $${compiler} -f"-DIUTEST_USE_MAIN" -f"-Werror" --encoding utf-8-sig --verbose $(WANDBOX_ADD_OPTIONS) || exit 1; \
	done

list-compiler:
	python iuwandbox.py --list-compiler --verbose

list-options:
	python iuwandbox.py --list-options $(WANDBOX_COMPILER)

#
# raw api
#
get-list-json:
	mkdir -p tmp
	curl https://wandbox.org/api/list.json > tmp/list.json

#
# iutest test
#

ALLTESTS_SRCS_=$(ALLTESTS_SRCS:%=../../test/%)

alltest: $(ALLTESTS_SRCS_) Makefile
	python iuwandbox.py $(ALLTESTS_SRCS_) -c $(WANDBOX_COMPILER) --encoding utf-8-sig $(EXPAND_INCLUDE)

alltest-dryrun: $(ALLTESTS_SRCS_) Makefile
	python iuwandbox.py $(ALLTESTS_SRCS_) -c $(WANDBOX_COMPILER) --encoding utf-8-sig $(EXPAND_INCLUDE) --dryrun

alltest-make: $(ALLTESTS_SRCS_) Makefile
	python iuwandbox.py $(ALLTESTS_SRCS_) -c $(WANDBOX_COMPILER) --encoding utf-8-sig $(EXPAND_INCLUDE) --make


COMPILE_ERROR_TESTS_SRC_=$(COMPILEERROR_TARGETS:%=../../test/%.cpp)

$(COMPILEERROR_TARGETS) : $(COMPILE_ERROR_TESTS_SRC_) Makefile
#	-python iuwandbox.py ../../test/$@.cpp -c clang-head -x "warning,gnu++1y" --encoding utf-8-sig $(EXPAND_INCLUDE)
	python iuwandbox.py ../../test/$@.cpp -c clang-head -x "warning,gnu++1y" --encoding utf-8-sig $(EXPAND_INCLUDE) | python ../python/iutest_compile_error_test.py -c clang
#	python iuwandbox.py ../../test/$@.cpp -c gcc-head -x "warning,gnu++1y" --encoding utf-8-sig $(EXPAND_INCLUDE) | python ../python/iutest_compile_error_test.py -c gcc

compile-error: $(COMPILE_ERROR_TESTS) Makefile

#
# unittest
#
utest: unittest

unittest:
	unit2 discover .

#
# profile
#

profile: $(TEST_SRC) Makefile
	python -m cProfile -s time iuwandbox.py $< -c $(WANDBOX_COMPILER) -f"-DIUTEST_USE_MAIN" --encoding utf-8-sig $(EXPAND_INCLUDE)

clean:
	$(RM) sample
