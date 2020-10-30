#!/usr/bin/env python
#
# cl-dME.py
#
# usage:
#   cl /B1cl-dME.bat main.cpp
#   cl /BXcl-dME.bat main.cpp

import os


def main():
    print(os.environ['MSC_CMD_FLAGS'])
    print(os.environ['MSC_IDE_FLAGS'])


if __name__ == "__main__":
    main()
