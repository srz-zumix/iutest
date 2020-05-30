#
# function.mk
#
# makefile utils functions
#
# Copyright (C) 2020, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

define is_number
$(shell test '$(1)' -eq '$(1)' 2>/dev/null && echo true || echo false)
endef
