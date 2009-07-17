/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */

#ifndef TAG_H
#define TAG_H
#include "dbpc.h"
#include "source_plugin.h"
#include <time.h>

enum update_mode { ON_USE = 0, CONTINUOUS };
enum permission { R = 0, W, RW };

typedef struct _DBPCTag DBPCTag;

/**
 * DBPCTag:
 * @name: Stores the name of the tag.
 * This name is unique for DBPC server instance and refers the tag item.
 * @address: Store where the value can be retried by the DBPC server.
 * Its format is specific to the protocol implemented by the DBPC server's protocol plugin.
 * @timestamp: Stores the late time when the value has been updated.
 * @validity: Stores the time for witch the tag's value is valid. Given in seconds.
 * @update_mode: corresponds to the update: 0-on use, 1-continuous.
 * @permission: What permissions does DBPC have to this value:
 * 0-read(R)
 * 1-write (W)
 * 2-read and write (RW);
 * @operation: operation to do in the next loop: 0-read, 1-write;
 * @user_permissions: needs more reasearch (not used yet).
 * @events: custom associated events and callbacks.
 * @source: #DBPCSource plugin to use.
 *
 * All data points available trough DBPC are represented by a Tag object.
 */

struct _DBPCTag {
	char *name;
	char *address;
	time_t timestamp;
	long validity;
	char update_mode;
	char permission;
	int user_permissions;
	char operation;
	DBPCValue value;

	void *events;

	DBPCSource *source;
};

/* function declarations */
DBPCTag *dbpc_tag_new(const char *tag_name, const char *address,
		      const char *plugin_name, int value_type, int value_size);
void dbpc_tag_set_permission(DBPCTag * t, int read_write);
char *dbpc_tag_value_type_to_string(int type);
void dbpc_tag_dump(DBPCTag * t);
void dbpc_tag_free(DBPCTag * t);

#endif				/* TAG_H */
