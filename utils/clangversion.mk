########################################
#
# Clang version check
#
########################################

ifeq ($(findstring clang++, $(CXX)), clang++)

CLANGVERSION:=$(shell $(CXX) --version | grep version | sed "s/.*version\s*\([0-9]*\.[0-9]*[\.-][0-9]*\).*/\1/")

dot:=.
empty:=
space:=$(empty) $(empty)
CLANGVERSION:=$(subst -,$(dot), $(CLANGVERSION))
CLANGVERSION:=$(subst $(dot),$(space), $(CLANGVERSION))

ifeq ($(words $(CLANGVERSION)), 3)
CLANGMAJOR:=$(word 1, $(CLANGVERSION))
CLANGMINOR:=$(word 2, $(CLANGVERSION))
else
CLANGMAJOR:=0
CLANGMINOR:=0
endif

STD_CPP03=c++98
STD_GNU03=gnu++98

STD_CPP11=c++11
STD_GNU11=gnu++11

NO_UNUSED_LOCAL_TYPEDEFS=-Wno-unused-local-typedefs

#
# c++14
#

# 3.5 later
ifeq (1,$(shell expr \( \( $(CLANGMAJOR) \> 3 \) \| \( $(CLANGMAJOR) \>= 3 \& $(CLANGMINOR) \>= 5 \) \)))
STD_CPP14=c++14
STD_GNU14=gnu++14
else

# 3.2 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \>= 3 \& $(CLANGMINOR) \>= 2 \)))
STD_CPP14=c++1y
STD_GNU14=gnu++1y
endif

endif

#
# c++17
#

# 3.5 later
ifeq (1,$(shell expr \( $(CLANGMAJOR) \> 3 \) \| \( $(CLANGMAJOR) \>= 3 \& $(CLANGMINOR) \>= 5 \)))
STD_CPP17=c++1z
STD_GNU17=gnu++1z
endif

#
# latest
#

STD_CPP=$(STD_CPP11)
STD_GNU=$(STD_GNU11)

ifdef STD_CPP14
STD_CPP=$(STD_CPP14)
STD_GNU=$(STD_GNU14)
endif

ifdef STD_CPP17
STD_CPP=$(STD_CPP17)
STD_GNU=$(STD_GNU17)
endif

ifndef STDFLAG
STDFLAG=-std=$(STD_CPP)
endif
#ifndef STDLIB
#STDLIB=-stdlib=libc++
#endif

endif
