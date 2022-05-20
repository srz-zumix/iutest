#
# Makefile
#
# Copyright (C) 2022, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

EXECUTE_TARGET=stdlib_feature_test
TARGET=stdlib_feature_test.pp
MAKEFILE=Makefile

.PHONY: clean default all test show

default : all

all : clean default show ## clean and build, run

# dir :
# 	@if [ ! -e `dirname $(OUTDIR)` ]; then mkdir -p `dirname $(OUTDIR)`; fi

clean : ## clean
	$(RM) $(TARGET) $(EXECUTE_TARGET) show_macros.i

test : $(EXECUTE_TARGET) ## run tests
	./${EXECUTE_TARGET}

${EXECUTE_TARGET}: % : %.cpp show_macros.i $(MAKEFILE)
	$(CXX) $(CXXFLAGS) -Wno-unused-macros -DFEATURE_TEST_EXECUTABLE -o $@ $<

show : $(TARGET) ## show feature macros
	@cat -s ./$(TARGET) \
		| grep -A 256 show_macros.i \
		| grep -B 256 stdlib_feature_test.cpp \
		| sed '/^#/d' \
		| sed 's/[";]//g' \
		| tr -d '\n' \
		| sed -e 's/define/\ndefine/g' -e 's/undef/\nundef/g' \
		| sed '/^$$/d' \
		| sed 's/^/#/g' \
		| paste -

${TARGET}: %.pp : %.cpp show_macros.i $(MAKEFILE)
	$(CXX) $(CXXFLAGS) -E -x c++ -o $@ $<

FEATURE_MACROS=\
	_POSIX_C_SOURCE \
	_POSIX_SOURCE \
	_XOPEN_SOURCE \
	_XOPEN_SOURCE_EXTENDED \
	_ISOC99_SOURCE \
	_ISOC11_SOURCE \
	_LARGEFILE64_SOURCE \
	_LARGEFILE_SOURCE \
	_FILE_OFFSET_BITS \
	_BSD_SOURCE \
	_SVID_SOURCE \
	_DEFAULT_SOURCE \
	_ATFILE_SOURCE \
	_GNU_SOURCE \
	_REENT_ONLY \
	_REENTRANT \
	_THREAD_SAFE \
	_FORTIFY_SOURCE \
	__ISO_C_VISIBLE \
	__ATFILE_VISIBLE \
	__BSD_VISIBLE \
	__GNU_VISIBLE \
	__MISC_VISIBLE \
	__POSIX_VISIBLE \
	__SVID_VISIBLE \
	__XSI_VISIBLE \
	__MINGW__ \
	__MINGW32__	\
	__MINGW64__ \
	__STRICT_ANSI__

show_macros.i: show_macros.tmp $(MAKEFILE)
	rm -f $@
	for m in $(FEATURE_MACROS); do sed -e "s/@DEF/$${m}/g" $< >> $@; done

