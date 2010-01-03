#include "tag.h"
#include "tag_bool.h"
#include <stdlib.h>
#include <string.h>

DBPCTagBool * dbpc_bool_new (DBPCConnection * cn,
                             const char *tag_name,
                             const char *address)
{
    DBPCTagBool *btag = malloc (sizeof (DBPCTagBool));
    btag->tag = dbpc_tag_new(cn, tag_name, address);
    btag->tag->value_size = sizeof (dbool);
    btag->tag->tag_from_byte = &dbpc_bool_from_byte;
    btag->tag->tag_to_byte = &dbpc_bool_to_byte;
    btag->tag->tag_data = btag;
    return btag;
}

int dbpc_bool_write (DBPCTagBool *btag, dbool value)
{
    if (dbpc_tag_set_value (DBPC_TAG(btag)) == 0)
    {
        if (value)
        {
            btag->value = dtrue;
        }
        else
        {
            btag->value = dfalse;
        }
        return 0;
    }
    else
    {
        return 1;
    }
}

int dbpc_bool_read (DBPCTagBool *btag)
{
    dbpc_tag_get_value (DBPC_TAG (btag));
    return 0;
}

void dbpc_bool_free (DBPCTagBool *btag)
{
    dbpc_tag_free (DBPC_TAG(btag));
    free (btag);
}

void dbpc_bool_dump (DBPCTag *t)
{
    dbpc_tag_dump (t);
    if (DBPC_TAG_BOOL(t)->value)
        printf ("TAG BOOL VALUE: TRUE\n");
    else
        printf ("TAG BOOL VALUE: FALSE\n");
}

void dbpc_bool_from_byte (DBPCTag *t, BYTE *value)
{
    memcpy (&(DBPC_TAG_BOOL(t)->value), value, t->value_size);
}

void dbpc_bool_to_byte(DBPCTag *t, BYTE *value)
{
    memcpy (value, &(DBPC_TAG_BOOL(t)->value), t->value_size);
}
