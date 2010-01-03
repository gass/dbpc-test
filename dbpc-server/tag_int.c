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
    itag->tag->value_size = sizeof (int);
    itag->tag->tag_from_byte = &dbpc_int_from_byte;
    itag->tag->tag_to_byte = &dbpc_int_to_byte;
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
    dbpc_tag_get_value (DBPC_TAG (itag));
    return 0;
}

void dbpc_int_free (DBPCTagInt *itag)
{
    dbpc_tag_free (DBPC_TAG(itag));
    free (itag);
}

void dbpc_int_dump (DBPCTag *t)
{
    dbpc_tag_dump (t);
    printf ("TAG INT VALUE: %d\n", DBPC_TAG_INT(t)->value);
}

void dbpc_int_from_byte (DBPCTag *t, BYTE *value)
{
    memcpy (&(DBPC_TAG_INT(t)->value), value, t->value_size);
}

void dbpc_int_to_byte(DBPCTag *t, BYTE *value)
{
    memcpy (value, &(DBPC_TAG_INT(t)->value), t->value_size);
}
