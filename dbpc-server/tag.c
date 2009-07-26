/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */

#include "tag.h"
#include "source_plugin.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

static char *dbpc_tag_dump_rw(DBPCTag * t);
static DBPCTag *dbpc_tag_new_empty(void);

DBPCTag *dbpc_tag_new(DBPCConnection * cn, const char *tag_name,
		      const char *address, int value_type, int value_size)
{
	DBPCTag *t = dbpc_tag_new_empty();

	t->name = strdup(tag_name);
	t->address = strdup(address);
	t->connection = cn;
	return t;
}

static DBPCTag *dbpc_tag_new_empty(void)
{
	DBPCTag *t = malloc(sizeof(DBPCTag));

	t->name = NULL;
	t->address = NULL;
	t->events = NULL;
	t->connection = NULL;
	t->timestamp = 0;
	return t;
}

void dbpc_tag_set_permission(DBPCTag * t, int read_write)
{
	t->permission = read_write;
}

void dbpc_tag_dump(DBPCTag * t)
{
	printf("TAG NAME: %s\n", t->name);
	printf("TAG ADDRESS: %s\n", t->address);
	printf("TAG PERMISSION: %s\n", dbpc_tag_dump_rw(t));
	printf("TAG TIMESTAMP: %ld\n", t->timestamp);
}

static char *dbpc_tag_dump_rw(DBPCTag * t)
{
	switch (t->permission) {
	case R:
		return ("READ");
		break;
	case W:
		return ("WRITE");
		break;
	case RW:
		return ("READ/WRITE");
		break;
	}
	return NULL;
}

void dbpc_tag_free(DBPCTag * t)
{
	if (t->name != NULL)
		free(t->name);
	if (t->address != NULL)
		free(t->address);

//    if (t->events!=NULL) free (t->events);
	free(t);
}
