#
# cxx.mk
#
# c++ command help
#
# Copyright (C) 2019-2020, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

ifeq ($(findstring c++, $(CXX)), c++)

ifeq ($(shell $(CXX) --version | grep -o clang), clang)
CXX_NAME=clang++
endif

ifeq ($(shell $(CXX) --version | grep -o GCC), GCC)
CXX_NAME=g++
endif

# $(warning CXX_NAME = $(CXX_NAME))

endif
