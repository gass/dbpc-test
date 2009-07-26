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
#include "tag_bool.h"
#include "tag_int.h"
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
	DBPCTagBool *btag;
	DBPCTagInt *itag;
	dbpc_source_load ("/home/gass/dbpc/dbpc-server/.libs/libdbpc-source-file.so.0.0.0");
	src = dbpc_source_list_find("file common name");
	if (!src) return;
	
	printf ("eeer\n");
	printf ("descrition: %s\n", src->description);
	cn = dbpc_connection_new(src, "/home/gass/Desktop/tt.txt");
	/* bool tag */
	btag = dbpc_bool_new(cn, "Luis Luis", "M100.0");
	dbpc_bool_write (btag, dtrue);
	dbpc_tag_list_add(DBPC_TAG(btag));
	dbpc_bool_dump (btag);
	/* bool int */
	itag = dbpc_int_new(cn, "Luis Luis2", "M100.0");
	dbpc_int_write (itag, 1000);
	dbpc_tag_list_add(DBPC_TAG(itag));
	dbpc_int_dump (itag);
	itag = DBPC_TAG_INT(dbpc_tag_list_find("Luis Luis2"));
	dbpc_int_write (itag, 1001);
	if (itag == NULL) 
	{
		printf ("itag NULL\n");
		return;
	}
	if (!itag)
	{
		printf ("itag empty\n");
		return;
	}
	dbpc_int_dump (itag);
}
