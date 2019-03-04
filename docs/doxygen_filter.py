#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# doxygen_filter.py
#
# Copyright (C) 2015-2019, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

import sys
import os
import codecs

def filter(path, encoding):
    f = codecs.open(path, 'r', encoding)
    n = 0
    fname = os.path.basename(path)
    if fname == "iutest_config.hpp":
        n = 2
    if f:
        for line in f:
            sys.stdout.write(line)
            if n < 2:
                if line.find("//=========================================================") != -1:
                    n += 1
                    if n == 2:
                        print('#include "iutest_config.hpp"')
    f.close()


def main():
    path = sys.argv[1]
    try:
        filter(path, 'utf-8-sig')
    except UnicodeDecodeError:
        filter(path, 'utf-8')


if __name__ == '__main__':
    main()
