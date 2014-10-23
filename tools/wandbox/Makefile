#
# Makefile

.PHONY: sample

TOOLS=pywandbox.py iuwandbox.py

fuse:
	make -C ../fuse

help: $(TOOLS)
	python iuwandbox.py -h
	
sample: sample.cpp $(TOOLS) Makefile
	python iuwandbox.py sample.cpp -x "warning,gnu++11" -f"-Dx=hogefuga\n-O3"

save: sample.cpp $(TOOLS) Makefile
	python iuwandbox.py sample.cpp -s -x "warning,gnu++11" -f"-Dx=hogefuga\n-O3" -r"--iutest_color=no"

