# Copyright (C) 2018, Takazumi Shirayanagi
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

CPPCHECK_DEFINES= \
	IUTEST_HAS_CLOCK=1 \
	IUTEST_MAX_PATH=260 \

CPPCHECK_UNDEFINES= \
	__WIN32__ \
	_WIN32 \
	_MSC_VER \
	_MSC_FULL_VER \
	WINAPI_FAMILY \
	WINAPI_FAMILY_PHONE_APP \
	WIN32_LEAN_AND_MEAN \
	_NATIVE_WCHAR_T_DEFINED \
	__AFX_H__ \
	__clang__ \
	__clang_analyzer__ \
	IUTEST_CLANG_MAJOR \
	IUTEST_CLANG_MINOR \
	__CYGWIN__ \
	__APPLE__ \
	__ppc__ \
	__ppc64__ \
	ANDROID \
	__ANDROID__ \
	__CUDACC__ \
	__INTEL_COMPILER \
	COMPILER_ICC \
	__BORLANDC__ \
	__MWERKS__ \
	__MINGW32__ \
	__MINGW64__ \
	__MINGW__ \
	__AVR32__ \
	__avr32__ \
	__arm__ \
	__ARMCC_VERSION \
	_XOPEN_SOURCE \
	_BSD_SOURCE \
	_POSIX_C_SOURCE \
	sun \
	__sun \
	__SunOS \
	__native_client__ \
	__SGI_STL_PORT \
	_STLPORT_VERSION \
	_STLP_LONG_LONG \
	__USE_MINGW_ANSI_STDIO \
	__MAC_OS_X_VERSION_MIN_REQUIRED \
	__STDC_WANT_SECURE_LIB__ \
	IUTEST_BUILD_DOXYGEN \
	IUTEST_OS_WINDOWS_MINGW \
	IUTEST_OS_FREEBSD \
	IUTEST_OS_LINUX_ANDROID \
	IUTEST_OS_NACL \
	IUTEST_COND_UNLIKELY \
	IUTEST_ATTRIBUTE_LIKELY_ \
	IUTEST_ATTRIBUTE_UNLIKELY_ \
	IUTEST_ATTRIBUTE_INIT_PRIORITY_ \
	IUTEST_ATTRIBUTE_NO_SANITIZE_ADDRESS \
	IUTEST_ATTRIBUTE_NO_SANITIZE_MEMORY \
	IUTEST_ATTRIBUTE_NO_SANITIZE_THREAD \
	IUTEST_HAS_ATTRIBUTE_DEPRECATED \
	__WANDBOX__ \
	GTEST_OS_SOLARIS \
	GTEST_OS_WINDOWS \
	GTEST_OS_WINDOWS_MINGW \

	# IUTEST_USE_GTEST \


# C++20

CPPCHECK_DEFINES+= \
	IUTEST_CPLUSPLUS=202002L

CPPCHECK_SUPPRESS= \
	syntaxError \
	missingIncludeSystem \
	ConfigurationNotChecked \
	knownConditionTrueFalse:*/iutest_internal_defs.hpp \
	unmatchedSuppression

CPPCHECK_DEFINES_OPTIONS=$(patsubst %,-D%,$(CPPCHECK_DEFINES))
CPPCHECK_UNDEFINES_OPTIONS=$(patsubst %,-U%,$(CPPCHECK_UNDEFINES))
CPPCHECK_SUPPRESS_OPTIONS=$(patsubst %,--suppress=%,$(CPPCHECK_SUPPRESS))

CPPCHECK_ENABLE_OPTION= --enable=all

DEFAULT_OPTIONS=--inline-suppr -f -j8 --platform=unix64

ifdef USE_CLANG
DEFAULT_OPTIONS+= --clang
endif

OPTIONS+= $(DEFAULT_OPTIONS)
OPTIONS+= $(CPPCHECK_ENABLE_OPTION)
OPTIONS+= $(CPPCHECK_DEFINES_OPTIONS)
OPTIONS+= $(CPPCHECK_UNDEFINES_OPTIONS)
OPTIONS+= $(CPPCHECK_SUPPRESS_OPTIONS)

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
	$(RM) $(TARGETS) check-config.xml

version:
	cppcheck --version

check-config:
	cppcheck $(IUTEST_INCLUDE) $(OPTIONS) $(SRCS) --check-config --xml 2> $@.xml

$(TARGETS): $(SRC_CPP) Makefile
	cppcheck $(IUTEST_INCLUDE) $(OPTIONS) $(SRCS) --xml 2> $@

html: $(TARGETS)
	cppcheck-htmlreport --file=$< --title=iutest --report-dir=./html
	# cppcheck-htmlreport --file=$< --title=iutest --report-dir=./html --source-dir=$(IUTEST_DIR)/include
