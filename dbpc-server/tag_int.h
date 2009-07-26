/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */

#ifndef TAG_INT_H
#define TAG_INT_H
#include "tag.h"
#include "dbpc.h"

#define DBPC_TAG_INT(x) dbpc_tag_get_data (x)
typedef struct _DBPCTagInt DBPCTagInt;

struct _DBPCTagInt {
    DBPCTag *tag;
    int value;
    };

DBPCTagInt * dbpc_int_new (DBPCConnection * cn,
                           const char *tag_name,
                           const char *address);

void dbpc_int_write (DBPCTagInt *itag, int value);
int dbpc_int_read (DBPCTagInt *itag);
void dbpc_int_free (DBPCTagInt *itag);
void dbpc_int_dump (DBPCTagInt * itag);
#endif /* TAG_INT_H */
