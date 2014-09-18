#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# iuwandbox.py
#

import os
import sys
import re
import codecs
import argparse
import pywandbox

from argparse import ArgumentParser
from pywandbox import Wandbox

IUTEST_FUSED_SRC = os.path.join(os.path.dirname(__file__), '../../fused-src/iutest.min.hpp')
IUTEST_INCLUDE_REGEX = re.compile(r'^\s*#\s*include\s*".*iutest\.hpp"')

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
		'--list_compiler'
		, action='store_true'
		, help = 'Listup compiler.'
	)
	parser.add_argument(
		'--list_options'
		, help = 'Listup compiler options.'
	)
	parser.add_argument(
		'-c'
		, '--compiler'
		, help = 'Compiler select.'
		, default = 'gcc-head'
	)
	parser.add_argument(
		'-x'
		, '--options'
		, help = 'Used options for a compiler.'
	)
	parser.add_argument(
		'--stdin'
		, help = 'Set stdin.'
	)
	parser.add_argument(
		'-f'
		, '--compiler_option_raw'
		, action='append'
		, help = 'Compile-time any additional options.'
	)
	parser.add_argument(
		'-r'
		, '--runtime_option_raw'
		, action='append'
		, help = 'Runtime-time any additional options.'
	)
	parser.add_argument(
		'-s'
		, '--save'
		, action='store_true'
		, help = 'Generate permanent link.'
	)
	parser.add_argument(
		'--permlink'
		, help = 'Get permanent link.'
	)
	parser.add_argument(
		'-o'
		, '--output'
		, help = 'Get permanent link code.'
	)
	parser.add_argument(
		'code'
		, metavar='CODE'
		, help = 'Source code file'
		, nargs='?'
	)
	if len(sys.argv) <= 1:
		parser.error('invalid number arguments')
	del sys.argv[0]
	options = parser.parse_args(sys.argv)
	return options

#
# make code
def make_code(path):
	code = ''
	file = open(path, 'r')
	for line in file:
		m = IUTEST_INCLUDE_REGEX.match(line)
		if m:
			f = codecs.open(IUTEST_FUSED_SRC, 'r', 'utf-8-sig')
			
			code += '//==================================================================>>>> ' + line
			code += f.read()
			code += '//==================================================================<<<< ' + line
		else:
			code += line
	file.close()
	return code

#
# run wandbox
def run_wandbox(code, options):
	w = Wandbox()
	w.code(code)
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
	return w.run()

#
# show result
def show_result(r):
	if 'error' in r:
		print r['error']
		sys.exit(1)
	if 'compiler_message' in r:
		print 'compiler_message:'
		print r['compiler_message']
	if 'program_message' in r:
		print 'program_message:'
		print r['program_message']
	if 'url' in r:
		print 'permlink: ' + r['permlink']
		print 'url: ' + r['url']
	return int(r['status'])

#
# show parameter
def show_parameter(r):
	if 'compiler' in r:
		print 'compiler:' + r['compiler']
	if 'options' in r:
		print 'options:' + r['options']
	if 'compiler-option-raw' in r:
		print 'compiler-option-raw:' + r['compiler-option-raw']
	if 'runtime-option-raw' in r:
		print 'runtime-option-raw' + r['runtime-option-raw']
	if 'created-at' in r:
		print r['created-at']

#
# run
def run(options):
	filepath = options.code
	if not os.path.exists(filepath):
		sys.exit(1)
	code = make_code(filepath)
	r = run_wandbox(code, options)
	b = show_result(r)
	sys.exit(b)
	
#
# listup compiler
def listup_compiler():
	w = Wandbox()
	r = w.get_compiler_list()
	for d in r:
		if d['language'] == 'C++':
			print d['name'] + ' (' + d['version'] + ')' 

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
							print s['name'] + ' (default)'
						else:
							print s['name']
					elif 'options' in s:
						print s['default'] + ' (default)'
						for o in s['options']:
							print '  ' + o['name']
							
#
# get permlink
def get_permlink(link, output):
	w = Wandbox()
	r = w.get_permlink(link)
	p = r['parameter']
	show_parameter(p)
	print 'result:'
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
		run(options)

if __name__ == '__main__':
	main()
