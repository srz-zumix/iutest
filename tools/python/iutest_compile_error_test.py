#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# iutest_compiler_error_test.py
#
# Copyright (C) 2015, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

import os
import sys
import argparse
import re
import codecs

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
		if s in {"error", u"エラー"}:
			self.type = "error"
		elif s in {"note", u"備考"}:
			self.type = "note"
		elif s in {"warning", u"警告"}:
			self.type = "warning"
		if s in {"error", "エラー"}:
			self.type = "error"
		elif s in {"note", "備考"}:
			self.type = "note"
		elif s in {"warning", "警告"}:
			self.type = "warning"
		else:
			self.type = s
	
	def is_error(self):
		if self.type == "error":
			return True
		return False

	def is_note(self):
		if self.type == "note":
			return True
		return False

	def is_type_none(self):
		if not self.type:
			return True
		return False

	def is_warning(self):
		if self.type == "warning":
			return True
		return False

	def has_error(self):
		if self.type == "error":
			return True
		elif self.parent and self.parent.has_error_parent():
			return True
		elif self.child and self.child.has_error_child():
			return True
		return False
	
	def has_error_parent(self):
		if self.type == "error":
			return True
		elif self.parent:
			return self.parent.has_error()
		return False

	def has_error_parent(self):
		if self.type == "error":
			return True
		elif self.parent:
			return self.parent.has_error_parent()
		return False

	def has_error_child(self):
		if self.type == "error":
			return True
		elif self.child:
			return self.child.has_error_child()
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
		
		if self.parent:
			e = self.parent.get_error_parent()
			if e:
				return e
		if self.child:
			e = self.child.get_error_child()
			if e:
				return e
		return None

	def get_error_parent(self):
		if self.type == "error":
			return self
		elif self.parent:
			return self.parent.get_error_parent()
		return None

	def get_error_child(self):
		if self.type == "error":
			return self
		elif self.child:
			return self.child.get_error_child()
		return None

format_gcc=True
color_prompt=False

#
# command line option
def parse_command_line():
	parser = ArgumentParser()
	parser.add_argument(
		'-v'
		, '--version'
		, action='version'
		, version=u'%(prog)s version 0.2'
	)
	parser.add_argument(
		'-c'
		, '--compiler'
		, help = 'set compiler.'
		, default='gcc'
	)
	if sys.version_info[0] >= 3:
		parser.add_argument(
			'-i'
			, '--infile'
			, type=argparse.FileType('r', encoding='UTF-8')
			, help = 'compiler stdout.'
			, default=sys.stdin
		)
	else:
		parser.add_argument(
			'-i'
			, '--infile'
			, type=argparse.FileType('r')
			, help = 'compiler stdout.'
			, default=sys.stdin
		)

	del sys.argv[0]
	options = parser.parse_args(sys.argv)
	return options

#
# parse_gcc_clang
def parse_gcc_clang(options, f, r_expansion, note_is_child):
	re_fatal = re.compile(r'(\S+)\s*:\s*fatal\s*error\s*.*')
	re_file = re.compile(r'(\S+):(\d+):(\d+)\s*:(.*)')
	re_infile = re.compile(r'In file included from (\S+):(\d+):(\d+)(.*)')
	re_message = re.compile(r'.*:\d+:\d+: (\S*): (.*)')
	re_expansion = re.compile(r_expansion)
	re_declaration = re.compile(r'.*declaration of\s*(.*)')
	msg_list = []
	msg = None
	prev = None
	for line in f:
		if re_fatal.match(line):
			raise Exception(line)

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
			else:
				msg.set_type('')
				msg.message += m.group(4)

			is_child = note_is_child and msg.is_note()
			is_type_none = prev and prev.is_type_none()
			is_declaration = False
			n = re_declaration.match(line)
			if n and prev and prev.message.find(n.group(1)) != -1:
				is_declaration = True
				
			if is_child or is_type_none or is_declaration or re_expansion.search(msg.message):
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
	return parse_gcc_clang(options, f, r'expanded from ', True)

#
# parse_vc
def parse_vc(options, f):
	re_fatal = re.compile(r'(\S+)\s*:\s*fatal\s*error\s*.*')
	re_file = re.compile(r'(\s*)(\S+)\((\d+)\)\s*:\s*(.*)')
	re_message = re.compile(r'.*\(\d+\)\s*: (\S*) (\S*: .*)')
	msg_list = []
	msg = None
	prev = None
	for line in f:
		if re_fatal.match(line):
			raise Exception(line)
			
		m = re_file.match(line)

		if m:
			if msg:
				msg_list.append(msg)
				prev = msg
			msg = ErrorMessage()
			msg.file = m.group(2)
			msg.line = int(m.group(3))
			msg.type = ""
			n = re_message.match(line)
			if n:
				msg.set_type(n.group(1))
				msg.message += n.group(2)
			else:
				msg.set_type('')
				msg.message += m.group(4)
				
			if m.group(1) and prev:
				prev.child = msg
				msg.parent = prev
		else:
			if msg:
				msg.message += '\n'
				msg.message += line
	msg_list.append(msg)
	return msg_list

#
# dump
def dump_msg(m):
	if format_gcc:
		if m.is_type_none():
			print("%s:%d: %s" % (m.file, m.line, m.message))
		else:
			print("%s:%d: %s: %s" % (m.file, m.line, m.type, m.message))
	else:
		if m.parent:
			print("\t%s(%d): %s %s" % (m.file, m.line, m.type, m.message))
		else:
			print("%s(%d): %s %s" % (m.file, m.line, m.type, m.message))

	
def dump_msgs(m):
	if m.parent:
		dump_msgs(m.parent)
	dump_msg(m)

def dump_list(l):
	for m in l:
		if not m.parent:
			print('------------------------------')
		dump_msg(m)
		if not m.child:
			print('------------------------------')

	return True

#
# test_result
def test_result(result, msg, e):
	OKGREEN = '\033[32m'
	WARNING = '\033[33m'
	FAIL    = '\033[31m'
	ENDC    = '\033[0m'
	
	if e:
		msg += ': ' + e.file + ': ' + str(e.line)

	if result:
		if color_prompt:
			print(OKGREEN + '[OK] ' + ENDC + msg)
		else:
			print('[OK] ' + msg)
	else:
		if color_prompt:
			print(FAIL + '[NG] ' + ENDC + msg)
		else:
			print('[NG] ' + msg)

#
# iutest
def iutest(l):
	result = True
	re_iutest = re.compile(r'IUTEST_TEST_COMPILEERROR\( (.*) \)')
	re_m = None
	check = None
	for msg in l:
		if not msg:
			continue

		mm = re_iutest.search(msg.message)
		if mm:
			if msg.parent:
				continue
			if check and not check.checked:
				dump_msg(check)
				dump_msg(msg)
				test_result(False, re_m.group(0), check)
				check = None
				result = False
			else:
				check = msg
				re_m = mm
		elif msg.has_error():
			#print '%s - %d' % (msg.file, msg.line)
			if check and msg.file in check.file and msg.line == check.line+1:
				actual = msg.get_error()
				expect = re_m.group(1).strip('"')
				if not expect or actual.message.find(expect) != -1:
					check.checked = True
					msg.checked = True
					e = None
					test_result(True, re_m.group(0), check)
			elif msg.is_tail() and not msg.is_checked():
				dump_msgs(msg)
				result = False
		elif msg.is_warning():
			dump_msg(msg)

	if check and not check.checked:
		test_result(False, re_m.group(0), check)
		result = False
	return result
#
# parse_output
def parse_output(options):
	global format_gcc
	l = None
	if not options.infile:
		raise Exception("infile null")
	#print(options.infile.encoding)
	f = options.infile
	#f = codecs.getreader('utf-8')(options.infile)
		
	if any(options.compiler.find(s) != -1 for s in ('clang', 'clang++')):
		l = parse_clang(options, f)
	elif any(options.compiler.find(s) != -1 for s in ('gcc', 'g++')):
		l = parse_gcc(options, f)
	elif options.compiler == 'cl':
		format_gcc = False
		l = parse_vc(options, f)
	else:
		raise Exception("sorry, %s compiler is not supported", (options.compiler))
	
	#return dump_list(l)
	return iutest(l)

#
# setup
def setup():
	global color_prompt
	term = os.environ.get('TERM')
	if term:
		if any( term.find(s) for s in ('xterm', 'screen', 'rxvt', 'linux', 'cygwin' ) ):
			color_prompt = True

#
# main
def main():
	options = parse_command_line()
	setup()
	if not parse_output(options):
		sys.exit(1)

if __name__ == '__main__':
	main()
