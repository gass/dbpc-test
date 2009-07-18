/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */

#include "source_plugin.h"
#include <stdlib.h>



static DBPCSource *dbpc_source_new_empty(void);

DBPCSource *dbpc_source_new(void)
{
	DBPCSource *src = dbpc_source_new_empty();
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
	return src;
}

void dbpc_source_free(DBPCSource * src)
{
	free(src);
}
