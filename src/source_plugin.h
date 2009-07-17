/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
#ifndef SOURCE_PLUGIN_H
#define SOURCE_PLUGIN_H

enum value_type {
	NONE = 0,
	BIT,
	BYTE,
	WORD,
	DWORD,
	INT,
	DINT,
	REAL
};

typedef struct _DBPCConnection DBPCConnection;

typedef struct _DBPCValue DBPCValue;

/**
 * DBPCValue:
 *
 * @value_type: the stored type of the #value.
 * It can be BIT, BYTE, INT, DINT, WORD, DWORD.
 * @value_size: the number of elements of #value_type, stored in #value.
 * @value: value of the tag, according to the #value_type
 *
 * A value definition.
 */
struct _DBPCValue {
	char value_type;
	int value_size;
	void *value;
};

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

void dbpc_value_init(DBPCValue * value, int value_type, int value_size);
void dbpc_value_dump(DBPCValue * value);
void dbpc_value_free(DBPCValue * value);
char *dbpc_value_type_to_string(int type);
void dbpc_value_dump(DBPCValue * value);
void dbpc_value_dump_value(DBPCValue * value);

#endif				/* SOURCE_PLUGIN_H */
