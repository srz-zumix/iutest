#
# python.mk
#
# Copyright (C) 2020, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

UTILS_MAKEFILE_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
include $(UTILS_MAKEFILE_DIR)/function.mk

PYTHON_VERSION_FULL_ := $(wordlist 2,4,$(subst ., ,$(shell python --version 2>&1)))

ifneq ($(PYTHON_VERSION_FULL_),)

PYTHON_VERSION := ${PYTHON_VERSION_FULL_}

PYTHON_VERSION_MAJOR_ := $(word 1,${PYTHON_VERSION})
PYTHON_VERSION_MINOR_ := $(word 2,${PYTHON_VERSION})
PYTHON_VERSION_PATCH_ := $(word 3,${PYTHON_VERSION})

ifeq ($(call is_number, $(PYTHON_VERSION_MAJOR_)),true)
PYTHON_VERSION_MAJOR := $(PYTHON_VERSION_MAJOR_)
endif
ifeq ($(call is_number, $(PYTHON_VERSION_MINOR_)),true)
PYTHON_VERSION_MINOR := $(PYTHON_VERSION_MINOR_)
endif
ifeq ($(call is_number, $(PYTHON_VERSION_PATCH_)),true)
PYTHON_VERSION_PATCH := $(PYTHON_VERSION_PATCH_)
endif

endif

ifndef PYTHON_VERSION_MAJOR
PYTHON_VERSION_MAJOR := 0
endif
ifndef PYTHON_VERSION_MINOR
PYTHON_VERSION_MINOR := 0
endif
ifndef PYTHON_VERSION_PATCH
PYTHON_VERSION_PATCH := 0
endif

# $(warning ${PYTHON_VERSION_MAJOR})
# $(warning ${PYTHON_VERSION_MINOR})
# $(warning ${PYTHON_VERSION_PATCH})

# 2.7 later
ifeq (1,$(shell expr \( \( $(PYTHON_VERSION_MAJOR) \>= 3 \) \| \( $(PYTHON_VERSION_MAJOR) \>= 2 \& $(PYTHON_VERSION_MINOR) \>= 7 \) \)))
IUTEST_USE_PYTHON:=1
else
IUTEST_USE_PYTHON:=0
endif
