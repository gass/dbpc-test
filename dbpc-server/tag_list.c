
#include "tag.h"
#include <string.h>

static void dbpc_tag_list_add_aux(DBPCTag * tag, DBPCTag * t);
static DBPCTag *dbpc_tag_list_find_aux (DBPCTag *tag, const char *tag_name);
static void dbpc_tag_list_remove_aux (DBPCTag *tag, DBPCTag *t);
static int dbpc_list_count_aux (DBPCTag *t, int n);

DBPCTag *TAG_LIST = NULL;

void dbpc_tag_list_add(DBPCTag * t)
{
	if (TAG_LIST == NULL) {
		TAG_LIST = t;
        t->next = NULL;
		return;
	} else {
		dbpc_tag_list_add_aux(TAG_LIST, t);
	}
}

static void dbpc_tag_list_add_aux(DBPCTag * tag, DBPCTag * t)
{
	if (tag->next == NULL) {
		tag->next = t;
        t->next = NULL;
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
    if ((strcmp(tag->name, tag_name) == 0)) {
        return tag;
    } else {
        return dbpc_tag_list_find_aux (tag->next, tag_name);
    }
    
}

void dbpc_tag_list_remove (DBPCTag *t)
{
    if (TAG_LIST == NULL)
    {
        return;
    }
    if (t == TAG_LIST)
    {
        TAG_LIST = t->next;
        return;
    }
    else
    {
        dbpc_tag_list_remove_aux (TAG_LIST, t); 
    }
}

static void dbpc_tag_list_remove_aux (DBPCTag *tag, DBPCTag *t)
{
    if (tag->next == t)
    {
        tag->next = t->next;
        t->next = NULL;
    }
    else
    {
        if (t->next == NULL)
        {
            return;
        }
        else
        {
            dbpc_tag_list_remove_aux (tag->next, t);
        }
    }
}

int dbpc_tag_list_count (void)
{
    return dbpc_list_count_aux (TAG_LIST, 0);
}

static int dbpc_list_count_aux (DBPCTag *t, int n)
{
    if (t == NULL)
    {
        return n;
    }
    else
    {
        return dbpc_list_count_aux (t->next, ++n);
    }
}
