
#include "tag.h"
#include <string.h>

static void dbpc_tag_list_add_aux(DBPCTag * tag, DBPCTag * t);
static DBPCTag *dbpc_tag_list_find_aux (DBPCTag *tag, const char *tag_name);

DBPCTag *TAG_LIST = NULL;

void dbpc_tag_list_add(DBPCTag * t)
{
	if (TAG_LIST == NULL) {
		TAG_LIST = t;
		return;
	} else {
		dbpc_tag_list_add_aux(TAG_LIST, t);
	}
}

static void dbpc_tag_list_add_aux(DBPCTag * tag, DBPCTag * t)
{
	if (tag->next == NULL) {
		tag->next = t;
	} else {
		dbpc_tag_list_add_aux(tag->next, t);
	}
}

DBPCTag *dbpc_tag_list_find(const char *tag_name)
{
    return dbpc_tag_list_find_aux (TAG_LIST, tag_name);
}

static DBPCTag *dbpc_tag_list_find_aux (DBPCTag *tag, const char *tag_name)
{
    if (tag == NULL) {
        return NULL;
    }
    if (!strcmp (tag->name, tag_name)) {
        return tag;
    } else {
        return dbpc_tag_list_find_aux (tag, tag_name);
    }
    
}
