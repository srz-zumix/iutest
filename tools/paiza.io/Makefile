#
# Makefile

.PHONY: sample

TOOLS=paizaio.py iupaiza.py

WANDBOX_COMPILER?=gcc-head

help: $(TOOLS)
	python iupaiza.py -h
	
fused:
	make -C ../fused

sample: sample.cpp $(TOOLS) Makefile
	python iupaiza.py sample.cpp

save: sample.cpp $(TOOLS) Makefile
	python iupaiza.py sample.cpp

test: ../../test/syntax_tests.cpp Makefile
	#python iupaiza.py $< -c $(WANDBOX_COMPILER) -f"-DIUTEST_USE_MAIN" --expand_include --encoding utf-8-sig
	
lentest: Makefile
	dd if=/dev/zero of=lentest.cpp bs=100001 count=1
	python iupaiza.py lentest.cpp
