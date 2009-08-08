/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */

#ifndef DBPC_H
#define DBPC_H
#include "tag.h"
#include "source.h"
#include "connection.h"

#define DEBUG_LEVEL 100
/* DEBUG_LEVEL:
 0 - no debug
 1 - function start, function end
 2 - print before memory functions
 100 - ALL
 */

/* default option */ 
#define DBPC_DEFAULT -1

/* special types */
/** boolean value */
typedef char dbool;

enum dbool {dfalse = 0, dtrue = 1};


#endif				/* DBPC_H */
