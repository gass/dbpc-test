/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */

#ifndef TAG_H
#define TAG_H
#include "dbpc.h"
#include "source_plugin.h"
#include <time.h>

#define DBPC_TAG(x) x->tag
#define NO_OP 0

enum update_mode { ON_USE = 0, CONTINUOUS };
enum permission { R = 1, W, RW };

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
 * 1-read(R)
 * 2-write (W)
 * 3-read and write (RW);
 * @operation: operation to do in the next loop: 0-read, 1-write;
 * @user_permissions: needs more reasearch (not used yet).
 * @events: custom associated events and callbacks.
 * @connection: connection to be used.
 * @tag_data: stores the data pointer (for #DBPCTagBool, for example)
 * @value_size: the memory occupied by the value, in bytes.
 * @next: the next #DBPCTag in the tag list.
 *
 * All data points available trough DBPC are represented by a Tag object.
 */
typedef void (* TagToByte) (DBPCTag *t, BYTE *value);
typedef void (* TagFromByte) (DBPCTag *t, BYTE *value);

struct _DBPCTag {
	char *name;
	char *address;
	time_t timestamp;
	long validity;
	char update_mode;
	char permission;
	int user_permissions;
	char operation;

	void *events;
	
    void *tag_data;
    size_t value_size;
    TagFromByte tag_from_byte;
    TagToByte tag_to_byte;
    
	DBPCConnection *connection;
	DBPCTag *next;
};

/* function declarations */
DBPCTag *dbpc_tag_new(DBPCConnection * cn, const char *tag_name,
		      const char *address);
void dbpc_tag_set_permission(DBPCTag * t, int read_write);
int dbpc_tag_get_permission(DBPCTag *t);
void dbpc_tag_dump(DBPCTag * t);
void dbpc_tag_free(DBPCTag * t);
void *dbpc_tag_get_data (DBPCTag *t);
int dbpc_tag_get_value (DBPCTag *t);
int dbpc_tag_set_value (DBPCTag *t);
int dbpc_tag_get_operation (DBPCTag *t);
int dbpc_tag_set_operation (DBPCTag *t, int op);
void dbpc_tag_set_update_mode (DBPCTag *t, int update_mode);
int dbpc_tag_get_update_mode (DBPCTag *t);

#endif				/* TAG_H */
