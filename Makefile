#
#
#
# Copyright (C) 2018-2020, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE


fused:
	make -C tools/fused

editorconfig-self-lint:
	make -C tools/python editorconfig
