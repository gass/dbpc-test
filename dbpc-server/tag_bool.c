#include "tag.h"
#include "tag_bool.h"
#include <stdlib.h>


DBPCTagBool * dbpc_bool_new (DBPCConnection * cn,
                             const char *tag_name,
                             const char *address)
{
    DBPCTagBool *btag = malloc (sizeof (DBPCTagBool));
    btag->tag = dbpc_tag_new(cn, tag_name, address);
    return btag;
}

void dbpc_bool_write (DBPCTagBool *btag, dbool value)
{
    if (value)
    {
        btag->value = dtrue;
    }
    else
    {
        btag->value = dfalse;
    }
}

dbool dbpc_bool_read (DBPCTagBool *btag)
{
    return btag->value;
}

void dbpc_bool_free (DBPCTagBool *btag)
{
    dbpc_tag_free (DBPC_TAG(btag));
    free (btag);
}
