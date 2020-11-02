#!/bin/sh

cd .ci/osdn

osdn login
./release.sh $VERSION
