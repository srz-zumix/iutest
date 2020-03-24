#
# Makefile

.PHONY: default clean all iutest internal util listener impl gtest src samples test

IUTEST_HPP=$(wildcard ../../include/*.hpp)
INTERNAL_HPP=$(wildcard ../../include/internal/*.hpp)
UTIL_HPP=$(wildcard ../../include/util/*.hpp)
LISTENER_HPP=$(wildcard ../../include/listener/*.hpp)
IMPL_HPP=$(wildcard ../../include/impl/*.ipp)
GTEST_HPP=$(wildcard ../../include/gtest/*.hpp) $(wildcard ../../include/gtest/switch/*.hpp)
SRC_CPP=$(wildcard ../../src/*.cpp)
SAMPLES=$(wildcard ../../samples/*.cpp)
TESTS=$(wildcard ../../test/*.cpp) $(wildcard ../../test/*.hpp)

SUPPRESS_WHITESPACE_SUB=/indent,/braces,/comments,/newline,/labels,/operators,/parens
SUPPRESS_WHITESPACE=$(subst /,-whitespace/,$(SUPPRESS_WHITESPACE_SUB))
SUPPRESS_BUILD_SUB=/include_what_you_use,/c++11,/c++tr1,/header_guard
SUPPRESS_BUILD=$(subst /,-build/,$(SUPPRESS_BUILD_SUB))
SUPPRESS_READABILITY=-readability/todo,-readability/braces,-readability/function
SUPPRESS_RUNTIME=-runtime/int,-runtime/references,-runtime/string
SUPPRESS=$(SUPPRESS_BUILD),$(SUPPRESS_WHITESPACE),$(SUPPRESS_READABILITY),$(SUPPRESS_RUNTIME)

default: iutest internal impl listener util gtest src samples test
all: clean default

iutest: $(IUTEST_HPP) cpplint.py Makefile
	python cpplint.py --extensions=hpp,cpp --linelength=150 --filter=$(SUPPRESS) $(IUTEST_HPP)

internal: $(INTERNAL_HPP) cpplint.py Makefile
	python cpplint.py --extensions=hpp,cpp --linelength=150 --filter=$(SUPPRESS) $(INTERNAL_HPP)

util: $(UTIL_HPP) cpplint.py Makefile
	python cpplint.py --extensions=hpp,cpp --linelength=150 --filter=$(SUPPRESS) $(UTIL_HPP)

listener: $(LISTENER_HPP) cpplint.py Makefile
	python cpplint.py --extensions=hpp,cpp --linelength=120 --filter=$(SUPPRESS) $(LISTENER_HPP)

impl: $(IMPL_HPP) cpplint.py Makefile
	python cpplint.py --extensions=ipp	   --linelength=150 --filter=$(SUPPRESS) $(IMPL_HPP)

gtest: $(GTEST_HPP) cpplint.py Makefile
	python cpplint.py --extensions=hpp,cpp --linelength=150 --filter=$(SUPPRESS),-build/include $(GTEST_HPP)

src: $(SRC_CPP) cpplint.py Makefile
	python cpplint.py --extensions=hpp,cpp --filter=$(SUPPRESS) $(SRC_CPP)

samples: $(SAMPLES) cpplint.py Makefile
	python cpplint.py --extensions=hpp,cpp --linelength=120 --filter=$(SUPPRESS),-build/namespace,-runtime/printf $(SAMPLES)

test: $(SRC_CPP) cpplint.py Makefile
	python cpplint.py --extensions=hpp,cpp --linelength=150 --filter=$(SUPPRESS),-build/namespace,-build/include $(TESTS)

sider:
	cd ../../ && \
	python test/cpplint/cpplint.py --extensions=hpp,cpp,c,h --linelength=150 --quiet --output vs7 \
		--filter="-build/c++11\
		,-build/c++tr1\
		,-build/header_guard\
		,-build/include_what_you_use\
		,-readability/braces\
		,-readability/todo\
		,-runtime/int\
		,-runtime/references\
		,-runtime/string\
		,-whitespace/braces\
		,-whitespace/comments\
		,-whitespace/indent\
		,-whitespace/newline\
		,-whitespace/operators\
		,-whitespace/parens\
		" --recursive . \

help:
	python cpplint.py

clean:
	rm -rf cpplint.py

cpplint.py:
	# git clone https://github.com/google/styleguide.git cpplint
	# cp cpplint/cpplint/cpplint.py cpplint.py
	git clone https://github.com/cpplint/cpplint.git cpplint
	cp cpplint/cpplint.py cpplint.py
	rm -rf cpplint
