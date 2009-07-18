#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "source_plugin.h"



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
