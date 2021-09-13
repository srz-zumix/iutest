#
# usegtest.mk
#
# Copyright (C) 2017-2018, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

ifdef GTEST_ROOT

GTEST_ROOT_=$(subst \,/,$(GTEST_ROOT))
ifeq ($(findstring yes, $(shell test -e $(GTEST_ROOT_)/googletest/include && echo -n yes)), yes)
GTEST_GMOCK_ROOT:=${GTEST_ROOT_}
GTEST_ROOT_:=$(GTEST_ROOT_)/googletest
endif

endif

ifdef GMOCK_ROOT

GMOCK_ROOT_=$(subst \,/,$(GMOCK_ROOT))
ifeq ($(findstring yes, $(shell test -e $(GMOCK_ROOT_)/googlemock/include && echo -n yes)), yes)
GTEST_GMOCK_ROOT:=${GMOCK_ROOT_}
GMOCK_ROOT_:=$(GMOCK_ROOT_)/googlemock
endif

ifndef GTEST_ROOT_

ifeq ($(findstring yes, $(shell test -e $(GMOCK_ROOT_)/gtest/include && echo -n yes)), yes)
GTEST_ROOT_:=$(GMOCK_ROOT_)/gtest
endif

ifeq ($(findstring yes, $(shell test -e $(GMOCK_ROOT_)/googletest/include && echo -n yes)), yes)
GTEST_ROOT_:=$(GMOCK_ROOT_)/googletest
endif

endif

endif

#
# Use Google Test
#
ifdef USE_GTEST

ifdef GTEST_ROOT_

GTEST_INC_=-isystem$(GTEST_ROOT_)/include
GTEST_SYSTEM_INCLUDED=1
#GTEST_LIB_=$(GTEST_ROOT_)/make/gtest.a

ifeq ($(findstring yes, $(shell test -e $(GTEST_ROOT_)/make/gtest-all.o && echo -n yes)), yes)

GTEST_LIB_=$(GTEST_ROOT_)/make/gtest-all.o

else

ifeq ($(findstring yes, $(shell test -e $(GTEST_GMOCK_ROOT)/build/lib/libgtest.a && echo -n yes)), yes)

GTEST_LIB_=-L $(GTEST_GMOCK_ROOT)/build/lib/ -lgtest

else

GTEST_LIB_=-lgtest

endif

endif


else

GTEST_INC_=
GTEST_LIB_=-lgtest -lpthread

endif

override LDFLAGS += $(GTEST_LIB_)
override CXXFLAGS += -DIUTEST_USE_GTEST -DIUTEST_HAS_SOCKET=0 $(NO_UNUSED_LOCAL_TYPEDEFS) -Wno-sign-compare $(GTEST_INC_)
ifeq ($(findstring suggest-override, $(CXXFLAGS)), suggest-override)
override CXXFLAGS += -Wno-suggest-override
endif
# override CXXFLAGS += -DGTEST_REMOVE_LEGACY_TEST_CASEAPI_

endif

#
# Use Google Mock
#

ifdef USE_GMOCK

ifdef GTEST_ROOT_

ifndef GMOCK_ROOT_

ifeq ($(findstring yes, $(shell test -e $(GTEST_ROOT_)/../googlemock/include && echo -n yes)), yes)
GMOCK_ROOT_=$(GTEST_ROOT_)/../googlemock
endif

endif

endif


ifdef GMOCK_ROOT_

GMOCK_INC_=-isystem$(GMOCK_ROOT_)/include -isystem$(GTEST_ROOT_)/include
GMOCK_LIB_=$(GMOCK_ROOT_)/make/gmock-all.o $(GMOCK_ROOT_)/make/gtest-all.o
GTEST_SYSTEM_INCLUDED=1

else

GMOCK_INC_=
GMOCK_LIB_=-lgmock -lgtest -lpthread

endif

override LDFLAGS += $(GMOCK_LIB_)
override CXXFLAGS += -DIUTEST_USE_GTEST -DIUTEST_USE_GMOCK -DIUTEST_HAS_SOCKET=0 $(NO_UNUSED_LOCAL_TYPEDEFS) $(GMOCK_INC_)
# override CXXFLAGS += -DGTEST_REMOVE_LEGACY_TEST_CASEAPI_

endif

