/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */

#include "source_list.h"
#include <stdlib.h>
#include <string.h>


static DBPCSource *dbpc_source_new_empty(void);

DBPCSource *dbpc_source_new(const char *name,
							void *connection_start,
							void *connection_stop,
							void* get_value,
							void *set_value )
{
	DBPCSource *src = dbpc_source_new_empty();
	src->name = strdup (name);
	src->connection_start = connection_start;
	src->connection_stop = connection_stop;
	src->get_value = get_value;
	src->set_value = set_value;
	return src;
}

static DBPCSource *dbpc_source_new_empty(void)
{
	DBPCSource *src = malloc(sizeof(DBPCSource));
	src->name = NULL;
	src->connection_start = NULL;
	src->connection_stop = NULL;
	src->get_value = NULL;
	src->set_value = NULL;
	src->monitor_value = NULL;
	src->next = NULL;
	return src;
}

void dbpc_source_free(DBPCSource * src)
{
	if (src->name != NULL) {
		free (src->name);
	}
	free(src);
}

DBPCConnection * dbpc_connection_new(DBPCSource *src, const char * connection_string) {
	DBPCConnection * cn = malloc(sizeof(DBPCConnection));
	cn->source = src;
	//cn->source->connection_start (cn, connection_string);
	return cn;
}

void dbpc_connection_free (DBPCConnection * cn) {
	free (cn);	
}
