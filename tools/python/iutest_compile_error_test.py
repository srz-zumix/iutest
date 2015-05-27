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
	child = None
	checked = False
	
	def set_type(self,str):
		s = str.strip()
		if s in {"error", "エラー"}:
			self.type = "error"
		elif s in {"note", "備考"}:
			self.type = "note"
		elif s in {"warning", "警告"}:
			self.type = "warning"
	
	def is_error(self):
		if self.type == "error":
			return True
		return False

	def is_note(self):
		if self.type == "note":
			return True
		return False

	def is_warning(self):
		if self.type == "warning":
			return True
		return False

	def has_error(self):
		if self.type == "error":
			return True
		elif self.parent:
			return self.parent.has_error()
		return False
	
	def is_checked(self):
		if self.checked:
			return True
		elif self.parent:
			return self.parent.is_checked()
		return False

	def is_tail(self):
		if self.child:
			return False
		return True
	
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
# parse_gcc_clang
def parse_gcc_clang(options, f, r_expansion, note_is_child):
	re_file = re.compile(r'(\S+):(\d+):(\d+)')
	re_infile = re.compile(r'In file included from (\S+):(\d+):(\d+)')
	re_message = re.compile(r'.*:\d+:\d+: (\S*): (.*)')
	re_expansion = re.compile(r_expansion)
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
				is_child = note_is_child and msg.is_note()
				if is_child or re_expansion.search(msg.message):
					prev.child = msg
					msg.parent = prev
		else:
			if msg:
				msg.message += '\n'
				msg.message += line
	msg_list.append(msg)
	return msg_list

#
# parse_gcc
def parse_gcc(options, f):
	return parse_gcc_clang(options, f, r'in expansion of macro', False)

#
# parse_clang
def parse_clang(options, f):
	return parse_gcc_clang(options, f, r'expanded from macro', True)

#
# dump
def dump_msg(m):
	print "%s:%d: %s: %s" % (m.file, m.line, m.type, m.message)
	
def dump_msgs(m):
	if m.parent:
		dump_msgs(m.parent)
	dump_msg(m)

def dump_list(l):
	for m in l:
		if not m.parent:
			print '------------------------------'
		dump_msg(m)
		if not m.child:
			print '------------------------------'

	return True

#
# test_result
def test_result(result, str):
	OKGREEN = '\033[32m'
	WARNING = '\033[33m'
	FAIL    = '\033[31m'
	ENDC    = '\033[0m'

	if result:
		print OKGREEN + '[OK] ' + ENDC + str
	else:
		print FAIL + '[NG] ' + ENDC + str

#
# iutest
def iutest(l):
	result = True
	re_iutest = re.compile(r'IUTEST_TEST_COMPILEERROR\( (.*) \)')
	re_m = None
	check = None
	for msg in l:
		if not msg.message:
			continue

		mm = re_iutest.search(msg.message)
		if mm:
			if msg.parent:
				continue
			if check:
				dump_msg(check)
				test_result(False, re_m.group(0))
				check = None
				result = False
			else:
				check = msg
				re_m = mm
		elif msg.has_error():
			if check and msg.file in check.file and msg.line == check.line+1:
				actual = msg.get_error()
				expect = re_m.group(1).strip('"')
				if actual.message.find(expect):
					check = None
					e = None
					msg.checked = True
					test_result(True, re_m.group(0))
			elif msg.is_tail() and not msg.is_checked():
				dump_msgs(msg)
				result = False
		elif msg.is_warning():
			dump_msg(msg)

	if check:
		test_result(False, re_m.group(0))
		result = False
	return result
#
# parse_output
def parse_output(options):
	l = None
	if not options.infile:
		raise Exception("infile null")
		
	if options.compiler == 'gcc' or options.compiler == 'g++':
		l = parse_gcc(options, options.infile)
	elif options.compiler == 'clang' or options.compiler == 'clang++':
		l = parse_clang(options, options.infile)
	else:
		raise Exception("sorry, %s compiler is not supported", (options.compiler))
	
	#return dump_list(l)
	return iutest(l)

#
# main
def main():
	options = parse_command_line()
	if not parse_output(options):
		sys.exit(1)

if __name__ == '__main__':
	main()
