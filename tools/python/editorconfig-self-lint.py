#!/usr/bin/env python
#
# editorconfig-lint.py
#
# Copyright (C) 2019, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

import sys
import os

try:
    from configparser import ConfigParser
except ImportError:
    from ConfigParser import SafeConfigParser as ConfigParser


class EditorConfig(object):
    def __init__(self, path):
        self.name = os.path.basename(path)
        self.fp = open(path)
        self.first_head = True

    def readline(self):
        if self.first_head:
            self.first_head = False
            return '[global]\n'
        return self.fp.readline()

    def __iter__(self):
        return self

    def __next__(self):
        line = self.readline()
        if not line:
            raise StopIteration
        return line

    next = __next__  # For Python 2 compatibility.


def main():
    path = sys.argv[1]
    ini = ConfigParser()
    if not os.path.exists(path):
        sys.stderr.write('%s not found...' % path)
        sys.exit(2)
    ini.read_file(EditorConfig(path))
    sys.exit(0)


if __name__ == '__main__':
    main()
