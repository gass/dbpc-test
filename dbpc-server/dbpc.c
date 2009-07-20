/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dbpc.h"

#include <stdio.h>
#include "dbpc.h"
#include "tag_list.h"
#include "file_test.h"
#include "source_list.h"
void create_source(void);
int main(void)
{
	DBPCTag *tag;
	printf("start source\n");
	create_source();
	printf("source created\n");
#if 0
	int i = 0;
	for (i = 0; i < 8; i++) {
		printf("############################\n");
		printf("Create a new DBPC Tag\n");
		tag = dbpc_tag_new("Luis Luis", "M100.0", "file", i, 1);
		printf("done tag new\n");

		dbpc_tag_set_permission(tag, RW);

		printf("end set permission");
		dbpc_tag_dump(tag);
		printf("done io dump\n");
		/* */
		dbpc_tag_free(tag);
		//if (i==7) i=0;
	}
#endif
	return 0;
}

void create_source(void)
{
	int i = 0;
	DBPCSource *src;
	DBPCConnection *cn;
	DBPCTag *tag;
	src = dbpc_source_new("file",
			      &file_connection_start,
			      &file_connection_stop, NULL, NULL);
	dbpc_source_list_add(src);
	for (i = 0; i < 1; i++) {

		dbpc_tag_list_add(tag);
		printf("add add\n");
		src = NULL;
		src = dbpc_source_list_find("file");
		printf("get get\n");
		cn = dbpc_connection_new(src, "/home/gass/Desktop/tt.txt");
		tag = dbpc_tag_new(cn, "Luis Luis", "M100.0", i, 1);
		dbpc_tag_list_add (tag);
		//printf ("status start %d\n", cn->status);
		//src->connection_stop (cn);
		//printf ("status stop %d\n", cn->status);
		//dbpc_connection_free (cn);
		//dbpc_source_free_from_list (src);
		printf("source free\n");
		//sleep (0.25);
		//dbpc_source_free (src);
	}
}
