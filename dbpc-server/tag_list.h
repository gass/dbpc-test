
#ifndef TAG_LIST_H
#define TAG_LIST_H
#include "tag.h"

void dbpc_tag_list_add(DBPCTag * t);
DBPCTag *dbpc_tag_list_find(const char *tag_name);
void dbpc_tag_list_remove (DBPCTag *t);
int dbpc_tag_list_count (void);

#endif				/* TAG_LIST_H */
