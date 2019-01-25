#
#
#
# Copyright (C) 2018-2019, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE

# iutest root directory
IUTEST_DIR = ../..
# iutest include directory
IUTEST_INCLUDE = -I$(IUTEST_DIR)/include

# All iutest headers.  Usually you shouldn't change this
# definition.
IUTEST_HEADERS =$(IUTEST_DIR)/include/*.hpp \
				$(IUTEST_DIR)/include/impl/*.ipp \
				$(IUTEST_DIR)/include/internal/*.hpp \
				$(IUTEST_DIR)/include/listener/*.hpp \
				$(IUTEST_DIR)/include/util/*.hpp \
				$(IUTEST_DIR)/include/gtest/*.hpp \
				$(IUTEST_DIR)/include/gtest/switch/*.hpp

# fused-src directory
FUSED_DIR = $(IUTEST_DIR)/fused-src

# fused src output
FUSED_TARGETS=iutest.hpp iutest.min.hpp
FUSED_WANDBOX_TARGET=iutest.wandbox.min.hpp
OUTPUTS_TARGETS=$(FUSED_TARGETS) $(FUSED_WANDBOX_TARGET)
OUTPUTS=$(OUTPUTS_TARGETS:%=$(FUSED_DIR)/%)

default: fused wandbox

fused: iutest.hpp iutest.min.hpp

$(FUSED_TARGETS): fused_impl

fused_impl: $(FUSED_DIR) $(IUTEST_HEADERS) fused_iutest_files.py Makefile
	python fused_iutest_files.py $(FUSED_DIR)

min: fused
	mv $(FUSED_DIR)/iutest.min.hpp $(FUSED_DIR)/iutest.hpp

wandbox: iutest.wandbox.min.hpp

$(FUSED_WANDBOX_TARGET): fused
	python iuwandbox_pp.py

wandbox_debug: fused
	python iuwandbox_pp.py debug

ls:
	ls -lh ../../fused-src

# tests
TEST_TARGETS=min_test wandbox_test

min_test: fused
	g++ tests/test.min.cpp -o $@
	./$@

wandbox_test: wandbox
	g++ tests/test.wandbox.min.cpp -o $@
	./$@

clean:
	$(RM) -rf $(OUTPUTS)
	$(RM) -rf $(TEST_TARGETS)

$(FUSED_DIR):
	@if [ ! -d $@ ]; then \
		mkdir -p $@; \
	fi
