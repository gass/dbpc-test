#include "tag.h"
#include "tag_bool.h"
#include <unistd.h>


DBPCTagBool * dbpc_tag_bool_new (DBPCConnection * cn,
                                 const char *tag_name,
                                 const char *address)
{
    DBPCTagBool *btag = malloc (sizeof (DBPCTagBool));
    btag->tag = dbpc_tag_new(cn, tag_name, address);
    return btag;
}
