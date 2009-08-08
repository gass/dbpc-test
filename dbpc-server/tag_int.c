#include "tag.h"
#include "tag_int.h"
#include <stdlib.h>
#include <string.h>


DBPCTagInt * dbpc_int_new (DBPCConnection * cn,
                             const char *tag_name,
                             const char *address)
{
    DBPCTagInt *itag = malloc (sizeof (DBPCTagInt));
    itag->tag = dbpc_tag_new(cn, tag_name, address);
    itag->tag->tag_data = itag;
    return itag;
}

int dbpc_int_write (DBPCTagInt *itag, int value)
{
    if (dbpc_tag_set_value (DBPC_TAG (itag)) == 0)
    {
        itag->value = value;
        return 0;
    }
    else
    {
        return 1;
    }
}

int dbpc_int_read (DBPCTagInt *itag)
{
    size_t size = sizeof(int);
    BYTE * value = malloc (size);
    int r;
    r = dbpc_tag_get_value (DBPC_TAG (itag), value, size);
    if (r == 0)
    {
        memcpy (&itag->value, value, size);
    }
    free (value);
    return 0;
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
