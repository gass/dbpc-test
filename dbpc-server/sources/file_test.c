#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "source_plugin.h"
#include <stdlib.h>

#define SOURCE_NAME_ID "file"
#define SOURCE_NAME "file common name"
#define SOURCE_DESCRIPTION "file description"

char * get_source_name_id (void) {
     return SOURCE_NAME_ID;
}

char * file_get_name (void) {
    return SOURCE_NAME;
}

char * file_get_description (void) {
    return SOURCE_DESCRIPTION;
}

void file_connection_start (DBPCConnection *cn, const char * filename) {
    cn->fd = open (filename, O_CREAT);
    if ( cn->fd == -1) {
        cn->status = ERROR;
    }
    else {
        cn->status = OK;
    }
}

void file_connection_stop (DBPCConnection *cn) {
    if ( (close (cn->fd)) == -1) {
        cn->status = ERROR;
    }
    else {
        cn->status = OK;
    }
}

int file_get_value (DBPCConnection * cn, const char *address, BYTE **value)
{
    /* dummy function */
    BYTE * value2 = malloc (4*sizeof (BYTE));
    value2[0] = 20;
    *value = value2;
    return 0;
}
