/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */

#ifndef TAG_BOOL_H
#define TAG_BOOL_H
#include "tag.h"
#include "dbpc.h"

typedef struct _DBPCTagBool DBPCTagBool;
#define DBPC_TAG_BOOL(x) ((DBPCTagBool *)dbpc_tag_get_data (x))

struct _DBPCTagBool {
    DBPCTag *tag;
    dbool value;
    };

DBPCTagBool * dbpc_bool_new (DBPCConnection * cn,
                                 const char *tag_name,
                                 const char *address);

int dbpc_bool_write (DBPCTagBool *btag, dbool value);
int dbpc_bool_read (DBPCTagBool *btag);
void dbpc_bool_free (DBPCTagBool *btag);
void dbpc_bool_dump (DBPCTag *t);
void dbpc_bool_from_byte (DBPCTag *t, BYTE *value);
void dbpc_bool_to_byte(DBPCTag *t, BYTE *value);
#endif /* TAG_BOOL_H */
