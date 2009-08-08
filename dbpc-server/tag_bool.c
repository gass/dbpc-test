#include "tag.h"
#include "tag_bool.h"
#include <stdlib.h>


DBPCTagBool * dbpc_bool_new (DBPCConnection * cn,
                             const char *tag_name,
                             const char *address)
{
    DBPCTagBool *btag = malloc (sizeof (DBPCTagBool));
    btag->tag = dbpc_tag_new(cn, tag_name, address);
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
    BYTE value;
    int r;
    r = dbpc_tag_get_value (DBPC_TAG (btag), &value, sizeof(BYTE));
    if (r == 0)
    {
        if (value > 0)
        {
            btag->value = dtrue;
        }
        else
        {
            btag->value = dfalse;
        }
    }
    return 0;
}

void dbpc_bool_free (DBPCTagBool *btag)
{
    dbpc_tag_free (DBPC_TAG(btag));
    free (btag);
}

void dbpc_bool_dump (DBPCTagBool * btag)
{
    dbpc_tag_dump (DBPC_TAG(btag));
    if (btag->value)
        printf ("TAG BOOL VALUE: TRUE\n");
    else
        printf ("TAG BOOL VALUE: FALSE\n");
}
