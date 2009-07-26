/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */

#ifndef TAG_BOOL_H
#define TAG_BOOL_H
#include "tag.h"

typedef struct _DBPCTagBool DBPCTagBool;

struct _DBPCTagBool {
    DBPCTag *tag;
    char value; // 0 - false, 1 - true
    };

DBPCTagBool * dbpc_tag_bool_new (DBPCConnection * cn,
                                 const char *tag_name,
                                 const char *address);

#endif /* TAG_BOOL_H */
