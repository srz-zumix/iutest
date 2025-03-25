#
# xcode.mk
#
# detect xcode compiler
#
# Copyright (C) 2018-2020, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

APPLE_CXXVERSION:=$(shell $(CXX) --version | grep -o Apple)

ifeq ($(APPLE_CXXVERSION),Apple)

CXX_APPLE_CLANG=1
CXX_NAME=clang++
APPLE_CLANGVERSION:=$(shell $(CXX) --version | grep -o "version\s[0-9]*\.[0-9]*\.[0-9]*")

dot:=.
empty:=
space:=$(empty) $(empty)
APPLE_CLANGVERSION:=$(subst -,$(dot), $(APPLE_CLANGVERSION))
APPLE_CLANGVERSION:=$(subst $(dot),$(space), $(APPLE_CLANGVERSION))
APPLE_CLANGVERSION:=$(subst version,, $(APPLE_CLANGVERSION))

# $(warning ${APPLE_CLANGVERSION})

APPLE_CLANGMAJOR:=$(word 1, $(APPLE_CLANGVERSION))
APPLE_CLANGMINOR:=$(word 2, $(APPLE_CLANGVERSION))
APPLE_CLANGPATCH:=$(word 3, $(APPLE_CLANGVERSION))

# $(warning ${APPLE_CLANGMAJOR})
# $(warning ${APPLE_CLANGMINOR})
# $(warning ${APPLE_CLANGPATCH})

ifeq ($(words $(APPLE_CLANGVERSION)), 3)

# https://en.wikipedia.org/wiki/Xcode#Toolchain_versions

# 17
ifeq (1,$(shell expr \( $(APPLE_CLANGMAJOR) \>= 17 \)))
  CLANGMAJOR:=19
  CLANGMINOR:=0
# 16
else ifeq (1,$(shell expr \( $(APPLE_CLANGMAJOR) \>= 16 \)))
  CLANGMAJOR:=17
  CLANGMINOR:=0
# 15
else ifeq (1,$(shell expr \( $(APPLE_CLANGMAJOR) \>= 15 \)))
  CLANGMAJOR:=16
  CLANGMINOR:=0
# 14
else ifeq (1,$(shell expr \( $(APPLE_CLANGMAJOR) \>= 14 \)))

ifeq (1,$(shell expr \( $(APPLE_CLANGPATCH) \>= 3 \)))
CLANGMAJOR:=15
CLANGMINOR:=0
else
CLANGMAJOR:=14
CLANGMINOR:=0
endif

# 13
else ifeq (1,$(shell expr \( $(APPLE_CLANGMAJOR) \>= 13 \)))

ifeq (1,$(shell expr \( $(APPLE_CLANGMINOR) \>= 1 \)))
CLANGMAJOR:=13
CLANGMINOR:=0
else
CLANGMAJOR:=12
CLANGMINOR:=0
endif

# 12
else ifeq (1,$(shell expr \( $(APPLE_CLANGMAJOR) \>= 12 \)))

ifeq (1,$(shell expr \( $(APPLE_CLANGPATCH) \>= 5 \)))
CLANGMAJOR:=11
CLANGMINOR:=0
else
CLANGMAJOR:=10
CLANGMINOR:=0
endif

# 11
else ifeq (1,$(shell expr \( $(APPLE_CLANGMAJOR) \>= 11 \)))

ifeq (1,$(shell expr \( $(APPLE_CLANGPATCH) \>= 3 \)))
CLANGMAJOR:=9
CLANGMINOR:=0
else
CLANGMAJOR:=8
CLANGMINOR:=0
endif

# 10
else ifeq (1,$(shell expr \( $(APPLE_CLANGMAJOR) \>= 10 \)))

ifeq (1,$(shell expr \( $(APPLE_CLANGMINOR) \>= 1 \)))
CLANGMAJOR:=7
CLANGMINOR:=0
else
CLANGMAJOR:=6
CLANGMINOR:=0
endif

# 9
else ifeq (1,$(shell expr \( $(APPLE_CLANGMAJOR) \>= 9 \)))

ifeq (1,$(shell expr \( $(APPLE_CLANGMINOR) \>= 1 \)))
CLANGMAJOR:=5
CLANGMINOR:=0
else
CLANGMAJOR:=4
CLANGMINOR:=0
endif

# 8
else ifeq (1,$(shell expr \( $(APPLE_CLANGMAJOR) \>= 8 \)))

CLANGMAJOR:=3
CLANGMINOR:=9

# 7
else ifeq (1,$(shell expr \( $(APPLE_CLANGMAJOR) \>= 7 \)))

ifeq (1,$(shell expr \( $(APPLE_CLANGMINOR) \>= 3 \)))
CLANGMINOR:=8
else
CLANGMINOR:=7
endif

else

# 6 or older
CLANGMAJOR:=3
CLANGMINOR:=${APPLE_CLANGMAJOR}

endif

else

# failed word split
CLANGMAJOR:=0
CLANGMINOR:=0

endif

CXX_MAJOR=${CLANGMAJOR}
CXX_MINOR=${CLANGMINOR}
CXX_VERSION=${CXX_MAJOR}.${CXX_MINOR}

# 9.0 later
ifeq (1,$(shell expr \( $(APPLE_CLANGMAJOR) \>= 9 \)))
IUTEST_CXX_STRICT_NOWARN_FLAGS+=-Wno-inconsistent-missing-destructor-override
endif


endif # Apple
