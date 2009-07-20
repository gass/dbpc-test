#include "connection.h"
#include "source_plugin.h"
#include <stdlib.h>

DBPCConnection *dbpc_connection_new(DBPCSource * src,
				    const char *connection_string)
{
	DBPCConnection *cn = malloc(sizeof(DBPCConnection));
	cn->source = src;
	//cn->source->connection_start (cn, connection_string);
	return cn;
}

void dbpc_connection_free(DBPCConnection * cn)
{
	free(cn);
}
