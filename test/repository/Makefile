#
#
#
# Copyright (C) 2020, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE

default: check-fullpath check-remote-crlf

check-fullpath:
	! find ../../projects -type f -print0 | xargs -0 grep '[d-zD-Z]:\\.*'

check-remote-crlf:
	! git grep --cached -I -l -P '\r'