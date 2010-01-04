
#include "tag.h"
#include "tag_list.h"
#include <string.h>

static void dbpc_tag_list_add_aux(DBPCTag * tag, DBPCTag * t);
static DBPCTag *dbpc_tag_list_find_aux (DBPCTag *tag, const char *tag_name);
static void dbpc_tag_list_remove_aux (DBPCTag *tag, DBPCTag *t);
static int dbpc_list_count_aux (DBPCTag *t, int n);
static int dbpc_list_process_aux (DBPCTag *t);
static int dbpc_list_execute_aux (DBPCTag *t, list_execute function);
static DBPCTag *dbpc_list_get_aux (DBPCTag *t, int count, int n);

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

int dbpc_list_process (void)
{
    return dbpc_list_execute (DBPC_LIST_EXECUTE(dbpc_tag_process));
}

int dbpc_list_dump (void)
{
    return dbpc_list_execute (DBPC_LIST_EXECUTE(dbpc_tag_dump));
}

int dbpc_list_execute (list_execute function)
{
    dbpc_list_execute_aux (TAG_LIST, function);
    return 0;
}

static int dbpc_list_execute_aux (DBPCTag *t, list_execute function)
{
    if (TAG_LIST == NULL)
    {
        return 0;
    }
    function(t);
    
    if (t->next == NULL)
    {
        return 0;
    }
    return dbpc_list_execute_aux (t->next, function);
}

DBPCTag *dbpc_list_get (int n)
{
    return dbpc_list_get_aux (TAG_LIST, 0, n);
}

static DBPCTag *dbpc_list_get_aux (DBPCTag *t, int count, int n)
{
    if (t == NULL)
    {
        return t;
    }
    else
    {
        if (count == n)
            return t;
        else
            if (t->next == NULL)
                return NULL;
            else
                return dbpc_list_get_aux (t->next, ++count, n);
    }
}
