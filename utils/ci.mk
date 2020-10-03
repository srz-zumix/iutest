#
# ci.mk
#
# Copyright (C) 2017-2020, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

ifneq ($(CI),)
CI=true
endif

ifdef AZURE_HTTP_USER_AGENT
CI=true
endif
