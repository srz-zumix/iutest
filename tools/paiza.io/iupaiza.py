#!/usr/bin/env python
#
# iupaiza.py
#

import os
import sys
import re
import codecs
import argparse
import paizaio

from argparse import ArgumentParser
from paizaio import PaizaIO

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
		, version=u'%(prog)s version 0.1'
	)
	parser.add_argument(
		'--stdin'
		, help = 'set stdin.'
	)
	parser.add_argument(
		'-o'
		, '--output'
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
		'code'
		, metavar='CODE'
			, help = 'source code file'
		, nargs='?'
	)
	if len(sys.argv) <= 1:
		parser.error('invalid number arguments')
	del sys.argv[0]
	options = parser.parse_args(sys.argv)
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
def make_code(path, encoding, expand):
	code = ''
	file = file_open(path, 'r', encoding)
	for line in file:
		m = IUTEST_INCLUDE_REGEX.match(line)
		if m:
			f = codecs.open(IUTEST_FUSED_SRC, 'r', 'utf-8-sig')
			
			code += '//==================================================================>>>> ' + line
			code += f.read()
			code += '//==================================================================<<<< ' + line
		else:
			if expand:
				m = EXPAND_INCLUDE_REGEX.match(line)
				if m:
					include_path = os.path.join(os.path.dirname(path), m.group(1))
					if os.path.exists(include_path):
						code += make_code(include_path, encoding, expand)
						code += '// '
			code += line
	file.close()
	return code

#
# run paiza
def run_paiza(code, options):
	paiza = PaizaIO()
	paiza.longpoll(True)
	paiza.code(code)
	return paiza.run()

#
# show result
def show_result(r):
	if 'error' in r:
		print r['error']
		sys.exit(1)
	build_result = r['build_result']
	if 'success' in build_result:
		if 'stdout' in r:
			print 'stdout:'
			print r['stdout']
		if 'stderr' in r:
			print 'stderr:'
			print r['stderr']
		if 'time' in r:
			print 'time:'
			print r['time']
		if 'memory' in r:
			print 'memory:'
			print r['memory']
		if 'exit_code' in r:
			return int(r['exit_code'])
	else:
		if 'build_stderr' in r:
			print r['build_stderr']
		if 'build_exit_code' in r:
			return int(r['build_exit_code'])

	return 1

#
# run
def run(options):
	filepath = options.code
	if not os.path.exists(filepath):
		sys.exit(1)
	code = make_code(filepath, options.encoding, options.expand_include)
	if options.output:
		f = file_open(options.output, 'w', options.encoding)
		f.write(code)
		f.close()
	r = run_paiza(code, options)
	b = show_result(r)
	sys.exit(b)

#
#
def main():
	options = parse_command_line()
	run(options)

if __name__ == '__main__':
	main()
