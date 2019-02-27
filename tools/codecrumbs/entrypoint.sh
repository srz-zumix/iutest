#!/bin/sh

set -exu

# codecrumbs -d . -e samples/main.cpp -p 2018
codecrumbs $*
