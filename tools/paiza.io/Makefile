#
# Makefile

.PHONY: sample

TOOLS=paizaio.py iupaiza.py

help: $(TOOLS)
	python iupaiza.py -h
	
fused:
	make -C ../fused

sample: sample.cpp $(TOOLS) Makefile
	python iupaiza.py sample.cpp

save: sample.cpp $(TOOLS) Makefile
	python iupaiza.py sample.cpp

test: ../../test/syntax_tests.cpp Makefile
	python iupaiza.py $< -f"-DIUTEST_USE_MAIN" --expand_include --encoding utf-8-sig

minimum_tests: ../../test/minimum_tests.cpp Makefile
	python iupaiza.py $< -f"-DIUTEST_USE_MAIN" --expand_include --encoding utf-8-sig

lentest: Makefile
	dd if=/dev/zero of=lentest.cpp bs=100001 count=1
	python iupaiza.py lentest.cpp

local: paizaio-sourcecode.cpp Makefile
	clang++ -std=c++11 $< -o paizaio

paizaio-sourcecode: paizaio-sourcecode.cpp Makefile
	python iupaiza.py paizaio-sourcecode.cpp -f"-DIUTEST_USE_MAIN" --expand_include --encoding utf-8-sig

clean:
	$(RM) paizaio paizaio-sourcecode.cpp paizaio-toolong-sourcecode.cpp *.pyc

