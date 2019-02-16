#
# Makefile

TMPDIR=tmp
OUTDIR=$(TMPDIR)/files
INPUTDIR=$(TMPDIR)/inputs
INPUT_XML1=$(INPUTDIR)/unit_tests.xml
INPUT_XML2=$(INPUTDIR)/matcher_tests.xml
INPUT_XML_RECORD_PROPERTY=$(INPUTDIR)/record_property_tests.xml
INPUT_XML_DISABLED=$(INPUTDIR)/disabled_tests.xml
INPUT_XML_FAILURE=$(INPUTDIR)/no_failure_fail_tests.xml
INPUT_XML_JP=$(INPUTDIR)/japanese_tests.xml
INPUT_XMLS=$(INPUT_XML1) $(INPUT_XML2) $(INPUT_XML_RECORD_PROPERTY) $(INPUT_XML_DISABLED) $(INPUT_XML_FAILURE) $(INPUT_XML_JP)
XML2FILE=xml2file.py
# XML2FILE_OPTION+=--verbose
# XML2FILE_OPTION+=--debug
XML2FILE_EXEC=python $(XML2FILE) $(XML2FILE_OPTION)
XMLTYPE=junit
# XMLTYPE=default

ifeq ($(VERBOSE),1)
XML2FILE_OPTION+=--verbose
endif

.PHONY: default clean all

default: xml2file

all: clean default record_prop disabled failed multi

clean:
	rm -rf $(TMPDIR)
	make -C ../../test clean

xml2file: $(INPUT_XML1) $(XML2FILE)
	$(XML2FILE_EXEC) -o $(OUTDIR) $(INPUT_XML1)

record_prop: $(INPUT_XML_RECORD_PROPERTY) $(XML2FILE)
	$(XML2FILE_EXEC) -o $(OUTDIR) $(INPUT_XML_RECORD_PROPERTY)

disabled: $(INPUT_XML_DISABLED) $(XML2FILE)
	$(XML2FILE_EXEC) -o $(OUTDIR) $(INPUT_XML_DISABLED)

failed: $(INPUT_XML_FAILURE) $(XML2FILE)
	$(XML2FILE_EXEC) -o $(OUTDIR) $(INPUT_XML_FAILURE)

jp: $(INPUT_XML_JP) $(XML2FILE)
	$(XML2FILE_EXEC) -o $(OUTDIR) $(INPUT_XML_JP)

multi: $(INPUT_XML1) $(INPUT_XML2) $(XML2FILE)
	$(XML2FILE_EXEC) -o $(OUTDIR) $(INPUT_XML1) $(INPUT_XML2)

$(INPUT_XMLS):
	make -C ../../test $(@:$(INPUTDIR)/%.xml=%)
	make -C ../../test OUTPUTXML=$(XMLTYPE) run_$(@:$(INPUTDIR)/%.xml=%)
	mkdir -p $(INPUTDIR)
	cp ../../test/$(@:$(INPUTDIR)/%.xml=%.xml) $@
