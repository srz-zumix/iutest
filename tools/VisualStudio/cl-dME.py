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
    def __init__():
        self.parser = ArgumentParser(add_help=False)
        self.parser.add_argument(
            '-D',
            dest='defs'
            action='append',
            default=[],
            help=SUPPRESS
        )

    def print(self, key):
        if key in os.environ:
            opts, args = self.parser.parse_known_args(os.environ[key])
            for d in opts.defs:
                print(d)


def main():
    printer = DefinePrinter()
    printer.print('MSC_CMD_FLAGS')
    printer.print('MSC_IDE_FLAGS')


if __name__ == "__main__":
    main()
