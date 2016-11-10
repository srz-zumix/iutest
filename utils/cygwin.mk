ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
IUTEST_MKFLAG_CYGWIN=1
else
IUTEST_MKFLAG_CYGWIN=0
endif

