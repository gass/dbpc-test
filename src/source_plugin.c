/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */

#include "source_plugin.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char *TypeString[9] = {
	"NONE",
	"BIT",
	"BYTE",
	"WORD",
	"DWORD",
	"INT",
	"DINT",
	"REAL"
};

static DBPCSource *dbpc_source_new_empty(void);
static void dbpc_value_set_type(DBPCValue * value, int type);

DBPCSource *dbpc_source_new(void)
{
	DBPCSource *src = dbpc_source_new_empty();
	return src;
}

static DBPCSource *dbpc_source_new_empty(void)
{
	DBPCSource *src = malloc(sizeof(DBPCSource));
	src->name = NULL;
	src->connection_start = NULL;
	src->connection_stop = NULL;
	src->get_value = NULL;
	src->set_value = NULL;
	src->monitor_value = NULL;
	return src;
}

void dbpc_source_free(DBPCSource * src)
{
	free(src);
}

void dbpc_value_init(DBPCValue * value, int value_type, int value_size)
{
	value->value_type = value_type;
	value->value_size = value_size;
	value->value = NULL;
	dbpc_value_set_type(value, value_type);
}

static void dbpc_value_set_type(DBPCValue * value, int value_type)
{
	size_t size = 0;

	if (value->value != NULL) {
		free(value->value);
		value->value = NULL;
	}
	value->value_type = value_type;

	switch (value_type) {
	case BIT:
	case BYTE:
		size = 1;
		break;
	case WORD:
	case INT:
		size = 2;
		break;
	case DINT:
	case REAL:
	case DWORD:
		size = 8;
		break;
	}
	if (size > 0) {
		value->value = malloc(value->value_size * size);
		memset(value->value, 0, value->value_size * size);
	}
}

void dbpc_value_dump_value(DBPCValue * value)
{
	switch (value->value_type) {
	case BIT:
	case BYTE:
		printf("VALUE: %d\n", *(int *)value->value);
		break;
	case WORD:
		printf("VALUE: not implemented yet\n");
		break;
	case INT:
		printf("VALUE: %d\n", *(int *)value->value);
		break;
	case DWORD:
		printf("VALUE: not implemented yet\n");
		break;
	case DINT:
		printf("VALUE: %ld\n", *(long *)value->value);
		break;
	case REAL:
		printf("VALUE: %f\n", *(float *)value->value);
		break;
	}
}

void dbpc_value_dump(DBPCValue * value)
{
	printf("VALUE TYPE: %s\n",
	       dbpc_value_type_to_string(value->value_type));
	dbpc_value_dump_value(value);
}

void dbpc_value_free(DBPCValue * value)
{
	if (value->value != NULL)
		free(value->value);
}

char *dbpc_value_type_to_string(int type)
{
	return TypeString[type];
}
