/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
#ifndef SOURCE_PLUGIN_H
#define SOURCE_PLUGIN_H
#include "value.h"

enum connection_status { OK = 1, ERROR };

typedef struct _DBPCConnection DBPCConnection;
typedef struct _DBPCSource DBPCSource;

/**
 * DBPCConnection:
 * @fd file descriptor handler.
 * @source Source plugin used for the connection.
 *
 * The DBPC connection handler.
 */
struct _DBPCConnection {
	int fd;
	int status;
	DBPCSource *source;
};

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
	void (*connection_start) (DBPCConnection * cn, const char *filename);
	void (*connection_stop) (DBPCConnection * cn);
	int (*get_value) (DBPCConnection * cn, const char *address,
			  DBPCValue * value);
	int (*set_value) (DBPCConnection * cn, const char *address,
			  DBPCValue * value);
	int (*monitor_value) (DBPCConnection * cn, const char *address,
			      DBPCValue * value);
	DBPCSource *next;
};

/* Sources */
DBPCSource *dbpc_source_new(const char *name,
			    void *connection_start,
			    void *connection_stop,
			    void *get_value, void *set_value);
void dbpc_source_free(DBPCSource * src);

/* Connections */
DBPCConnection *dbpc_connection_new(DBPCSource * src,
				    const char *connection_string);
void dbpc_connection_free(DBPCConnection * cn);
#endif				/* SOURCE_PLUGIN_H */
