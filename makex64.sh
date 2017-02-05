#!/bin/sh
export CFLAGS="-mtune=generic -Os -pipe"
make
if test -e distrib/libqdinp2.a
then
    echo 'Making Distributable'
    tar -cvzf predist/qdinp2x64.tar.gz distrib/libqdinp2.a distrib/qdinp2.h
fi
