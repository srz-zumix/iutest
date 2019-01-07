#
# Makefile

OUTDIR=tmp
INPUT_XML1=unit_tests.xml
INPUT_XML2=matcher_tests.xml
INPUT_XMLS=$(INPUT_XML1) $(INPUT_XML2)

.PHONY: default clean

default: xml2file

clean:
	rm -rf $(OUTDIR)
	rm -rf $(INPUT_XMLS)

xml2file: $(INPUT_XML1) xml2file.py
	python xml2file.py -o $(OUTDIR) $(INPUT_XML1)

multi: $(INPUT_XML1) $(INPUT_XML2) xml2file.py
	python xml2file.py -o $(OUTDIR) $(INPUT_XML1) $(INPUT_XML2)

$(INPUT_XMLS):
	make -C ../../test OUTPUTXML=1 run_$(@:%.xml=%)
	cp ../../test/$@ $@
