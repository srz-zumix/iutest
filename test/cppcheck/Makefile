# Copyright (C) 2018-2021, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE


# iutest root directory
IUTEST_DIR = ../..
IUTEST_INCLUDE = -I$(IUTEST_DIR)/include

IUTEST_HEADERS =$(IUTEST_DIR)/include/*.hpp \
				$(IUTEST_DIR)/include/impl/*.ipp \
				$(IUTEST_DIR)/include/internal/*.hpp \
				$(IUTEST_DIR)/include/listener/*.hpp \
				$(IUTEST_DIR)/include/util/*.hpp \
				$(IUTEST_DIR)/include/gtest/*.hpp \
				$(IUTEST_DIR)/include/gtest/switch/*.hpp

#
# cppcheck configuration
#

include Config.mk

CPPCHECK_DEFINES_OPTIONS=$(patsubst %,-D%,$(CPPCHECK_DEFINES))
CPPCHECK_UNDEFINES_OPTIONS=$(patsubst %,-U%,$(CPPCHECK_UNDEFINES))
CPPCHECK_SUPPRESS_OPTIONS=$(patsubst %,--suppress=%,$(CPPCHECK_SUPPRESS))

CPPCHECK_ENABLE_OPTION= --enable=all

DEFAULT_OPTIONS=--inline-suppr -j8 --platform=unix64

ifdef FULL
DEFAULT_OPTIONS+= -f
endif
ifdef CTU_DEPTH
DEFAULT_OPTIONS+= --max-ctu-depth=$(CTU_DEPTH)
endif
ifdef USE_CLANG
DEFAULT_OPTIONS+= --clang
endif

OPTIONS+= $(DEFAULT_OPTIONS)
OPTIONS+= $(CPPCHECK_ENABLE_OPTION)
OPTIONS+= $(CPPCHECK_DEFINES_OPTIONS)
OPTIONS+= $(CPPCHECK_UNDEFINES_OPTIONS)
OPTIONS+= $(CPPCHECK_SUPPRESS_OPTIONS)
ifdef CPPCHECK_ADD_OPTIONS
OPTIONS+= $(CPPCHECK_ADD_OPTIONS)
endif

SRC_CPP=$(wildcard ../../src/*.cpp)
SAMPLES=$(wildcard ../../samples/*.cpp)
TESTS=$(wildcard ../../test/*.cpp)

SRCS=$(SRC_CPP) \
	$(TESTS) \
	#$(SAMPLES) \

TARGETS=cppcheck_result.xml

#
#
# build targets.
#

.PHONY: clean default all

default: version $(TARGETS)

all: clean default

clean:
	$(RM) $(TARGETS) check-config.xml ./html

version:
	cppcheck --version

check-config:
	cppcheck $(IUTEST_INCLUDE) $(OPTIONS) $(SRCS) --check-config --xml 2> $@.xml

$(TARGETS): $(SRC_CPP) $(IUTEST_HEADERS) Config.mk
	cppcheck $(IUTEST_INCLUDE) $(OPTIONS) $(SRCS) --xml 2> $@

HTML_REPORT_DIR:=./html
html: $(TARGETS)
	@if [ ! -e ${HTML_REPORT_DIR} ]; then mkdir -p ${HTML_REPORT_DIR}; fi
	cppcheck-htmlreport --file=$< --title=iutest --report-dir=${HTML_REPORT_DIR}
	# cppcheck-htmlreport --file=$< --title=iutest --report-dir=./html --source-dir=$(IUTEST_DIR)/include
