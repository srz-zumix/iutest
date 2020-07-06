#
# utils.mk
#
# makefile utils
#
# Copyright (C) 2019-2020, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

UTILS_MAKEFILE_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

include $(UTILS_MAKEFILE_DIR)/cpp.mk
include $(UTILS_MAKEFILE_DIR)/xcode.mk
include $(UTILS_MAKEFILE_DIR)/cygwin.mk
include $(UTILS_MAKEFILE_DIR)/mingw.mk
include $(UTILS_MAKEFILE_DIR)/ci.mk
include $(UTILS_MAKEFILE_DIR)/python.mk
