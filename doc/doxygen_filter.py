#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# doxygen_filter.py
#
# Copyright (C) 2015-2016, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

import sys
import os


# main
def main():
    path = sys.argv[1]
    f = open(path)
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

if __name__ == '__main__':
    main()
