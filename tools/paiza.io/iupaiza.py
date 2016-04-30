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
	paiza.longpoll_timeout(100)
	paiza.code(code)
	return paiza.run()

#
# show result
def show_result(r):
	if 'error' in r:
		print(r['error'])
		sys.exit(1)
	build_result = r['build_result']
	if 'success' in build_result:
		if 'stdout' in r:
			print('stdout:')
			print(r['stdout'])
		if 'stderr' in r:
			print('stderr:')
			print(r['stderr'])
		if 'time' in r:
			print('time:')
			print(r['time'])
		if 'memory' in r:
			print('memory:')
			print(r['memory'])
		if 'exit_code' in r:
			return int(r['exit_code'])
	else:
		if 'build_stderr' in r:
			print(r['build_stderr'])
		if 'build_exit_code' in r:
			return int(r['build_exit_code'])

	return 1

#
# output code
def output_code(path, code, encoding):
	f = file_open(path, 'w', encoding)
	f.write(code)
	f.close()

predefined_macros = { '__clang__':'1'
					, '_LIBCPP_VERSION':'1101'
					, 'NULL':'0'
					, '__linux__':'1'
					, '__cplusplus':'201402'
					, '__cpp_rvalue_references':'200610'
					, '__has_include':None
					}
#userdefined_macros = { '':'1'
#					}
expands_macros = [ 'IUTEST_IPP_INLINE'
				, 'IUTEST_NULLPTR'
				, 'IUTEST_CXX_CONSTEXPR'
				, 'IUTEST_CXX_CONSTEXPR_OR_CONST'
				, 'IUTEST_CXX_DELETED_FUNCTION'
				, 'IUTEST_CXX_DEFAULT_FUNCTION'
				, 'IUTEST_CXX_EXPLICIT_CONVERSION'
				, 'IUTEST_CXX_NOEXCEPT_SPEC'
				, 'IUTEST_PRAGMA_GCC_WARN_PUSH'
				, 'IUTEST_PRAGMA_GCC_WARN_DISABLE'
				, 'IUTEST_PRAGMA_GCC_WARN_POP'
				, 'IUTEST_ATTRIBUTE_UNUSED_'
				, 'IUTEST_ATTRIBUTE_DEPRECATED_'
				, 'IUTEST_ATTRIBUTE_PURE_'
				, 'IUTEST_ATTRIBUTE_NORETURN_'
				]

# 
clang_has_features = { 'cxx_nullptr':'1'
				, 'cxx_attributes':'1'
				, 'cxx_auto_type':'1' 
				, 'cxx_constexpr':'1'
				, 'cxx_decltype':'1'
				, 'cxx_defaulted_functions':'1'
				, 'cxx_deleted_functions':'1'
				, 'cxx_explicit_conversions':'1'
				, 'cxx_generalized_initializers':'1'
				, 'cxx_lambdas':'1'
				, 'cxx_noexcept':'1'
				, 'cxx_override_control':'1'
				, 'cxx_rtti':'1'
				, 'cxx_rvalue_references':'1'
				, 'cxx_static_assert':'1'
				, 'cxx_strong_enums':'1'
				, 'cxx_unicode_literals':'1'
				, 'cxx_variadic_templates':'1'
				, 'c_generic_selections': '0'
				}

clang_has_include = { '<cxxabi.h>':'1'
					, '<uchar.h>':'1'
					, '<experimental/any>':'0'
					, '<ext/cmath>':'0'
					, '<array>':'1'
					, '<future>':'1'
					, '<ratio>':'1'
					, '<shared_mutex>':'1'
					, '<scoped_allocator>':'1'
					, '<typeindex>':'1'
					, '<type_traits>':'1'
					, '<tr1/tuple>':'0'
					}

#
#
def expand_macro(line, macros):
	dst = ""
	for s in re.split('([\(\):;{} /%+\-=<>!&\|*#]+)', line):
		if s in expands_macros and s in macros:
			if macros[s]:
				dst += macros[s]
		else:
			dst += s
	return dst

#
# 
def append_define(line, depth, macros, unkowns):
	def append(d, v, depth, macros, unkowns):
		d = re.sub('\(.*\)', '', d)
		if any(x == -1 for x in depth):
			unkowns.append(d)
		else:
			macros[d] = v
		return d
	m = re.match("#\s*define (\S+)\s(.+)$", line)
	if m:
		return append(m.group(1), m.group(2), depth, macros, unkowns)
	else:
		m = re.match("#\s*define (\S+)$", line)
		if m:
			return append(m.group(1), None, depth, macros, unkowns)
	return None

#
#
def expand_ppif_macro(expr, macros, unkowns):
	expand = ""
	for s in re.split('(&&|\|\||!)', expr):
		if s == '&&':
			expand += ' and '
		elif s == '||':
			expand += ' or '
		elif s == '!':
			expand += " not "
		else:
			m = re.match("(.*)defined\((.*?)\)(.*)", s)
			if m:
				d = m.group(2)
				if d in unkowns:
					expand += s
				else:
					f = d in macros
					expand += m.group(1) + str(f) + m.group(3)
				continue
			m = re.match("(.*)__has_include\((.*?)\)(.*)", s)
			if m:
				f = m.group(2)
				if f in clang_has_include:
					expand += m.group(1) + clang_has_include[f] + m.group(3)
				else:
					expand += s
				continue
			m = re.match("(.*)__has_feature\((.*?)\)(.*)", s)
			if m:
				f = m.group(2)
				if f in clang_has_features:
					expand += m.group(1) + clang_has_features[f] + m.group(3)
					continue
			for w in re.split('([+\-=<>\(\)]+)', s):
				if re.match('[+\-=<>\(\)]+', w) or w.isspace():
					expand += w
				elif len(w) > 0:
					if w in unkowns:
						expand += s
					elif w in macros:
						expand += expand_ppif_macro(macros[w], macros, unkowns)
					elif w.isdigit():
						expand += w
					else:
						expand += '0'

	expand = expand.replace('0(0)', '0')
	expand = expand.replace('not =', '!=')
	return expand

#
#
def eval_ppif(expr, macros, unkowns):
	expand = expand_ppif_macro(expr, macros, unkowns)
	try:
		if eval(expand):
			return 1
		else:
			return 0
	except Exception, e:
		if not any( x in expand for x in unkowns ):
			if True:
				print(expr)
				print(expand)
				print(e)
		return -1
						
#
#
def check_ppif(ins, expr, macros, unkowns):
	if ins == "if" or ins == "elif":
		return eval_ppif(expr, macros, unkowns)
	elif ins == "ifdef":
		if expr in unkowns:
			return -1
		if expr not in macros:
			return 0
	elif ins == "ifndef":
		if expr in unkowns:
			return -1
		if expr in macros:
			return 0
	return 1

#
#
def check_pp(line, depth, brothers, macros, unkowns):
	m = re.match("#\s*(ifdef|ifndef|if)\s*(.*)$", line)
	if m:
		f = check_ppif(m.group(1), m.group(2), macros, unkowns)
		depth.append(f)
		brothers.append([])
		return all( x != 0 for x in depth ) and f == -1
	m = re.match("#\s*elif(.*)$", line)
	if m:
		brother = brothers[-1]
		brother.append(depth[-1])
		f = 0
		if not any( x == 1 for x in brother):
			f = check_ppif("elif", m.group(1), macros, unkowns)
		depth[-1] = f
		return all( x != 0 for x in depth ) and any(x == -1 for x in brother)
	m = re.match("#\s*else\s*$", line)
	if m:
		brother = brothers[-1]
		f = depth[-1]
		if f == 1 or any(x == 1 for x in brother):
			f = 0
		elif f == 0:
			f = 1
		depth[-1] = f
		return all( x != 0 for x in depth ) and f == -1
	if re.match("#\s*endif", line):
		brother = brothers[-1]
		f = depth.pop()
		b1 = all( x != 0 for x in depth )
		b2 = any(x == -1 for x in brother)
		brothers.pop()
		return b1 and (f == -1 or b2)
	return len(depth) == 0 or all( x != 0 for x in depth )

#
#
def reduction(line):
	line = line.replace('IIUT_', 'II_')
	line = line.replace('II_PP_', 'IP_')
	line = re.sub('\s+', ' ', line)
	line = re.sub('\s$', '', line)
	return line
#
#
def preprocess(code, macros):
	macros = predefined_macros
	unkowns = []
	depth = []
	brother = []
	dst = ""
	for line in code.splitlines():
		# c++ comment
		if re.match('^//.*', line):
			continue
		# if/ifdef/ifndef/elif/endif
		if check_pp(line, depth, brother, macros, unkowns):
			# define
			d = append_define(line, depth, macros, unkowns)
			if d:
				if d in expands_macros:
					continue
			line = expand_macro(line, macros)
			if len(line) > 0:
				line = reduction(line)
				dst += line + "\n"
		
	#for k,v in sorted(macros.items()):
	#	if v == None:
	#		print(k)
	#	else:
	#		print(k + " " + v)
	return dst

#
#
def run_impl(code, options):
	r = run_paiza(code, options)
	b = show_result(r)
	sys.exit(b)

#
# run
def run(options):
	filepath = options.code
	if not os.path.exists(filepath):
		sys.exit(1)
	code = make_code(filepath, options.encoding, options.expand_include)
	if options.output:
		output_code(options.output, code, options.encoding)
	try:
		run_impl(code, options)
	except paizaio.TooLongException, e:
		print(e)
		output = options.output
		if not options.output:
			output = "paizaio-toolong-sourcecode.cpp"
			output_code(output, code, options.encoding)
			print("source code -> " + output)
		try:
			output = os.path.basename(filepath) + ".p"
			macros = { '__clnag__':'1', '_LIBCPP_VERSION':'1101', 'NULL':'0' }
			code = preprocess(code, macros)
			output_code("paizaio-sourcecode.cpp", code, options.encoding)
			run_impl(code, options)
		except paizaio.TooLongException, e:
			print(e)
			sys.exit(1)
		except Exception, e:
			print(e)
			raise
	except:
		raise

#
#
def main():
	options = parse_command_line()
	run(options)

if __name__ == '__main__':
	main()
