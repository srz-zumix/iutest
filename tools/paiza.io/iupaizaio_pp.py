#!/usr/bin/env python
#
# iupaiza_pp.py
#

import re

predefined_macros = {
					'__clang__': '1',
					'_LIBCPP_VERSION': '1101',
					'NULL': '0',
					'__linux__': '1',
					'__cplusplus': '201402',
					'__cpp_rvalue_references': '200610',
					'__has_include': None
					}
#userdefined_macros = { '': '1'
#					}
expands_macros = [
				'IUTEST_IPP_INLINE',
				'IUTEST_NULLPTR',
				'IUTEST_CXX_CONSTEXPR',
				'IUTEST_CXX_CONSTEXPR_OR_CONST',
				'IUTEST_CXX_DELETED_FUNCTION',
				'IUTEST_CXX_DEFAULT_FUNCTION',
				'IUTEST_CXX_EXPLICIT_CONVERSION',
				'IUTEST_CXX_NOEXCEPT_SPEC',
				'IUTEST_CXX_OVERRIDE',
				'IUTEST_CXX_FINAL',
				'IUTEST_CXX_NOTHROW',
				'IUTEST_PRAGMA_GCC_WARN_PUSH',
				'IUTEST_PRAGMA_GCC_WARN_DISABLE',
				'IUTEST_PRAGMA_GCC_WARN_POP',
				'IUTEST_ATTRIBUTE_UNUSED_',
				'IUTEST_ATTRIBUTE_DEPRECATED_',
				'IUTEST_ATTRIBUTE_PURE_',
				'IUTEST_ATTRIBUTE_NORETURN_'
				]

#
expand_function_macros = [
						'IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN',
						'IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END',
						'IUTEST_PRAGMA_EXTERN_TEMPLATE_WARN_DISABLE_BEGIN',
						'IUTEST_PRAGMA_EXTERN_TEMPLATE_WARN_DISABLE_END',
						'IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_BEGIN',
						'IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_END',
						'IUTEST_PRAGMA_MSC_WARN_PUSH',
						'IUTEST_PRAGMA_MSC_WARN_DISABLE',
						'IUTEST_PRAGMA_MSC_WARN_POP',
						'IUTEST_WORKAROUND_MSC_STLSTREAM_C4250',
						'IUTEST_EXPLICIT_TEMPLATE_TYPE_',
						'IUTEST_APPEND_EXPLICIT_TEMPLATE_TYPE_'
						]

# 
clang_has_features = {
				'cxx_nullptr': '1',
				'cxx_attributes': '1',
				'cxx_auto_type': '1' ,
				'cxx_constexpr': '1',
				'cxx_decltype': '1',
				'cxx_defaulted_functions': '1',
				'cxx_deleted_functions': '1',
				'cxx_explicit_conversions': '1',
				'cxx_generalized_initializers': '1',
				'cxx_lambdas': '1',
				'cxx_noexcept': '1',
				'cxx_override_control': '1',
				'cxx_rtti': '1',
				'cxx_rvalue_references': '1',
				'cxx_static_assert': '1',
				'cxx_strong_enums': '1',
				'cxx_unicode_literals': '1',
				'cxx_variadic_templates': '1',
				'c_generic_selections':  '0'
				}

clang_has_include = {
					'<cxxabi.h>': '1',
#					'<uchar.h>': '1',
					'<uchar.h>': '0',
					'<experimental/any>': '0',
					'<ext/cmath>': '0',
					'<array>': '1',
					'<future>': '1',
					'<ratio>': '1',
					'<shared_mutex>': '1',
					'<scoped_allocator>': '1',
					'<typeindex>': '1',
					'<type_traits>': '1',
					'<tr1/tuple>': '0'
					}

RE_MACRO_SPLIT = re.compile('([\(\):;{} /%+\-=<>!&\|*#]+)')
RE_SPLIT_PAREN = re.compile('([\(\)])')
RE_FUNC_MACRO = re.compile('([\w_]+)\((.*?)\)')
RE_DEFINE = re.compile('#\s*define (\S+)\s*(.*)$')
RE_DEFINE_PARSE = re.compile('(.*)defined\((.*?)\)(.*)')
RE_HAS_INCLUDE = re.compile('(.*)__has_include\((.*?)\)(.*)')
RE_HAS_FEATURE = re.compile('(.*)__has_feature\((.*?)\)(.*)')
RE_SPLIT_OP = re.compile('(&&|\|\||!)')
RE_SYMBOLMARK = re.compile('([+\-=<>\(\)]+)')
RE_PPIF = re.compile('#\s*(ifdef|ifndef|if)\s*(.*)$')
RE_PPELIF = re.compile('#\s*elif(.*)$')
RE_PPELSE = re.compile('#\s*else\s*$')
RE_PPENDIF = re.compile('#\s*endif')
RE_CPP_COMMENT = re.compile('^//.*')

class PaizaPreprocessor:
	macros = predefined_macros
	unkowns = []
	depth = []
	brothers = []


	def __expand_macro(self, line):
		dst = ""
		for s in RE_MACRO_SPLIT.split(line):
			if s in expands_macros and s in self.macros:
				if self.macros[s]:
					dst += self.macros[s]
			else:
				dst += s
		return self.__expand_function_macro(dst)


	def __expand_function_macro(self, line):
		dst = ""
		tokens = []
		prev = ""
		for s in RE_SPLIT_PAREN.split(line):
			if s == '(':
				tokens.append(prev)
			elif s == ')' and len(tokens) > 0:
				tokens[-1] += prev + s
				s = ""
				ss = tokens.pop()
				for m in RE_FUNC_MACRO.finditer(ss):
					d = m.group(1)
					if d in expand_function_macros:
						if d in self.macros and self.macros[d] == None:
							ss = ss.replace(m.group(0), '')
				if len(tokens) > 0:
					tokens[-1] += ss
				else:
					dst += ss
			elif len(tokens) > 0:
				tokens[-1] += prev
			else:
				dst += prev
			prev = s
		for s in tokens:
			dst += s
		dst += prev
		return dst


	def __append_define(self, line):
		def append(d, v, depth, macros, unkowns):
			d = re.sub('\(.*\)', '', d)
			if any(x == -1 for x in depth):
				unkowns.append(d)
			else:
				if len(v) == 0:
					macros[d] = None
				else:
					macros[d] = v
			return d
		m = RE_DEFINE.match(line)
		if m:
			return append(m.group(1), m.group(2), self.depth, self.macros, self.unkowns)
		return None

	def __expand_ppif_macro(self, expr):
		expand = ""
		for s in RE_SPLIT_OP.split(expr):
			if s == '&&':
				expand += ' and '
			elif s == '||':
				expand += ' or '
			elif s == '!':
				expand += " not "
			else:
				m = RE_DEFINE_PARSE.match(s)
				if m:
					d = m.group(2)
					if d in self.unkowns:
						expand += s
					else:
						f = d in self.macros
						expand += m.group(1) + str(f) + m.group(3)
					continue
				m = RE_HAS_INCLUDE.match(s)
				if m:
					f = m.group(2)
					if f in clang_has_include:
						expand += m.group(1) + clang_has_include[f] + m.group(3)
					else:
						expand += s
					continue
				m = RE_HAS_FEATURE.match(s)
				if m:
					f = m.group(2)
					if f in clang_has_features:
						expand += m.group(1) + clang_has_features[f] + m.group(3)
						continue
				for w in RE_SYMBOLMARK.split(s):
					if RE_SYMBOLMARK.match(w) or w.isspace():
						expand += w
					elif len(w) > 0:
						if w in self.unkowns:
							expand += s
						elif w in self.macros:
							expand += self.__expand_ppif_macro(self.macros[w])
						elif w.isdigit():
							expand += w
						else:
							expand += '0'

		expand = expand.replace('0(0)', '0')
		expand = expand.replace('not =', '!=')
		return expand


	def __eval_ppif(self, expr):
		expand = self.__expand_ppif_macro(expr)
		try:
			if eval(expand):
				return 1
			else:
				return 0
		except Exception, e:
			if not any( x in expand for x in self.unkowns ):
				if True:
					print(expr)
					print(expand)
					print(e)
			return -1


	def __check_ppif(self, ins, expr):
		if ins == "if" or ins == "elif":
			return self.__eval_ppif(expr)
		elif ins == "ifdef":
			if expr in self.unkowns:
				return -1
			if expr not in self.macros:
				return 0
		elif ins == "ifndef":
			if expr in self.unkowns:
				return -1
			if expr in self.macros:
				return 0
		return 1


	def __check_pp(self, line):
		m = RE_PPIF.match(line)
		if m:
			f = self.__check_ppif(m.group(1), m.group(2))
			self.depth.append(f)
			self.brothers.append([])
			return all( x != 0 for x in self.depth ) and f == -1
		m = RE_PPELIF.match(line)
		if m:
			brother = self.brothers[-1]
			brother.append(self.depth[-1])
			f = 0
			if not any( x == 1 for x in brother):
				f = self.__check_ppif("elif", m.group(1))
			self.depth[-1] = f
			return all( x != 0 for x in self.depth ) and any(x == -1 for x in brother)
		m = RE_PPELSE.match(line)
		if m:
			brother = self.brothers[-1]
			f = self.depth[-1]
			if f == 1 or any(x == 1 for x in brother):
				f = 0
			elif f == 0:
				f = 1
			self.depth[-1] = f
			return all( x != 0 for x in self.depth ) and f == -1
		if RE_PPENDIF.match(line):
			brother = self.brothers[-1]
			f = self.depth.pop()
			b1 = all( x != 0 for x in self.depth )
			b2 = any(x == -1 for x in brother)
			self.brothers.pop()
			return b1 and (f == -1 or b2)
		return len(self.depth) == 0 or all( x != 0 for x in self.depth )


	def __reduction(self, line):
		line = line.replace('IIUT_', 'II_')
		line = line.replace('II_PP_', 'IP_')
		line = line.replace('IUTEST_UNUSED_VAR', '(void)')
		line = re.sub('\s+', ' ', line)
		line = re.sub('\s$', '', line)
		return line


	def preprocess(self, code, macros):
		dst = ""
		for line in code.splitlines():
			# c++ comment
			if RE_CPP_COMMENT.match(line):
				continue
			# if/ifdef/ifndef/elif/endif
			if self.__check_pp(line):
				# define
				d = self.__append_define(line)
				if d:
					if d in expands_macros or d in expand_function_macros:
						continue
					if d in [ 'IUTEST_UNUSED_VAR' ]:
						continue
				line = self.__expand_macro(line)
				if len(line) > 0:
					line = self.__reduction(line)
					dst += line + "\n"
		return dst
