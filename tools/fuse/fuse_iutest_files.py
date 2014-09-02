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

def Fuse(root, filename, output_dir):
	output_file = codecs.open(os.path.join(output_dir, filename), 'w', 'utf-8-sig')
	processed_files = sets.Set();
	def ProcessFile(curr, filename, fileset):
		path = os.path.join(root, filename)
		if not os.path.exists(path):
			path = os.path.join(curr, filename)
		
		path = os.path.normpath(path)
		if path in fileset:
			return
		
		find_ifdef = False;
		fileset.add(path)
		for line in codecs.open(path, 'r', 'utf-8-sig'):
			m = INCLUDE_REGEX.match(line)
			if m:
				if find_ifdef:
					s = sets.Set()
					s.add(path)
					ProcessFile(os.path.dirname(path), m.group(1), s)
				else:
					ProcessFile(os.path.dirname(path), m.group(1), fileset)
			else:
				m = IFDEF_REGEX.match(line)
				find_ifdef = bool(m)
				output_file.write(line)
	ProcessFile(root, filename, processed_files)
	output_file.close()

def FuseAll(root, output_dir):
	Fuse(root, 'iutest.hpp', output_dir)

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

