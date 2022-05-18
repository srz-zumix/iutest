#
# Makefile
#
# Copyright (C) 2022, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

EXECUTE_TARGET=stdlib_config_check
TARGET=stdlib_config_check.pp
MAKEFILE=Makefile

.PHONY: clean default all test show

default : all

all : clean default show ## clean and build, run

# dir :
# 	@if [ ! -e `dirname $(OUTDIR)` ]; then mkdir -p `dirname $(OUTDIR)`; fi

clean : ## clean
	$(RM) $(TARGET) $(EXECUTE_TARGET)

test : $(EXECUTE_TARGET) ## run tests
	./${EXECUTE_TARGET}

${EXECUTE_TARGET}: % : %.cpp $(MAKEFILE)
	$(CXX) $(CXXFLAGS) -Wno-unused-macros -DSTDLIB_CONFIG_CHECK_EXECUTABLE -o $@ $<

show : $(TARGET) ## show feature macros
	@cat -s ./$(TARGET) \
		| grep -A 256 stdlib_config_check_macros.cpp \
		| grep -B 256 $(EXECUTE_TARGET).cpp \
		| sed '/^#/d' \
		| sed 's/[";]//g' \
		| tr -d '\n' \
		| sed -e 's/define/\ndefine/g' -e 's/undef/\nundef/g' \
		| sed '/^$$/d' \
		| sed 's/^/#/g' \
		| paste -

${TARGET}: %.pp : %.cpp $(MAKEFILE)
	$(CXX) $(CXXFLAGS) -Wno-unused-macros -E -x c++ -o $@ $<
