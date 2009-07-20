/***************************************************************************
 *            value.h
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

#ifndef VALUE_H
#define VALUE_H

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

void dbpc_value_init(DBPCValue * value, int value_type, int value_size);
void dbpc_value_dump(DBPCValue * value);
void dbpc_value_free(DBPCValue * value);
char *dbpc_value_type_to_string(int type);
void dbpc_value_dump(DBPCValue * value);
void dbpc_value_dump_value(DBPCValue * value);
char *strdup_printf (const char *fmt, ...);

#endif				/* VALUE_H */
