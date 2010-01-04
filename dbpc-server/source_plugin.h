/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
#ifndef SOURCE_PLUGIN_H
#define SOURCE_PLUGIN_H
#include "utils.h"

typedef char BYTE;

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
	char * connection_string;
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
 * @process_pre: Pre-processing. Permits to organize the memory to get from the
  connection source.
 * @process: Ends pre-processing. The first call to this function retrieves the
 full data from the connection soure to a buffer. The following calls to this
 function retrieves data from that buffer, until pre-processing is called again.
 * @monitor: function that monitors a variable change.
 */
struct _DBPCSource {
	char *name;
	char *description;
	void (*connection_start) (DBPCConnection * cn);
	void (*connection_stop) (DBPCConnection * cn);
    int (*get_value) (DBPCConnection * cn, const char *address,
			  BYTE *value, size_t size);
	int (*set_value) (DBPCConnection * cn, const char *address,
			  BYTE *value, size_t size);
    int (*process_pre) (DBPCConnection * cn, const char *address,
			  BYTE *value, size_t size);
	int (*process) (DBPCConnection * cn, const char *address,
			  BYTE *value, size_t size);
	int (*monitor_value) (DBPCConnection * cn, const char *address,
			      BYTE * value);

	DBPCSource *next;
};


#endif				/* SOURCE_PLUGIN_H */
