#
# eval_line.py
#
# Copyright (C) 2014, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

import sys
import argparse
import re

from argparse import ArgumentParser

# EvalIntAction
class EvalIntAction(argparse.Action):
	def __call__(self, parser, namespace, values, options_string=None):
		setattr(namespace, self.dest, int(eval(values[0])))

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
		'-r'
		, '--repeat'
		, action=EvalIntAction
		, dest = 'repeat'
		, nargs=1
		, help = 'Set eval repeat count.'
		, default = 1
	)
	parser.add_argument(
		'-s'
		, '--start'
		, action=EvalIntAction
		, dest = 'start'
		, nargs=1
		, help = 'Set eval repeat start no.'
		, default = 0
	)
	parser.add_argument(
		'-o'
		, '--output'
		, dest = 'output'
		, help = 'output file path.'
		, default = None
	)
	parser.add_argument(
		'expression'
		, metavar='EXP'
		, help = 'eval expressions'
		, nargs='+'
	)
	if len(sys.argv) <= 1:
		parser.error('invalid number arguments')

	options = parser.parse_args(sys.argv)
	return options

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
	options = parse_command_line()
	define = options.expression[1]
	for a in options.expression[2:]:
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
