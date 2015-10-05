#
# Makefile

.PHONY: sample

TOOLS=paiza.py iupaiza.py

WANDBOX_COMPILER?=gcc-head

fused:
	make -C ../fused

help: $(TOOLS)
	python iupaiza.py -h
	
sample: sample.cpp $(TOOLS) Makefile
	python iupaiza.py sample.cpp

save: sample.cpp $(TOOLS) Makefile
	python iupaiza.py sample.cpp

test: ../../test/syntax_tests.cpp Makefile
	#python iupaiza.py $< -c $(WANDBOX_COMPILER) -f"-DIUTEST_USE_MAIN" --expand_include --encoding utf-8-sig
	
lentest: Makefile
	dd if=/dev/zero of=lentest.cpp bs=100001 count=1
	python iupaiza.py lentest.cpp
