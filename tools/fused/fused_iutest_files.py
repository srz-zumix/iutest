#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# fuse_iutest_files.py
#
# Copyright (C) 2014-2016, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

""" fuse_iutest_files.py
fuse_iutest_files.py [IUTEST_ROOT_DIR] OUTPUT_DIR
"""

import os
import sys
import re
import codecs

IUTEST_INCLUDE_DIR = os.path.join(os.path.dirname(__file__), '../../include')

class IutestFused:
	INCLUDE_REGEX = re.compile(r'^\s*#\s*include\s*"(.*iutest.*)"')
	IFDEF_REGEX = re.compile(r'^\s*#\s*if(def\s*\S*|\s*defined\s*\(.*\))')
	PREPRO_REGEX = re.compile(r'^\s*#')
	COMMENT_REGEX = re.compile(r'^\s*//.*')
	C_COMMENT_BEGIN_REGEX = re.compile(r'^\s*(.*)/\*.*')
	C_COMMENT_END_REGEX = re.compile(r'^\s*\*/(.*)')
	STRING_REGEX = re.compile(r'(".+?")')
	INCG_REGEX = re.compile(r'^\s*#\s*(ifndef|define|endif)[/\s]*(INCG_\S*)\s*\Z')
	c_comment = False
	store_line = ""

	def IsUnnecessaryIncludeGuard(self, line):
		m = self.INCG_REGEX.match(line)
		if m:
			incg = m.group(2)
			if incg not in { 'INCG_IRIS_IUTEST_HPP_', 'INCG_IRIS_IUTEST_SWITCH_HPP_', 'INCG_IRIS_IUTEST_SPI_HPP_' }:
				#print(incg)
				return True
		return False

	def Minmumize(self, line):
		# if defined -> ifdef
		line = re.sub(r'\s*#\s*if\s*defined\((\S*)\)\s*\Z', r'#ifdef \1', line)
		# if !defined -> ifndef
		line = re.sub(r'\s*#\s*if\s*!defined\((\S*)\)\s*\Z', r'#ifndef \1', line)

		# C comment
		if self.c_comment:
			m = self.C_COMMENT_END_REGEX.match(line)
			if m:
				self.c_comment = False
				line = m.group(1)
			else:
				return ""
		m = self.C_COMMENT_BEGIN_REGEX.match(line)
		if m:
			self.c_comment = True
			line = m.group(1)
		line = line.strip()
		if len(line) == 0:
			return ""

		# C++ comment
		if self.COMMENT_REGEX.match(line):
			return ""
		# include guard
		if self.IsUnnecessaryIncludeGuard(line):
			return ""

		# string store
		str_l = self.STRING_REGEX.findall(line)
		for s in str_l:
			line = line.replace(s, '"@STRING@"', 1)

		# remove comment and strip
		line = re.sub('//[\S \t]*', '', line)
		line = line.strip(' \t')
		# remvoe \r 
		line = line.rstrip()
		line += '\n'
		# remove preprocessor directive unnecessary whitespace
		line = re.sub('^\s*#\s*', '#', line)
		line = re.sub('^\s*#(.+?)[ \t]+', r'#\1 ', line)

		# remove unnecessary whitespace
		line = re.sub('\s+(".*?")', r' \1', line)
		line = re.sub(r'\)\s+>', r')>', line)
		line = re.sub(';[ \t]+', ';', line)
		line = re.sub('[ \t]+', ' ', line)
		line = re.sub('([\w)]+)\s+([&|\+\-<>=\?]+)[ \t]+([^>])', r'\1\2\3', line)
		line = re.sub('\s*([{\+\-\*/%=<>&|!]+=)[ \t]*', r'\1', line)
		line = re.sub('<\s+(\w)', r'<\1', line)
		line = re.sub('\s+:[ \t]+(\w)', r':\1', line)
		line = re.sub('\s*,[ \t]*', ',', line)
		line = re.sub('\s*\)', ')', line)
		line = re.sub('\)\s+{', '){', line)
		#line = re.sub('{\s+return', '{return', line)

		# define HOGE(x) vs define HOGE (x)
		m = re.match('^#define\s+(\w+)\s+(\([^)]*?\))$', line)
		line = re.sub('\s*\([ \t]*', '(', line)
		if m:
			line = re.sub('^#define\s+(\w+)(\([^)]*?\))$', r'#define \1 \2', line)
		else:
			line = re.sub('^#define\s+(\w+\([^)]*?\))(\S+)', r'#define \1 \2', line)

		# string restore
		for s in str_l:
			line = line.replace('"@STRING@"', s, 1)

		line = re.sub('^#define\s+(\w+)=', r'#define \1 =', line)
		return line
	
	def Flush(self, output_file):
		if len(self.store_line) > 0:
			output_file.write(self.store_line)
			output_file.write('\n')
			self.store_line = ""

	def Translate(self, root, filename, output, output_dir, minimum):
		output_file = codecs.open(os.path.join(output_dir, output), 'w', 'utf-8-sig')
		processed_files = set();
		# fused-min not support gtest switch
		if minimum:
			processed_files.add(os.path.normpath(os.path.join(root, "gtest/iutest_switch.hpp")))
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
				m = self.INCLUDE_REGEX.match(line)
				if m:
					self.Flush(output_file)
					include_file = m.group(1)
					if find_ifdef:
						s = set(fileset)
						ProcessFile(os.path.dirname(path), include_file, s, minimum)
					else:
						ProcessFile(os.path.dirname(path), include_file, fileset, minimum)
				else:
					find_ifdef = bool(self.IFDEF_REGEX.match(line))
					if minimum:
						line = self.Minmumize(line)
						if len(line):
							if self.PREPRO_REGEX.match(self.store_line):
								line = line.strip();
								if line.endswith('\\'):
									self.store_line += line.rstrip(r'\\')
								else:
									self.store_line += line
									self.Flush(output_file)
							elif self.PREPRO_REGEX.match(line):
								self.Flush(output_file)
								if line.strip().endswith('\\'):
									self.store_line += line.strip().rstrip(r'\\')
								else:
									output_file.write(line)
							else:
								strip_line = line.strip();
								self.store_line += strip_line
								#if not re.match('.*[{};\(\)<>]$', strip_line):
								#	self.Flush(output_file)
								if re.match('.*(:|IUTEST_CXX_DEFAULT_FUNCTION)$', strip_line):
									self.store_line += " "
					else:
						output_file.write(line)
			self.Flush(output_file)

		ProcessFile(root, filename, processed_files, minimum)
		output_file.close()

def FusedSrc(root, filename, output, output_dir, minimum):
	f = IutestFused()
	f.Translate(root, filename, output, output_dir, minimum)

def FusedAll(root, output_dir):
	FusedSrc(root, 'iutest.hpp', 'iutest.hpp', output_dir, False)
	FusedSrc(root, 'iutest.hpp', 'iutest.min.hpp', output_dir, True)

def main():
	argc = len(sys.argv)
	if argc == 2:
		FusedAll(IUTEST_INCLUDE_DIR, sys.argv[1])
	elif argc == 3:
		FusedAll(os.path.join(sys.argv[1], "include"), sys.argv[2])
	else:
		print(__doc__)
		sys.exit(1)

if __name__ == '__main__':
	main()

