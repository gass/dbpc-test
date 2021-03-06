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
	BYTE * value;
	dbpc_source_load ("dbpc-server/.libs/libdbpc-source-file.so.0.0.0");
	src = dbpc_source_list_find("file common name");
	if (!src) return;
	
	printf ("eeer\n");
	printf ("descrition: %s\n", src->description);
	cn = dbpc_connection_new(src, "text_file.dbpc");
	/* bool tag */
	btag = dbpc_bool_new(cn, "Luis Luis", "M6.1");
	dbpc_tag_set_permission (DBPC_TAG(btag), RW);
	dbpc_tag_set_update_mode (DBPC_TAG(btag), CONTINUOUS);
	dbpc_tag_set_operation (DBPC_TAG(btag), R);
	dbpc_tag_list_add(DBPC_TAG(btag));
	//dbpc_bool_dump (btag);
	printf ("COUNT %d\n", dbpc_tag_list_count ());
	
	/* bool int */
	itag = dbpc_int_new(cn, "Luis Luis2", "M0");
	dbpc_tag_set_update_mode (DBPC_TAG(itag), CONTINUOUS);
	dbpc_tag_set_permission (DBPC_TAG(itag), RW);
	dbpc_tag_set_operation (DBPC_TAG(itag), R);
	dbpc_tag_list_add(DBPC_TAG(itag));
	itag = dbpc_int_new(cn, "Luis Luis2", "M1");
	dbpc_tag_set_update_mode (DBPC_TAG(itag), CONTINUOUS);
	dbpc_tag_set_permission (DBPC_TAG(itag), RW);
	dbpc_tag_set_operation (DBPC_TAG(itag), R);
	dbpc_tag_list_add(DBPC_TAG(itag));
	itag = dbpc_int_new(cn, "Luis Luis2", "M2");
	dbpc_tag_set_update_mode (DBPC_TAG(itag), CONTINUOUS);
	dbpc_tag_set_permission (DBPC_TAG(itag), RW);
	dbpc_tag_set_operation (DBPC_TAG(itag), RW);
	dbpc_tag_list_add(DBPC_TAG(itag));
	itag = dbpc_int_new(cn, "Luis Luis2", "M3");
	dbpc_tag_set_update_mode (DBPC_TAG(itag), CONTINUOUS);
	dbpc_tag_set_permission (DBPC_TAG(itag), RW);
	dbpc_tag_set_operation (DBPC_TAG(itag), R);
	dbpc_tag_list_add(DBPC_TAG(itag));
//	dbpc_int_write (itag, 1000);
	//dbpc_tag_list_add(DBPC_TAG(itag));
//	dbpc_int_dump (itag);
	//itag = DBPC_TAG_INT(dbpc_tag_list_find("Luis Luis2"));
	/*
	dbpc_int_write (itag, 1001);
	dbpc_int_dump (itag);
	
	dbpc_bool_read (btag);
	dbpc_bool_dump (btag);
	dbpc_int_read (itag);
	dbpc_int_dump (itag);
	 */
	printf ("COUNT %d\n", dbpc_tag_list_count ());
		dbpc_connection_start (cn);
		//dbpc_tag_process (DBPC_TAG(itag));
		//dbpc_tag_process (DBPC_TAG(itag));
		//dbpc_int_dump (itag);
		itag = DBPC_TAG_INT(dbpc_list_get(3));
		if (itag != NULL)
		{
			
			dbpc_int_write (itag, 1001);
			dbpc_int_dump(DBPC_TAG(itag));
		}
		dbpc_list_process ();

		//dbpc_bool_dump (btag);
		//dbpc_list_execute(DBPC_LIST_EXECUTE(dbpc_int_dump))
		dbpc_connection_stop (cn);
		dbpc_bool_dump (DBPC_TAG(btag));
		int c;
		int j;
		c = dbpc_tag_list_count();
		for (j=1; j<c;j++)
			dbpc_int_dump(dbpc_list_get(j));
		
/*	
	printf ("COUNT %d\n", dbpc_tag_list_count ());
	dbpc_tag_list_remove (DBPC_TAG(btag));
	printf ("COUNT %d\n", dbpc_tag_list_count ());
	dbpc_bool_free(btag);
	dbpc_tag_list_remove (DBPC_TAG(itag));
	printf ("COUNT %d\n", dbpc_tag_list_count ());
	dbpc_int_free(itag);
*/	
}
