/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */

#include "source_list.h"
#include "source.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

/*
 * The list of available #DBPCSource's.
 */
DBPCSource *SOURCES = NULL;

static void dbpc_source_list_add_aux(DBPCSource * src, DBPCSource * newsrc);
static DBPCSource *dbpc_source_list_find_aux(DBPCSource * src,
					     const char *name);
static void dbpc_source_free_from_list_aux(DBPCSource * source,
					   DBPCSource * src);

void dbpc_source_list_add(DBPCSource * newsrc)
{
	if (SOURCES == NULL) {
		SOURCES = newsrc;
		return;
	} else {
		dbpc_source_list_add_aux(SOURCES, newsrc);
	}
}

static void dbpc_source_list_add_aux(DBPCSource * src, DBPCSource * newsrc)
{
	if (src->next == NULL) {
		src->next = newsrc;
		return;
	} else {
		dbpc_source_list_add_aux(src->next, newsrc);
	}
}

DBPCSource *dbpc_source_list_find(const char *name)
{
	return dbpc_source_list_find_aux(SOURCES, name);
}

static DBPCSource *dbpc_source_list_find_aux(DBPCSource * src, const char *name)
{
	if (src == NULL) {
		return NULL;
	}
	if ((strcmp(src->name, name)) == 0) {
		return src;
	} else {
		return dbpc_source_list_find_aux(src->next, name);
	}
}

void dbpc_source_free_from_list(DBPCSource * src)
{
	dbpc_source_free_from_list_aux(SOURCES, src);
}

static void
dbpc_source_free_from_list_aux(DBPCSource * source, DBPCSource * src)
{
	if (source == src) {
		dbpc_source_free(src);
		source = NULL;
		return;
	} else {
		dbpc_source_free_from_list_aux(source->next, src);
	}
}

void dbpc_source_load (const char *filename) {
	DBPCSource *src;
	void * handle = NULL;
	void * (*get_source_name_id) (void);
	void * (*get_name) (void);
	void * (*get_description) (void);
	char *id;
	char *pchr;
	handle = dlopen(filename, RTLD_LAZY);
	if (!handle) {
		printf ("eeee\n");
		return;
	}
	printf ("eeeea\n");
	src = dbpc_source_new_empty();
	get_source_name_id = dlsym(handle, "get_source_name_id");
	id = get_source_name_id ();
	
	
	pchr = strdup_printf("%s_get_name", id);
	
	get_name = dlsym(handle, pchr);
	free(pchr);
	src->name = strdup(get_name ());
	
	pchr = strdup_printf("%s_get_description", id);
	get_description = dlsym(handle, pchr);
	free (pchr);
	
	
	src->description = strdup (get_description ());
	
	pchr = strdup_printf("%s_connection_start", id);
	src->connection_start = dlsym(handle, pchr);
	free(pchr);
	
	pchr = strdup_printf("%s_connection_stop", id);
	src->connection_stop = dlsym(handle, pchr);
	free(pchr);
	
	dbpc_source_list_add (src);
}
