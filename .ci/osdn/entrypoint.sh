#!/bin/sh

cd .ci/osdn

osdn login
sh release.sh $VERSION
