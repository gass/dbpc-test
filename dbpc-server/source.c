/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */

#include "source.h"
#include <stdlib.h>
#include <string.h>

/**
 * dbpc_source_new:
 *
 * @name: source's name.
 * @connection_start: pointer to the connection_start function of the plugin.
 * @connection_stop: pointer to the connection_stop function of the plugin.
 * @get_value: pointer to the get_value function of the plugin.
 * @set_value: pointer to the set_value function of the plugin.
 *
 * Creates a new #DBPCSource with all fields filled.
 */
DBPCSource *dbpc_source_new(const char *name,
							void *connection_start,
							void *connection_stop,
							void *get_value,
							void *set_value,
							void *process_pre,
							void *process)
{
	DBPCSource *src = dbpc_source_new_empty();
	src->name = strdup(name);
	src->connection_start = connection_start;
	src->connection_stop = connection_stop;
	src->get_value = get_value;
	src->set_value = set_value;
	src->process_pre = process_pre;
	src->process = process;
	return src;
}

/**
 * dbpc_source_new_empty:
 *
 * Simple function to produce a "NULLED" #DBPCSource.
 */
DBPCSource *dbpc_source_new_empty(void)
{
	DBPCSource *src = malloc(sizeof(DBPCSource));
	src->name = NULL;
	src->description = NULL;
	src->connection_start = NULL;
	src->connection_stop = NULL;
	src->get_value = NULL;
	src->set_value = NULL;
	src->monitor_value = NULL;
	src->process_pre = NULL;
	src->process = NULL;
	src->next = NULL;
	return src;
}

void dbpc_source_free(DBPCSource * src)
{
	if (src->name != NULL) {
		free(src->name);
	}
	if (src->description != NULL) {
		free(src->description);
	}
	free(src);
}
