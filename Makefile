#ALL: qdinplib.tar.gz qdinpmlib.tar.gz
#	echo "All created!"
#
#qdinplibcode.tar.gz: Makefile qdinp.c qdinp.h qdinpm.h qdinpm.c
#	tar -czvf qdinplibcode.tar.gz Makefile qdinp.c qdinp.h qdinpm.h qdinpm.c
#
#qdinplib.tar.gz: libqdinplib.a qdinp.h
#	tar -czvf qdinplib.tar.gz libqdinplib.a qdinp.h
#
#qdinpmlib.tar.gz: libqdinpmlib.a qdinpm.h
#	tar -czvf qdinpmlib.tar.gz libqdinpmlib.a qdinpm.h

CC = gcc

# To make for older Unixes (including Coherent), uncomment this next line
#COHFLAGS = -DCOHERENT

distrib/libqdinp2.a: tmp/qdinpm.o
	ar rc distrib/libqdinp2.a tmp/qdinpm.o
	ranlib distrib/libqdinp2.a
	cp source/qdinpm.h distrib/qdinp2.h

tmp/qdinpm.o: source/qdinpm.c source/qdinpm.h
	${CC} ${CFLAGS} ${COHFLAGS}  -c source/qdinpm.c
	mv qdinpm.o tmp/

clean: tmp/qdinpm.o
	cd tmp; rm -f qdinpm.o
