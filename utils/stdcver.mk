ifdef STDFLAG

ifeq ($(findstring gnu, $(STDFLAG)), gnu)
CPP_GNU_EXTENSION=1
else
CPP_GNU_EXTENSION=0
endif

CPPVER_=$(shell echo $(STDFLAG) | grep -o \+\+[0-9][0-9A-Za-z] | sed "s/\+\+//g")

# $(warning CPPVER_ = $(CPPVER_))

ifeq ($(CPPVER_),98)
CPPVER=98
CPPVER_Y=1998
endif

ifeq ($(CPPVER_),03)
CPPVER=03
CPPVER_Y=2003
endif

ifeq ($(CPPVER_),0x)
CPPVER=11
CPPVER_Y=2011
endif

ifeq ($(CPPVER_),11)
CPPVER=11
CPPVER_Y=2011
endif

ifeq ($(CPPVER_),1y)
CPPVER=14
CPPVER_Y=2014
endif

ifeq ($(CPPVER_),14)
CPPVER=14
CPPVER_Y=2014
endif

ifeq ($(CPPVER_),1z)
CPPVER=17
CPPVER_Y=2017
endif

ifeq ($(CPPVER_),17)
CPPVER=17
CPPVER_Y=2017
endif

ifeq ($(CPPVER_),2a)
CPPVER=20
CPPVER_Y=2020
endif

ifeq ($(CPPVER_),20)
CPPVER=20
CPPVER_Y=2020
endif

# $(warning CPPVER = $(CPPVER))
# $(warning CPPVER_Y = $(CPPVER_Y))

endif
