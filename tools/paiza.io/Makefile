#
# Makefile

.PHONY: sample

TOOLS=paizaio.py iupaizaio.py iupaizaio_pp.py

help: $(TOOLS)
	python iupaizaio.py -h

fused:
	make -C ../fused

sample: sample.cpp $(TOOLS) Makefile
	python iupaizaio.py sample.cpp

save: sample.cpp $(TOOLS) Makefile
	python iupaizaio.py sample.cpp

test: ../../test/syntax_tests.cpp Makefile
	python iupaizaio.py $< --use-main --expand_include --encoding utf-8-sig

minimum_tests: ../../test/minimum_tests.cpp Makefile
	python iupaizaio.py $< --use-main --expand_include --encoding utf-8-sig

lentest: Makefile
	dd if=/dev/zero of=lentest.cpp bs=100001 count=1
	python iupaizaio.py lentest.cpp

local: paizaio-sourcecode.cpp Makefile
	clang++ -std=c++11 $< -o paizaio

paizaio-sourcecode: paizaio-sourcecode.cpp Makefile
	python iupaizaio.py paizaio-sourcecode.cpp --use-main --expand_include --encoding utf-8-sig

clean:
	$(RM) paizaio paizaio-sourcecode.cpp paizaio-toolong-sourcecode.cpp *.pyc
