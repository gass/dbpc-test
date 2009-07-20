
#ifndef SOURCE_LIST_H
#define SOURCE_LIST_H
#include "source_plugin.h"

void dbpc_source_list_add(DBPCSource * newsrc);
DBPCSource *dbpc_source_list_find(const char *name);
void dbpc_source_free_from_list(DBPCSource * src);
void dbpc_source_load (const char *filename);

#endif				/* SOURCE_LIST_H */
