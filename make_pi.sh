#!/bin/sh
export CFLAGS="-Os -pipe"
make
if test -e distrib/libqdinp2.a
then
    echo 'Making distributable'
    tar -cvzf predist/qdinp2_pi.tar.gz distrib/libqdinp2.a distrib/qdinp2.h
fi
