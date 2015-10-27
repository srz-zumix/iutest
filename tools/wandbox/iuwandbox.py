#!/usr/bin/env python
#
# iuwandbox.py
#
# Copyright (C) 2014-2015, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

import os
import sys
import re
import codecs
import argparse
import wandbox

from argparse import ArgumentParser
from wandbox import Wandbox

IUTEST_FUSED_SRC = os.path.join(os.path.dirname(__file__), '../../fused-src/iutest.min.hpp')
IUTEST_INCLUDE_REGEX = re.compile(r'^\s*#\s*include\s*".*iutest\.hpp"')
EXPAND_INCLUDE_REGEX = re.compile(r'^\s*#\s*include\s*"(.*?)"')

#
# command line option
def parse_command_line():
	parser = ArgumentParser()
	parser.add_argument(
		'-v'
		, '--version'
		, action='version'
		, version=u'%(prog)s version 3.0'
	)
	parser.add_argument(
		'--list_compiler'
		, action='store_true'
		, help = 'listup compiler.'
	)
	parser.add_argument(
		'--list_options'
		, metavar='COMPILER'
		, help = 'listup compiler options.'
	)
	parser.add_argument(
		'-c'
		, '--compiler'
		, help = 'compiler select. default=gcc-head'
		, default = 'gcc-head'
	)
	parser.add_argument(
		'-x'
		, '--options'
		, help = 'used options for a compiler.'
		, default = None
	)
	parser.add_argument(
		'--stdin'
		, help = 'set stdin.'
	)
	parser.add_argument(
		'-f'
		, '--compiler_option_raw'
		, metavar='OPTIONS'
		, action='append'
		, help = 'compile-time any additional options.'
	)
	parser.add_argument(
		'-r'
		, '--runtime_option_raw'
		, metavar='OPTIONS'
		, action='append'
		, help = 'runtime-time any additional options.'
	)
	parser.add_argument(
		'-s'
		, '--save'
		, action='store_true'
		, help = 'generate permanent link.'
	)
	parser.add_argument(
		'--permlink'
		, metavar='ID'
		, help = 'get permanent link.'
	)
	parser.add_argument(
		'-o'
		, '--output'
		, metavar='FILE'
		, help = 'output source code.'
	)
	parser.add_argument(
		  '--encoding'
		, help = 'set encoding.'
	)
	parser.add_argument(
		  '--expand_include'
		, action='store_true'
		, help = 'expand include file.'
	)
	parser.add_argument(
		  '--check_config'
		, action='store_true'
		, help = 'check config.'
	)
	parser.add_argument(
		  '--verbose'
		, action='store_true'
		, help = 'verbose.'
	)
	parser.add_argument(
		'code'
		, metavar='CODE'
		, help = 'source code file'
		, nargs='?'
	)
	options, unknown = parser.parse_known_args()
	return options

#
# file open
def file_open(path, mode, encoding):
	if encoding:
		file = codecs.open(path, mode, encoding)
	else:
		file = open(path, mode)
	return file

#
# make code
def make_code(path, encoding, expand, includes):
	code = ''
	file = file_open(path, 'r', encoding)
	for line in file:
		m = IUTEST_INCLUDE_REGEX.match(line)
		if m:
			code += '#include "iutest.hpp"\n'
		else:
			m = EXPAND_INCLUDE_REGEX.match(line)
			if m:
				include_path = os.path.join(os.path.dirname(path), m.group(1))
				if os.path.exists(include_path):
					if expand:
						code += make_code(include_path, encoding, expand, includes)
						code += '// '
					else:
						includes.append(include_path)
			code += line
	file.close()
	return code

#
# check config
def check_config(options):
	if not find_compiler(options.compiler):
		print('Wandbox is not supported compiler [' + options.compiler + ']')
		listup_compiler()
		sys.exit(1)

#
# setup includes
def setup_includes(w, includes, encoding):
	iutest = codecs.open(IUTEST_FUSED_SRC, 'r', 'utf-8-sig')
	w.add_file('iutest.hpp', iutest.read())
	for filepath in includes:
		f = codecs.open(filepath, 'r', encoding)
		w.add_file(filepath, f.read())

#
# run wandbox
def run_wandbox(code, includes, options):
	w = Wandbox()
	w.compiler(options.compiler)
	if options.options:
		w.options(options.options)
	if options.stdin:
		w.stdin(options.stdin)
	if options.compiler_option_raw:
		co = ''
		for opt in options.compiler_option_raw:
			co += opt + '\n'
		co = co.replace('\\n', '\n')
		w.compiler_options(co)
	if options.runtime_option_raw:
		ro = ''
		for opt in options.runtime_option_raw:
			ro += opt + '\n'
		ro = ro.replace('\\n', '\n')
		w.runtime_options(ro)
	if options.save:
		w.permanent_link(options.save)
	if options.verbose:
		w.dump()
	w.code(code)
	setup_includes(w, includes, options.encoding)
	return w.run()

#
# show result
def show_result(r):
	if 'error' in r:
		print(r['error'])
		sys.exit(1)
	if 'compiler_message' in r:
		print('compiler_message:')
		print(r['compiler_message'])
	if 'program_message' in r:
		print('program_message:')
		print(r['program_message'])
	if 'url' in r:
		print('permlink: ' + r['permlink'])
		print('url: ' + r['url'])
	if 'status' in r:
		return int(r['status'])
	return 1

#
# show parameter
def show_parameter(r):
	if 'compiler' in r:
		print('compiler:' + r['compiler'])
	if 'options' in r:
		print('options:' + r['options'])
	if 'compiler-option-raw' in r:
		print('compiler-option-raw:' + r['compiler-option-raw'])
	if 'runtime-option-raw' in r:
		print('runtime-option-raw' + r['runtime-option-raw'])
	if 'created-at' in r:
		print(r['created-at'])

#
# run
def run(options):
	filepath = options.code
	if not os.path.exists(filepath):
		sys.exit(1)
	includes = []
	code = make_code(filepath, options.encoding, options.expand_include, includes)
	if options.output:
		f = file_open(options.output, 'w', options.encoding)
		f.write(code)
		f.close()
	r = run_wandbox(code, includes, options)
	b = show_result(r)
	sys.exit(b)
	
#
# listup compiler
def listup_compiler():
	w = Wandbox()
	r = w.get_compiler_list()
	for d in r:
		if d['language'] == 'C++':
			print(d['name'] + ' (' + d['version'] + ')')

#
# find compiler
def find_compiler(c):
	w = Wandbox()
	r = w.get_compiler_list()
	for d in r:
		if d['language'] == 'C++' and d['name'] == c:
			return True
	return False

#
# listup options
def listup_options(compiler):
	w = Wandbox()
	r = w.get_compiler_list()
	for d in r:
		if d['name'] == compiler:
			if 'switches' in d:
				switches = d['switches']
				for s in switches:
					if 'name' in s:
						if s['default']:
							print(s['name'] + ' (default)')
						else:
							print(s['name'])
					elif 'options' in s:
						print(s['default'] + ' (default)')
						for o in s['options']:
							print('  ' + o['name'])
							
#
# get permlink
def get_permlink(link, output):
	w = Wandbox()
	r = w.get_permlink(link)
	p = r['parameter']
	show_parameter(p)
	print('result:')
	b = show_result(r['result'])
	if output:
		f = open(output, 'w')
		f.write(p['code'])
		f.close()
	sys.exit(b)

#
#
def main():
	options = parse_command_line()
	if options.list_compiler:
		listup_compiler()
	elif options.list_options:
		listup_options(options.list_options)
	elif options.permlink:
		get_permlink(options.permlink, options.output)
	else:
		if options.check_config:
			check_config(options)
		run(options)

if __name__ == '__main__':
	main()
