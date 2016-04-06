########################################
#
# GCC version check
#
########################################

#ifeq ($(CXX),g++)
ifeq ($(findstring g++, $(CXX)), g++)
ifneq ($(findstring clang++, $(CXX)), clang++)

GCCVERSION:=$(shell $(CXX) -dumpversion)

dot:=.
empty:=
space:=$(empty) $(empty)
GCCVERSION:=$(subst $(dot),$(space), $(GCCVERSION))
GCCMAJOR:=$(word 1, $(GCCVERSION))
GCCMINOR:=$(word 2, $(GCCVERSION))

STD_CPP03=c++98
STD_GNU03=gnu++98

#
# c++11
#

# 4.7 later
ifeq (1,$(shell expr \( $(GCCMAJOR) \> 4 \) \| \( $(GCCMAJOR) \>= 4 \& $(GCCMINOR) \>= 7 \)))
STD_CPP11=c++11
STD_GNU11=gnu++11

NO_UNUSED_LOCAL_TYPEDEFS=-Wno-unused-local-typedefs
else
STD_CPP11=c++0x
STD_GNU11=gnu++0x
endif

#
# c++14
#

# 5.0 later
ifeq (1,$(shell expr \( $(GCCMAJOR) \> 4 \) ))
STD_CPP14=c++14
STD_GNU14=gnu++14
else

# 4.8 later
ifeq (1,$(shell expr \( $(GCCMAJOR) \>= 4 \& $(GCCMINOR) \>= 8 \)))
STD_CPP14=c++1y
STD_GNU14=gnu++1y
endif

endif

#
# c++17
#

# 5.0 later
ifeq (1,$(shell expr \( $(GCCMAJOR) \> 4 \) ))
STD_CPP17=c++1z
STD_GNU17=gnu++1z
endif

#
# latest
#

STD_CPP=$(STD_CPP03)
STD_GNU=$(STD_GNU03)

ifdef STD_CPP11
STD_CPP=$(STD_CPP11)
STD_GNU=$(STD_GNU11)
endif

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

#
# Warning Option
#

# until 4.6
ifeq (1,$(shell expr \( $(GCCMAJOR) \< 4 \) \| \( $(GCCMAJOR) = 4 \& $(GCCMINOR) \< 6 \)))
IUTEST_CXX_WARN_FLAGS+=-Wno-sign-compare
endif

IUTEST_CXX_WARN_FLAGS+=-Wno-missing-field-initializers

endif
endif
