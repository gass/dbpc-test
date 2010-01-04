#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "source_plugin.h"
#include <stdlib.h>
#include <string.h>


#define SOURCE_NAME_ID "file"
#define SOURCE_NAME "file common name"
#define SOURCE_DESCRIPTION "file description"
/** address type */
enum address_type { invalid_address, boolean, integer };

/* static elements */
static int file_parse_address (const char *address, int *byte_addr, int *bit_addr);
static int file_get_byte_array (DBPCConnection *cn, int byte_addr, BYTE *byte_array, size_t size);
static int file_set_byte_array (DBPCConnection *cn,
                                int byte_addr,
                                BYTE *byte_array,
                                size_t size);

char * get_source_name_id (void) {
     return SOURCE_NAME_ID;
}

char * file_get_name (void) {
    return SOURCE_NAME;
}

char * file_get_description (void) {
    return SOURCE_DESCRIPTION;
}

void file_connection_start (DBPCConnection *cn) {
    cn->fd = open (cn->connection_string, O_RDWR);
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

int file_get_value (DBPCConnection * cn, const char *address, BYTE *value, size_t size)
{
    int byte_addr, bit_addr;
    int bit_mask = 0;
    int address_type = file_parse_address (address, &byte_addr, &bit_addr);
    
    if (address_type == invalid_address)
        return 1;
    
    /* if it is a valid address, we can retrieve the needed bytes */
    file_get_byte_array(cn, byte_addr, value, size);
    
    /* act according to the address type */
    switch (address_type)
    {
        case boolean:
            bit_mask = 1 << (bit_addr);
            if (bit_mask & *value)
            {
                *value = 1;
            }
            else
            {
                *value = 0;
            }
            break;
    }
    return 0;
}

/**
  * Gets a byte array from the file.
  * @cn: connection to be used.
  * @byte_addr: the order of the byte to be retrieved.
  * @value: allocated memory for the byte array to be retrieved  
  */

static int file_get_byte_array (DBPCConnection *cn,
                                int byte_addr,
                                BYTE *byte_array,
                                size_t size)
{
    ssize_t s;
    s = pread (cn->fd, byte_array, size, byte_addr);
    return 0;   
}

/**
  * Copies a byte array to the file.
  * @cn: connection to be used.
  * @byte_addr: the order of the byte to be changed.
  * @value: allocated memory for the byte array to be copied.  
  */

static int file_set_byte_array (DBPCConnection *cn,
                                int byte_addr,
                                BYTE *byte_array,
                                size_t size)
{
    ssize_t s;
    s = pwrite (cn->fd, byte_array, size, byte_addr);
    return 0;   
}


int file_set_value (DBPCConnection * cn, const char *address, BYTE *value, size_t size)
{
    int byte_addr, bit_addr;
    int bit_mask = 0;
    int address_type = file_parse_address (address, &byte_addr, &bit_addr);
    BYTE *read_value = NULL, *write_value = NULL;
    
    if (address_type == invalid_address)
        return 1;

    if (address_type == boolean)
    {
        read_value = malloc(size);
        write_value = malloc(size);
        file_get_byte_array(cn, byte_addr, read_value, size);    
        bit_mask = 1 << (bit_addr);
        *write_value = bit_mask & *read_value;
        
        file_set_byte_array (cn, byte_addr, write_value, size);
        free (read_value);
        free (write_value);
    }
    else
    {
        file_set_byte_array(cn, byte_addr, value, size);
    }
    return 0;
}

static int file_parse_address (const char *address, int *byte_addr, int *bit_addr)
{
    const char *address_t;
    int address_len = strlen(address);
    address_t = address;
    if (*address_t != 'M')
    {
        return invalid_address;
    }
    address_t = address + address_len -2;
    if (*address_t == '.')
    {
        address_t = address + 1;
        *byte_addr = atoi (address_t);
        address_t = address + address_len -1;
        *bit_addr = atoi(address_t);
        return boolean;
    }
    else
    {
        address_t = address;
        ++address_t;
        *byte_addr = atoi (address_t);
        return integer;
    }
}
