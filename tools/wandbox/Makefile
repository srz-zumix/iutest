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
	
