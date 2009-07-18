/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */

#include "source_list.h"
#include "source_plugin.h"
#include <stdlib.h>
#include <string.h>

/*
 * The list of available #DBPCSource's.
 */
DBPCSource * SOURCES = NULL;


static void dbpc_source_list_add_aux (DBPCSource *src, DBPCSource *newsrc);
static DBPCSource *dbpc_source_list_find_aux (DBPCSource *src, const char *name);
static void dbpc_source_free_from_list_aux (DBPCSource *source, DBPCSource *src);

void dbpc_source_list_add (DBPCSource *newsrc) {
	if (SOURCES == NULL) {
		SOURCES = newsrc;
		return;
	}
	else {
		dbpc_source_list_add_aux (SOURCES, newsrc);
	}
}

static void dbpc_source_list_add_aux (DBPCSource *src, DBPCSource *newsrc) {
	if (src->next == NULL) {
		src->next = newsrc;
		return;
	}
	else {
		dbpc_source_list_add_aux (src->next, newsrc);
	}
}

DBPCSource *dbpc_source_list_find (const char *name) {
	return dbpc_source_list_find_aux (SOURCES, name);
}

static DBPCSource *dbpc_source_list_find_aux (DBPCSource *src, const char *name) {
	if (src == NULL) {
		return NULL;
	}
	if ((strcmp (src->name, name)) == 0) {
		return src;
	}
	else {
		return dbpc_source_list_find_aux (src->next, name);
	}
}


void dbpc_source_free_from_list (DBPCSource *src) {
	dbpc_source_free_from_list_aux (SOURCES, src);
}

static void dbpc_source_free_from_list_aux (DBPCSource *source, DBPCSource *src) {
	if (source == src) {
		dbpc_source_free (src);
		source = NULL;
		return;
	}
	else {
		dbpc_source_free_from_list_aux (source->next, src);
	}
}
