#
# Makefile

.PHONY: all iutest internal

IUTEST_HPP=$(wildcard ../../include/*.hpp)
INTERNAL_HPP=$(wildcard ../../include/internal/*.hpp)

SUPPRESS_WHITESPACE_SUB=/tab,/indent,/braces,/comments,/newline,/labels,/operators,/parens
SUPPRESS_WHITESPACE=$(subst /,-whitespace/,$(SUPPRESS_WHITESPACE_SUB))
SUPPRESS_BUILD=-build/include_what_you_use,-build/c++11,-build/namespaces
SUPPRESS_READABILITY=-readability/todo,-readability/braces
SUPPRESS_RUNTIME=-runtime/int,-runtime/references
SUPPRESS=$(SUPPRESS_BUILD),$(SUPPRESS_WHITESPACE),$(SUPPRESS_READABILITY),$(SUPPRESS_RUNTIME)

all: iutest internal

iutest: $(IUTEST_HPP) cpplint.py Makefile
	python cpplint.py --extensions=hpp,cpp --linelength=150 --filter=$(SUPPRESS) $(IUTEST_HPP)

internal: $(INTERNAL_HPP) cpplint.py Makefile
	python cpplint.py --extensions=hpp,cpp --linelength=110 --filter=$(SUPPRESS) $(INTERNAL_HPP)

cpplint.py:
	git clone https://github.com/google/styleguide.git cpplint
	cp cpplint/cpplint/cpplint.py cpplint.py
	rm -rf cpplint
