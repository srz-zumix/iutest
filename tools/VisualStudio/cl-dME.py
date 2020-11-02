#!/usr/bin/env python
#
# cl-dME.py
#
# usage:
#   cl /B1cl-dME.bat main.cpp
#   cl /BXcl-dME.bat main.cpp

import os
from argparse import ArgumentParser
from argparse import SUPPRESS


class DefinePrinter:
    def __init__(self):
        self.parser = ArgumentParser(add_help=False)
        self.parser.add_argument(
            '-D',
            dest='defs',
            action='append',
            default=[],
            help=SUPPRESS
        )

    def printto(self, key):
        print(key)
        if os.environ.has_key(key):
            opts, args = self.parser.parse_known_args(os.environ[key])
            for d in opts.defs:
                print(d)
            print(opts)
            print(args)


def main():
    printer = DefinePrinter()
    printer.printto('MSC_CMD_FLAGS')
    printer.printto('MSC_IDE_FLAGS')


if __name__ == "__main__":
    main()
