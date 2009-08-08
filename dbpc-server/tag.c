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
		      const char *address)
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
	/* set permission 0, means set the default permission */
	dbpc_tag_set_permission(t, DBPC_DEFAULT);
	dbpc_tag_set_operation (t, DBPC_DEFAULT);
	return t;
}

void dbpc_tag_set_permission(DBPCTag * t, int read_write)
{
	/* in case of error, sets the default permission */
	if (read_write <= R || read_write > W || read_write == DBPC_DEFAULT)
	{
		t->permission = R;
	}
	else
	{
		t->permission = read_write;
	}
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

void *dbpc_tag_get_data (DBPCTag *t)
{
	if (t == NULL)
	{
		return NULL;
	}
	else
	{
		return t->tag_data;
	}
}
/**
  * This function retrieves the tag value.
  * If this tag has not continuous read, it will force the read from the source.
  */
int dbpc_tag_get_value (DBPCTag *t, BYTE *value, size_t size)
{
    if (t->update_mode == ON_USE)
	{
		/*
		 * If the tag is only read on use, we must set it to be updated in the
		 *  next loop.
		 * TODO:
		 * remove the get_value call, set the operation to READ, wait for 
		 *  the tag to be updated and then return the value.
		 */
		return t->connection->source->get_value (t->connection,
												 t->address, value, size);
	}
	else
	{
		/* if it is read continuously, we don't need to request an update, since
		 *  it is already up-to-date.
		 */
		return 10;
	}
}

/**
 * Sets that this tag must be written in the next update.
 */
int dbpc_tag_set_value (DBPCTag *t)
{
	/* check if we have write permission */
	if (dbpc_tag_get_write_permission (t) == 1)
	{
		/* in the next access to this tag,
		 * it will write the value that the tag has.
		 */
		dbpc_tag_set_operation (t, W);
		return 0;
	}
	else
	{
		/* it has no write permission */
		return 1;
	}
}

int dbpc_tag_get_write_permission (DBPCTag *t)
{
	if (t->permission == RW || t->permission == W)
	{
		return 1;
	}
	if (t->permission == R)
	{
		return 0;
	}
	else
	{
		dbpc_tag_set_permission (t, 0);
	}
}
/**
  * Defines what to do in the next loop */
int dbpc_tag_set_operation (DBPCTag *t, int op)
{
	if ((op == DBPC_DEFAULT && t->update_mode == CONTINUOUS))
	{
		t->operation = R;
		return 0;
	}
	if ((op == DBPC_DEFAULT && t->update_mode == ON_USE))
	{
		t->operation = NO_OP;
		return 0;
	}

	switch (op)
	{
		case R:
			t->operation = R;
			break;
		case RW:
			t->operation = RW;
			break;
		case W:
			t->operation = W;
			break;
		case NO_OP:
			t->operation = NO_OP;
			break;
		default:
			dbpc_tag_set_operation (t, DBPC_DEFAULT);
	}
	return 0;
}
/**
  * Processes a tag, meaning that if according to the permissions and the
  *  operation to be done
  */
int dbpc_tag_process (DBPCTag * t)
{
	/* operate according */
	switch (t->operation)
	{
		case W:
			printf ("write\n");
			dbpc_tag_set_operation (t, DBPC_DEFAULT);
			break;
		case R:
			printf ("read\n");
			break;
		case NO_OP:
			printf ("no_op\n");
			break;
	}

	return 0;
}
