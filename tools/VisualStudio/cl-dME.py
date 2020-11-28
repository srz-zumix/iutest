#!/usr/bin/env python
#
# cl-dME.py
#
# usage:
#   cl /B1cl-dME.bat main.cpp
#   cl /BXcl-dME.bat main.cpp

from argparse import ArgumentParser
from argparse import SUPPRESS


def main():
    parser = ArgumentParser(add_help=False)
    parser.add_argument(
        '-D',
        dest='defs',
        action='append',
        default=[],
        help=SUPPRESS
    )
    opts, args = parser.parse_known_args()
    for d in opts.defs:
        print(d)


if __name__ == "__main__":
    main()
