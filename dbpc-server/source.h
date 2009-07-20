/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
#ifndef SOURCE_H
#define SOURCE_H
#include "source_plugin.h"

/* Sources */
DBPCSource *dbpc_source_new(const char *name,
			    void *connection_start,
			    void *connection_stop,
			    void *get_value, void *set_value);

void dbpc_source_free(DBPCSource * src);

#endif /* SOURCE_H */
