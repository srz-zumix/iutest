#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# iutest_incg_test.py
#
# Copyright (C) 2016, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

import os
import sys
import re
import codecs


def main():
    filepath = sys.argv[1]
    incg = os.path.basename(filepath).upper().replace('.', '_')
    f = codecs.open(filepath, 'r', 'utf-8-sig')
    text = f.read()
    f.close()
    r = '\s*#\s*ifndef[/\s]*INCG_IRIS_{0}\S*\s*'.format(incg)
    if not re.search(r, text):
        exit(1)


if __name__ == '__main__':
    main()
