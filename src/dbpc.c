/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dbpc.h"

#include <stdio.h>
#include "dbpc.h"
#include "tag.h"

int main(void)
{
	DBPCTag *tag;
	DBPCSource *src;
	int i = 0;
	for (i = 0; i < 8; i++) {
		printf("############################\n");
		printf("Create a new DBPC Tag\n");
		tag = dbpc_tag_new("Luis Luis", "M100.0", "Mitsubishi", i, 1);
		printf("done tag new\n");

		dbpc_tag_set_permission(tag, RW);

		printf("end set permission");
		dbpc_tag_dump(tag);
		printf("done io dump\n");
		/* */
		dbpc_tag_free(tag);
		//if (i==7) i=0;
	}
	src = dbpc_source_new();
	dbpc_source_free(src);
	return 0;
}
