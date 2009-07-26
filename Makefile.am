## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = dbpc-server

dbpc_sampledocdir = ${prefix}/doc/dbpc_sample
dbpc_sampledoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS

EXTRA_DIST = $(dbpc_sampledoc_DATA) 

bin_PROGRAMS = \
	dbpc-test

dbpc_test_SOURCES = \
	dbpc-server/dbpc.c\
	dbpc-server/dbpc.h \
	dbpc-server/source_list.c \
	dbpc-server/source_list.h \
	dbpc-server/source_plugin.h \
	dbpc-server/tag.c \
	dbpc-server/tag.h \
	dbpc-server/tag_list.c \
	dbpc-server/tag_list.h \
	dbpc-server/connection.c \
	dbpc-server/connection.h \
	dbpc-server/source.c \
	dbpc-server/source.h \
	dbpc-server/utils.c \
	dbpc-server/utils.h \
	dbpc-server/value.c \
	dbpc-server/value.h

dbpc_test_CFLAGS = \
	-I./dbpc-server \
	-I./dbpc-server/sources \
	-ldl

# Copy all the spec files. Of cource, only one is actually used.
dist-hook:
	for specfile in *.spec; do \
		if test -f $$specfile; then \
			cp -p $$specfile $(distdir); \
		fi \
	done

