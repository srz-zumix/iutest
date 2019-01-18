#!/usr/bin/env python
#
# editorconfig-lint.py
#
# Copyright (C) 2019, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

import sys

try:
    import configparser
except ImportError:
    import ConfigParser as configparser

def main():
    path = sys.argv[1]
    ini = configparser.SafeConfigParser()
    if not os.path.exists(path):
        sys.stderr.write('%s not found...' % path)
        sys.exit(2)
    ini.read(path)
    sys.exit(0)

if __name__ == '__main__':
    main()
