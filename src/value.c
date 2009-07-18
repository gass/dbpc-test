/***************************************************************************
 *            value.c
 *
 *  Sat Jul 18 13:28:58 2009
 *  Copyright  2009  Luis Matos
 *  <gass@otiliamatos.ath.cx>
 ****************************************************************************/

/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with main.c; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */
#include "value.h"
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

static void dbpc_value_set_type(DBPCValue * value, int type);

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
