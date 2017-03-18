#!/usr/bin/make
#
# Doxygen special commands checker
#
# Usage: make -C DoxygenCommandCheck.mk ROOT=<root-path> [ADD_COMMANDS=<additional commands>]
#
# Copyright (C) 2017, Takazumi Shirayanagi\n
# This software is released under the new BSD License,
# see LICENSE
#

# doxygen special commands list (v1.18.13)
DOXYGEN_COMMAND_LIST={ \
	} \
	a \
	addindex \
	addtogroup \
	anchor \
	arg \
	attention \
	author \
	authors \
	b \
	brief \
	bug \
	c \
	callergraph \
	callgraph \
	category \
	cite \
	class \
	code \
	cond \
	copybrief \
	copydetails \
	copydoc \
	copyright \
	date \
	def \
	defgroup \
	deprecated \
	details \
	diafile \
	dir \
	docbookonly \
	dontinclude \
	dot \
	dotfile \
	e \
	else \
	elseif \
	em \
	endcode \
	endcond \
	enddocbookonly \
	enddot \
	endhtmlonly \
	endif \
	endinternal \
	endlatexonly \
	endlink \
	endmanonly \
	endmsc \
	endparblock \
	endrtfonly \
	endsecreflist \
	endverbatim \
	enduml \
	endxmlonly \
	enum \
	example \
	exception \
	extends \
	f$ \
	f[ \
	f] \
	f{ \
	f} \
	file \
	fn \
	headerfile \
	hidecallergraph \
	hidecallgraph \
	hideinitializer \
	htmlinclude \
	htmlonly \
	idlexcept \
	if \
	ifnot \
	image \
	implements \
	include \
	includedoc \
	includelineno \
	ingroup \
	internal \
	invariant \
	interface \
	latexinclude \
	latexonly \
	li \
	line \
	link \
	mainpage \
	manonly \
	memberof \
	msc \
	mscfile \
	n \
	name \
	namespace \
	nosubgrouping \
	note \
	overload \
	p \
	package \
	page \
	par \
	paragraph \
	param \
	parblock \
	post \
	pre \
	private \
	privatesection \
	property \
	protected \
	protectedsection \
	protocol \
	public \
	publicsection \
	pure \
	ref \
	refitem \
	related \
	relates \
	relatedalso \
	relatesalso \
	remark \
	remarks \
	result \
	return \
	returns \
	retval \
	rtfonly \
	sa \
	secreflist \
	section \
	see \
	short \
	showinitializer \
	since \
	skip \
	skipline \
	snippet \
	snippetdoc \
	snippetlineno \
	startuml \
	struct \
	subpage \
	subsection \
	subsubsection \
	tableofcontents \
	test \
	throw \
	throws \
	todo \
	tparam \
	typedef \
	union \
	until \
	var \
	verbatim \
	verbinclude \
	version \
	vhdlflow \
	warning \
	weakgroup \
	xmlonly \
	xrefitem \
#	$ \
#	@ \
#	\ \
#	& \
#	~ \
#	< \
#	> \
#	# \
#	% \
#	" \
#	. \
#	:: \
#	| \
#	-- \
#	--- \

DOXYGEN_COMMANDS=$(shell echo ${DOXYGEN_COMMAND_LIST} | sed -e 's/\([\S]*\)\s\([\S]*\)/\1|\2/g')
ifdef ADD_COMMANDS
DOXYGEN_COMMANDS:=${DOXYGEN_COMMANDS}$(shell echo '|${ADD_COMMANDS}' | sed -e 's/\s\([\S]*\)/|\1/g' -e 's/\[/\\[/g' -e 's/\]/\\]/g')
endif
ifneq ("$(wildcard $(ROOT))","")
FILELIST=$(shell find ${ROOT} -type f -name '*.hpp')
FILELIST+=$(shell find ${ROOT} -type f -name '*.h')
FILELIST+=$(shell find ${ROOT} -type f -name '*.ipp')
FILELIST+=$(shell find ${ROOT} -type f -name '*.c')
FILELIST+=$(shell find ${ROOT} -type f -name '*.cpp')
else
ROOT_PATH_NOT_EXIST=1
endif

ifneq ($(FILELIST),)
NOMATCHS=$(shell grep -aozP '/\*\*[\s\S]*?\*/' ${FILELIST} | grep -aoP '\s@[\S]*?\s' | grep -avP '.*@(${DOXYGEN_COMMANDS})\s.*' | sort -bu)
NOMATCHS+=$(shell grep -aonP '//!.*' ${FILELIST} | grep -aoP '\s@[\S]*' | grep -avP '.*@(${DOXYGEN_COMMANDS})' | sort -bu)
endif

default: doxygen-command-typo-check

doxygen-command-typo-check:
#	@echo '${DOXYGEN_COMMANDS}'
ifdef ROOT_PATH_NOT_EXIST
	@echo '${ROOT}: No such file or directory'
	@false
endif
ifeq ($(strip $(NOMATCHS)),)
	@true
else
	@echo '${NOMATCHS}' | sed -e 's/\s/\n/g' -e 's/\(\S\)\n/\1\\\\s\n/g' -e 's/\[/\\\\[/g' -e 's/\]/\\\\]/g' | sort -bu | xargs -n1 grep ${FILELIST} -ne
	@false
endif
