#
# Makefile

.PHONY: check

HPP=$(wildcard ../../include/*.hpp)

SUPPRESS_WHITESPACE_SUB=/tab,/indent,/braces,/comments,/newline,/labels,/operators,/parens
SUPPRESS_WHITESPACE=$(subst /,-whitespace/,$(SUPPRESS_WHITESPACE_SUB))
SUPPRESS_BUILD=-build/include_what_you_use,-build/c++11
SUPPRESS_READABILITY=-readability/todo
SUPPRESS=$(SUPPRESS_BUILD),$(SUPPRESS_WHITESPACE),$(SUPPRESS_READABILITY)

check: $(HPP) cpplint.py Makefile
	python cpplint.py --extensions=hpp,cpp --linelength=100 --filter=$(SUPPRESS) $(HPP)

cpplint.py:
	git clone https://github.com/google/styleguide.git cpplint
	cp cpplint/cpplint/cpplint.py cpplint.py
	rm -rf cpplint
