#
# eval_line.py
#
# Copyright (C) 2014, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

import sys
import optparse
import re

from optparse import OptionParser

usage = u'%prog [Args] [Options]\nDetailed options -h or --help\n\nArgs: eval expression'
version = u'%prog 0.1'

#
# command line option
def parse_command_line():
	parser = OptionParser(usage=usage, version=version)
	parser.add_option(
		'-r'
		, '--repeat'
		, type = 'int'
		, dest = 'repeat'
		, help = 'Set eval repeat count.'
		, default = 1
	)
	parser.add_option(
		'-s'
		, '--start'
		, type = 'int'
		, dest = 'start'
		, help = 'Set eval repeat start no.'
		, default = 0
	)
	parser.add_option(
		'-o'
		, '--output'
		, type = 'str'
		, dest = 'output'
		, help = 'output file path.'
		, default = None
	)
	if len(sys.argv) <= 1:
		parser.error('invalid number arguments')

	options, args = parser.parse_args(sys.argv)
	return options, args

def eval_line(r, define, line):
	m = r.finditer(define)
	if m == None:
		return define
	else:
		out = define
		for e in m:
			out = out.replace( e.group(0), str(eval(e.group(1))) )
		return out

def main():
	re_eval = re.compile(r'\${([^}]+)}')
	options, args = parse_command_line()
	define = args[1]
	for a in args[2:]:
		define += ' ' + a

	output = options.output
	if output == None:
		for line in range(options.repeat):
			print eval_line(re_eval, define, line+options.start)
	else:
		file = open(output, 'w')
		for line in range(options.repeat):
			file.write( eval_line(re_eval, define, line+options.start) )
			file.write( '\n' )
		file.close()


if __name__ == '__main__':
	main()
