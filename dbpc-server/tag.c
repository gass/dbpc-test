/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */

#include "tag.h"
#include "source_plugin.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

static char *dbpc_tag_dump_rw(DBPCTag * t);
static char *dbpc_tag_dump_operation(DBPCTag *t);
static DBPCTag *dbpc_tag_new_empty(void);

/**
  * Creates a new tag.
  */
DBPCTag *dbpc_tag_new(DBPCConnection * cn, const char *tag_name,
		      const char *address)
{
	DBPCTag *t = dbpc_tag_new_empty();

	t->name = strdup(tag_name);
	t->address = strdup(address);
	t->connection = cn;
	return t;
}

/**
  * Initiates a new empty tag.
  * All values are set for empty and/or default.
  */
static DBPCTag *dbpc_tag_new_empty(void)
{
	DBPCTag *t = malloc(sizeof(DBPCTag));

	t->name = NULL;
	t->address = NULL;
	t->events = NULL;
	t->connection = NULL;
	t->timestamp = 0;
	dbpc_tag_set_permission(t, DBPC_DEFAULT);
	dbpc_tag_set_operation (t, DBPC_DEFAULT);
	return t;
}

void dbpc_tag_set_permission(DBPCTag * t, int read_write)
{
	/*
	 * Only 2 options: R or RW.
	 * Defaults for R;
	 */
	if (read_write == RW)
	{
		t->permission = RW;
	}
	else
	{
		t->permission = R;
	}
}

void dbpc_tag_dump(DBPCTag * t)
{
	printf("TAG NAME: %s\n", t->name);
	printf("TAG ADDRESS: %s\n", t->address);
	printf("TAG PERMISSION: %s\n", dbpc_tag_dump_rw(t));
	printf("TAG OPERATION: %s\n", dbpc_tag_dump_operation(t));
	printf("TAG TIMESTAMP: %ld\n", t->timestamp);
}

static char *dbpc_tag_dump_rw(DBPCTag * t)
{
	switch (dbpc_tag_get_permission(t)) {
	case R:
		return ("READ");
		break;
	case RW:
		return ("READ/WRITE");
		break;
	}
	return NULL;
}

static char *dbpc_tag_dump_operation(DBPCTag *t)
{
	switch (dbpc_tag_get_operation(t))
	{
		case R:
			return ("READ");
			break;
		case W:
			return ("WRITE");
			break;
		case RW:
			return ("READ/WRITE");
			break;
		case NO_OP:
			return ("NO Operation");
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
    if (dbpc_tag_get_update_mode (t) == ON_USE)
	{
		/*
		 * If the tag is only read on use, we must set it to be updated in the
		 *  next loop.
		 * TODO:
		 * remove the get_value call, set the operation to READ, wait for 
		 *  the tag to be updated and then return the value.
		 */
		dbpc_tag_set_operation (t, R);
		return 0;
//		return t->connection->source->get_value (t->connection,
//												 t->address, value, size);
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
	if (dbpc_tag_get_permission (t) == RW)
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

int dbpc_tag_get_permission (DBPCTag *t)
{
	if (t->permission == RW)
	{
		return RW;
	}
	if (t->permission == R)
	{
		return R;
	}
	else
	{
		dbpc_tag_set_permission (t, DBPC_DEFAULT);
		return dbpc_tag_get_permission (t);
	}
}
/**
  * Defines what to do in the next loop */
int dbpc_tag_set_operation (DBPCTag *t, int op)
{
	if ((op == DBPC_DEFAULT && dbpc_tag_get_update_mode(t) == CONTINUOUS))
	{
		t->operation = R;
		return 0;
	}
	if ((op == DBPC_DEFAULT && dbpc_tag_get_update_mode(t) == ON_USE))
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
			return 1;
	}
	return 0;
}

int dbpc_tag_get_operation (DBPCTag *t)
{
	return t->operation;
	
}

void dbpc_tag_set_update_mode (DBPCTag *t, int update_mode)
{
	if (update_mode == CONTINUOUS)
	{
		t->update_mode = CONTINUOUS;
	}
	else
	{
		t->update_mode = ON_USE;
	}
}

int dbpc_tag_get_update_mode (DBPCTag *t)
{
	return t->update_mode;
	
}
/**
  * Processes a tag.
  * Reads, writes, or does nothing, according to the operation defined.
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
			dbpc_tag_set_operation (t, DBPC_DEFAULT);
			break;
		case NO_OP:
			printf ("no_op\n");
			break;
		default:
			dbpc_tag_set_operation (t, DBPC_DEFAULT);
	}

	return 0;
}
