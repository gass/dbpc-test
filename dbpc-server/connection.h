/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
#ifndef CONNECTION_H
#define CONNECTION_H
#include "source_plugin.h"

/* Connections */
DBPCConnection *dbpc_connection_new(DBPCSource * src,
				    const char *connection_string);
void dbpc_connection_free(DBPCConnection * cn);
int dbpc_connection_start (DBPCConnection *cn);
int dbpc_connection_stop (DBPCConnection *cn);
#endif /*CONNECTION_H */
