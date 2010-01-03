
#ifndef TAG_LIST_H
#define TAG_LIST_H
#include "tag.h"

typedef void (*list_execute) (DBPCTag *t);
#define DBPC_LIST_EXECUTE(function) (list_execute) &function

void dbpc_tag_list_add(DBPCTag * t);
DBPCTag *dbpc_tag_list_find(const char *tag_name);
void dbpc_tag_list_remove (DBPCTag *t);
int dbpc_tag_list_count (void);
int dbpc_list_process (void);
int dbpc_list_execute (list_execute function);

#endif				/* TAG_LIST_H */
