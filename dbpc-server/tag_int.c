#include "tag.h"
#include "tag_int.h"
#include <stdlib.h>


DBPCTagInt * dbpc_int_new (DBPCConnection * cn,
                             const char *tag_name,
                             const char *address)
{
    DBPCTagInt *itag = malloc (sizeof (DBPCTagInt));
    itag->tag = dbpc_tag_new(cn, tag_name, address);
    itag->tag->tag_data = itag;
    return itag;
}

void dbpc_int_write (DBPCTagInt *itag, int value)
{
    itag->value = value;
}

int dbpc_int_read (DBPCTagInt *itag)
{
    return itag->value;
}

void dbpc_int_free (DBPCTagInt *itag)
{
    dbpc_tag_free (DBPC_TAG(itag));
    free (itag);
}

void dbpc_int_dump (DBPCTagInt * itag)
{
    dbpc_tag_dump (DBPC_TAG(itag));
    printf ("TAG INT VALUE: %d\n", itag->value);
}
