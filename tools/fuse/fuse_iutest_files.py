#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# fuse_iutest_files.py
#
# Copyright (C) 2014, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

""" fuse_iutest_files.py
fuse_iutest_files.py.py [IUTEST_ROOT_DIR] OUTPUT_DIR
"""

import os
import sys
import sets
import re
import codecs

IUTEST_INCLUDE_DIR = os.path.join(os.path.dirname(__file__), '../../include')
INCLUDE_REGEX = re.compile(r'^\s*#\s*include\s*"(.*iutest.*)"')
IFDEF_REGEX = re.compile(r'^\s*#\s*if\s*defined\s*\(.*\)')
COMMENT_REGEX = re.compile(r'^\s*//.*')
C_COMMENT_BEGIN_REGEX = re.compile(r'^\s*(.*)/\*.*')
C_COMMENT_END_REGEX = re.compile(r'^\s*\*/(.*)')
STRING_REGEX = re.compile(r'.*".*?".*')
EMPTYLINE_REGEX = re.compile(r'^\s*$')

def Fuse(root, filename, output, output_dir, minimum):
	output_file = codecs.open(os.path.join(output_dir, output), 'w', 'utf-8-sig')
	processed_files = sets.Set();
	def ProcessFile(curr, filename, fileset, minimum):
		path = os.path.join(root, filename)
		if not os.path.exists(path):
			path = os.path.join(curr, filename)
		
		path = os.path.normpath(path)
		if path in fileset:
			return
		
		find_ifdef = False;
		c_comment = False;
		fileset.add(path)
		for line in codecs.open(path, 'r', 'utf-8-sig'):
			line = re.sub('/\*.*?\*/', '', line)
			m = INCLUDE_REGEX.match(line)
			if m:
				if find_ifdef:
					s = sets.Set()
					s.add(path)
					ProcessFile(os.path.dirname(path), m.group(1), s, minimum)
				else:
					ProcessFile(os.path.dirname(path), m.group(1), fileset, minimum)
			else:
				m = IFDEF_REGEX.match(line)
				find_ifdef = bool(m)
				if minimum:
					if c_comment:
						m = C_COMMENT_END_REGEX.match(line)
						if m:
							c_comment = False
							if not EMPTYLINE_REGEX.match(m.group(1)):
								output_file.write(m.group(1))
					else:
						m = C_COMMENT_BEGIN_REGEX.match(line)
						if m:
							c_comment = True
							if not EMPTYLINE_REGEX.match(m.group(1)):
								output_file.write(m.group(1))
						elif not EMPTYLINE_REGEX.match(line):
							if not COMMENT_REGEX.match(line):
								line = re.sub('//[\S \t]*', '', line)
								line = line.strip(' \t')
								line = line.rstrip() + '\r\n'
								line = re.sub('^\s*#\s*', '#', line)
								line = re.sub('^\s*#(.+?)[ \t]+', '#\\1 ', line)
								line = re.sub('\s+(".*?")', ' \\1', line)
								if not STRING_REGEX.match(line):
									line = re.sub('[ \t]+', ' ', line)
									line = re.sub('\s+([&|\+\-<>]+)[ \t]+', '\\1', line)
									line = re.sub('\s*([{\+\-\*/%=<>&|]+=)[ \t]*', '\\1', line)
									#line = re.sub('\w\s*([{\+\-\*/%=<>&|!]+)[ \t]*', '\\1', line)
									line = re.sub('\s*,[ \t]*', ',', line)
									line = re.sub('\s*\)', ')', line)
									line = re.sub('\)\s+{', '){', line)
									line = re.sub('\s*\([ \t]*', '(', line)
								output_file.write(line)
				else:
					output_file.write(line)
	ProcessFile(root, filename, processed_files, minimum)
	output_file.close()

def FuseAll(root, output_dir):
	Fuse(root, 'iutest.hpp', 'iutest.hpp', output_dir, False)
	Fuse(root, 'iutest.hpp', 'iutest.min.hpp', output_dir, True)

def main():
	argc = len(sys.argv)
	if argc == 2:
		FuseAll(IUTEST_INCLUDE_DIR, sys.argv[1])
	elif argc == 3:
		FuseAll(os.path.join(sys.argv[1], "include"), sys.argv[2])
	else:
		print __doc__
		sys.exit(1)

if __name__ == '__main__':
	main()

