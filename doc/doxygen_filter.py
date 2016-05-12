#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# doxygen_filter.py
#
# Copyright (C) 2015, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

import sys


# main
def main():
	f = open(sys.argv[1])
	n = 0
	if f:
		for line in f:
			sys.stdout.write(line)
			if line.find("//=========================================================") != -1:
				n += 1
				if n == 2:
					print('#include "iutest_config.hpp"')
	f.close()

if __name__ == '__main__':
	main()
