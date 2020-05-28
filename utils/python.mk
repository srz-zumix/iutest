#
# python.mk
#
# Copyright (C) 2020, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

PYTHON_VERSION_FULL_ := $(wordlist 2,4,$(subst ., ,$(shell python --version 2>&1)))

ifneq ($(PYTHON_VERSION_FULL_),)

PYTHON_VERSION=${PYTHON_VERSION_FULL_}
PYTHON_VERSION_MAJOR := $(word 1,${PYTHON_VERSION})
PYTHON_VERSION_MINOR := $(word 2,${PYTHON_VERSION})
PYTHON_VERSION_PATCH := $(word 3,${PYTHON_VERSION})

# $(warning ${PYTHON_VERSION})

else

PYTHON_VERSION_MAJOR := 0
PYTHON_VERSION_MINOR := 0
PYTHON_VERSION_PATCH := 0

endif

# 2.7 later
ifeq (1,$(shell expr \( \( $(PYTHON_VERSION_MAJOR) \> 3 \) \| \( $(PYTHON_VERSION_MAJOR) \>= 3 \& $(PYTHON_VERSION_MINOR) \>= 7 \) \)))
IUTEST_USE_PYTHON:=1
else
IUTEST_USE_PYTHON:=0
endif
