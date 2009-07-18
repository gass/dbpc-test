## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" 

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = \
	dbpc-test

dbpc_test_SOURCES = \
	dbpc.c     \
	dbpc.h     \
	source_plugin.c     \
	source_plugin.h     \
	tag.c     \
	tag.h     \
	value.c     \
	value.h     \
	sources/file_test.c     \
	sources/file_test.h     \
	source_list.c     \
	source_list.h     \
	tag_list.h     \
	tag_list.c

SUBDIRS = \
	sources

