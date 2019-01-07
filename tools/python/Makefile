#
# Makefile

.PHONY: sample clean
TOOLS=eval_line.py

sample: $(TOOLS) Makefile
	python eval_line.py '#define PP_INC_$${line} $${line+1}' -r 255 -s 1 -o pp_inc.h --encoding utf-8-sig

clean:
	rm -rf pp_inc.h

xml2file:
	make -C ../../test OUTPUTXML=1 run_matcher_tests > /dev/null
	make -C ../../test OUTPUTXML=1 run_unit_tests > /dev/null
	python xml2file.py -o tmp ../../test/unit_tests.xml ../../test/matcher_tests.xml
