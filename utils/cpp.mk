#
# cxx.mk
#
# c++ command help
#
# Copyright (C) 2019, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

UTILS_MAKEFILE_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

include $(UTILS_MAKEFILE_DIR)/gccversion.mk
include $(UTILS_MAKEFILE_DIR)/clangversion.mk

ifeq ($(findstring c++, $(CXX)), c++)

ifeq ($(shell $(CXX) --version | grep -o clang), clang)
CXX_NAME=clang++
CXX_MAJOR=${CLANGMAJOR}
CXX_MINOR=${CLANGMINOR}
CXX_VERSION=${CXX_MAJOR}.${CXX_MINOR}
endif

ifeq ($(shell $(CXX) --version | grep -o GCC), GCC)
CXX_NAME=g++
CXX_MAJOR=${GCCMAJOR}
CXX_MINOR=${GCCMINOR}
CXX_VERSION=${CXX_MAJOR}.${CXX_MINOR}
endif

# $(warning CXX_NAME = $(CXX_NAME))

endif
