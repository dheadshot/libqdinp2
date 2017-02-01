#!/bin/sh
export CFLAGS="-march=i486 -mtune=i686 -Os -pipe"
make
if test -e distrib/libqdinp2.a
then
    tar -cvzf predist/qdinp2x86.tar.gz distrib/libqdinp2.a distrib/qdinp2.h
fi
