
#ifndef FILE_TEST_H
#define FILE_TEST_H
#include "source_plugin.h"
void file_connection_stop (DBPCConnection *cn);
DBPCConnection *file_connection_start (const char * filename);

#endif
