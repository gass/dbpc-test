#include "connection.h"
#include "source_plugin.h"
#include <stdlib.h>
#include <string.h>

DBPCConnection *dbpc_connection_new(DBPCSource * src,
				    const char *connection_string)
{
	DBPCConnection *cn = malloc(sizeof(DBPCConnection));
	cn->source = src;
    cn->connection_string = strdup (connection_string);
	return cn;
}

int dbpc_connection_start (DBPCConnection *cn)
{
    cn->source->connection_start (cn);
    return 0;
}

int dbpc_connection_stop (DBPCConnection *cn)
{
    cn->source->connection_stop (cn);
    return 0;
}
void dbpc_connection_free(DBPCConnection * cn)
{
    if (cn->connection_string != NULL)
    {
        free (cn->connection_string);
    }
	free(cn);
}
