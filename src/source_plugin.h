/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
#ifndef SOURCE_PLUGIN_H
#define SOURCE_PLUGIN_H
#include "value.h"


typedef struct _DBPCConnection DBPCConnection;

typedef struct _DBPCSource DBPCSource;

/**
 * DBPCSource:
 *
 * @name: source name.
 * @connection_start: function that startes the communication.
 * @connection_stop: function to stop the communication.
 * @get_value: function that retrieves a value from the source.
 * @set_value: function that sets a value to the source.
 * @monitor: function that monitors a variable change.
 */
struct _DBPCSource {
	char *name;
	 DBPCConnection(*connection_start) (const char *connection_string);
	void (*connection_stop) (DBPCConnection * cn);
	int (*get_value) (DBPCConnection * cn, const char *address,
			  DBPCValue * value);
	int (*set_value) (DBPCConnection * cn, const char *address,
			  DBPCValue * value);
	int (*monitor_value) (DBPCConnection * cn, const char *address,
			      DBPCValue * value);
};

DBPCSource *dbpc_source_new(void);
void dbpc_source_free(DBPCSource * src);

#endif				/* SOURCE_PLUGIN_H */
