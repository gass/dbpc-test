## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" 

AM_CFLAGS =\
	 -Wall\
	 -g

SUBDIRS = \
	sources

lib_LTLIBRARIES = \
	libdbpc-source-file.la

libdbpc_source_file_la_SOURCES = \
	source_plugin.h         \
	sources/file_test.c         \
	sources/file_test.h

