#!/usr/bin/env python
# -*- coding: utf-8 -*-

#
# iutest_compiler_error_test.py
#
# Copyright (C) 2015, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

import sys
import argparse
import re

from argparse import ArgumentParser

class ErrorMessage:
	file = ""
	line = 0
	type = ""
	message = ""
	parent = None
	
	def set_type(self,str):
		s = str.strip()
		if s in {"error", "エラー"}:
			self.type = "error"
		elif s in {"note", "備考"}:
			self.type = "note"
			
	def has_error(self):
		if self.type == "error":
			return True
		elif self.parent:
			return self.parent.has_error()
		return False
	
	def get_error(self):
		if self.type == "error":
			return self
		elif self.parent:
			return self.parent.get_error()
		return None

#
# command line option
def parse_command_line():
	parser = ArgumentParser()
	parser.add_argument(
		'-v'
		, '--version'
		, action='version'
		, version=u'%(prog)s version 0.1'
	)
	parser.add_argument(
		'-c'
		, '--compiler'
		, help = 'set compiler.'
		, default='gcc'
	)
	parser.add_argument(
		'-i'
		, '--infile'
		, help = 'compiler stdout.'
		, default=sys.stdin
	)

	del sys.argv[0]
	options = parser.parse_args(sys.argv)
	return options

#
# parse_gcc
def parse_gcc(options, f):
	re_file = re.compile(r'(\S+):(\d+):(\d+)')
	re_infile = re.compile(r'In file included from (\S+):(\d+):(\d+)')
	re_message = re.compile(r'.*:\d+:\d+: (\S*): (.*)')
	re_expansion = re.compile(r'in expansion of macro')
	msg_list = []
	msg = None
	prev = None
	for line in f:
		m = re_file.match(line)
		if not m:
			m = re_infile.match(line)

		if m:
			if msg:
				msg_list.append(msg)
				prev = msg
			msg = ErrorMessage()
			msg.file = m.group(1)
			msg.line = int(m.group(2))
			msg.type = ""
			n = re_message.match(line)
			if n:
				msg.set_type(n.group(1))
				msg.message += n.group(2)
				if re_expansion.search(msg.message):
					msg.parent = prev
		else:
			if msg:
				msg.message += line
	msg_list.append(msg)
	return msg_list

#
# dump
def dump_msg(m):
	print "%s:%d" % (m.file, m.line)
	print m.type
	print m.message

def dump_list(l):
	for m in l:
		dump_msg(m)

#
# iutest
def iutest(l):
	re_iutest = re.compile(r'IUTEST_TEST_COMPILEERROR\( (.*) \)')
	re_m = None
	c = None
	for msg in l:
		mm = re_iutest.search(msg.message)
		if mm:
			if c:
				raise Exception(re_m.group(0))
			else:
				c = msg
				re_m = mm
		elif c:
			if msg.file in c.file and msg.line == c.line+1 and msg.has_error():
				actual = msg.get_error()
				expect = re_m.group(1).strip('"')
				if actual.message.find(expect):
					c = None
					print re_m.group(0) + ' - OK'
				
#
# parse_output
def parse_output(options):
	l = None
	if options.compiler == 'gcc' or options.compiler == 'g++':
		if options.infile:
			l = parse_gcc(options, options.infile)
		else:
			l = parse_gcc(options, sys.stdin)
	else:
		raise Exception("sorry, %s compiler is not supported", (options.compiler))
	
	#dump_list(l)
	iutest(l)

#
# main
def main():
	options = parse_command_line()
	parse_output(options)
	sys.exit(0)

if __name__ == '__main__':
	main()
