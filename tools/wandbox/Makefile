#
# Makefile

.PHONY: sample

TOOLS=wandbox.py iuwandbox.py

WANDBOX_COMPILER?=gcc-head

fuse:
	make -C ../fuse

help: $(TOOLS)
	python iuwandbox.py -h
	
sample: sample.cpp $(TOOLS) Makefile
	python iuwandbox.py sample.cpp -f"-Dx=hogefuga\n-O3" --check_config

save: sample.cpp $(TOOLS) Makefile
	python iuwandbox.py sample.cpp -s -x "warning" -f"-Dx=hogefuga\n-O3" -r"--iutest_color=no" --expand_include

local:
	g++ sample.cpp -o sample
	./sample
	
test: ../../test/iutest_syntax_tests.cpp Makefile
	python iuwandbox.py $< -c $(WANDBOX_COMPILER) -f"-DIUTEST_USE_MAIN" --expand_include --encoding utf-8-sig

test-gcc: ../../test/iutest_syntax_tests.cpp Makefile
	python iuwandbox.py $< -c gcc-head -f"-DIUTEST_USE_MAIN" -x "warning,gnu++1y" --expand_include --encoding utf-8-sig

test-clang: ../../test/iutest_syntax_tests.cpp Makefile
	python iuwandbox.py $< -c clang-head -f"-DIUTEST_USE_MAIN" -x "warning,gnu++1y" --expand_include --encoding utf-8-sig

check-strict: ../../test/iutest_check_strict_tests.cpp Makefile
#	-python iuwandbox.py $< -c clang-head -x "warning,gnu++1y" --expand_include --encoding utf-8-sig
	python iuwandbox.py $< -c clang-head -x "warning,gnu++1y" --expand_include --encoding utf-8-sig | python ../python/iutest_compile_error_test.py -c clang
#	python iuwandbox.py $< -c gcc-head -x "warning,gnu++1y" --expand_include --encoding utf-8-sig | python ../python/iutest_compile_error_test.py -c gcc
