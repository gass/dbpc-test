#include <dbus/dbus.h>
#include <stdio.h>
#include <string.h>

#define exit(a) return(a)
dbus_int32_t num = 0;
int reply_to_method_call(DBusMessage *msg, DBusConnection *conn);
int main()
{
    
   DBusError err;
   DBusConnection* conn;
   DBusMessage *msg;
   int ret;
   // initialise the errors
   dbus_error_init(&err);

   // connect to the bus
   conn = dbus_bus_get(DBUS_BUS_SYSTEM, &err);
   if (dbus_error_is_set(&err)) { 
      fprintf(stderr, "Connection Error (%s)\n", err.message); 
      dbus_error_free(&err); 
   }
   if (NULL == conn) { 
       sleep(1);
      return 1; 
   }
    // request a name on the bus
   ret = dbus_bus_request_name(conn, "org.testes.daemon", 
         DBUS_NAME_FLAG_REPLACE_EXISTING 
         , &err);
   if (dbus_error_is_set(&err)) { 
      fprintf(stderr, "Name Error (%s)\n", err.message); 
      dbus_error_free(&err); 
   }
   if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret) { 
      exit(1);
   }

  
    
    //test_signal (conn);
    

 // loop, testing for new messages
   while (1) {
      // non blocking read of the next available message
      dbus_connection_read_write(conn, 0);
      msg = dbus_connection_pop_message(conn);

      // loop again if we haven't got a message
      if (NULL == msg) { 
         continue; 
      }
        printf ("recebeu qqcoisa 1\n");
      // check this is a method call for the right interface and method
       printf ("method %s %s\n", dbus_message_get_interface(msg), dbus_message_get_member (msg));
      if (dbus_message_is_method_call(msg, "org.testes.daemon", "Change_estado"))
         reply_to_method_call(msg, conn);
        printf ("recebeu qqcoisa 2\n");
      // free the message
      dbus_message_unref(msg);
   }


    
}

int reply_to_method_call(DBusMessage *msg, DBusConnection *conn)
{
    DBusMessage *return2, *msg2;
    DBusMessageIter iter;
    const char  *path;
    const char  *interface;
    printf ("entrou na resposta\n");
    path = dbus_message_get_path (msg);
    interface = dbus_message_get_interface (msg);
    return2 = dbus_message_new_method_return (msg);
    printf ("before ssend\n");
    if (!dbus_connection_send(conn, return2, NULL)) { 
      fprintf(stderr, "Out Of Memory!\n"); 
      exit(1);
   }
        printf ("before flush\n");
    dbus_connection_flush(conn);
        printf ("after flush\n");
    dbus_message_unref(return2);
        printf ("after unref\n");
    
    
printf ("path %s, interface %s\n", path, interface);
    msg2 = dbus_message_new_signal (path, interface, "StatusChanged");
        dbus_message_iter_init_append  	(msg2,&iter);
    ++num;
    dbus_message_iter_append_basic (&iter, DBUS_TYPE_INT32, &num);
     ++num;
    dbus_message_iter_append_basic (&iter, DBUS_TYPE_INT32, &num);
    dbus_connection_send(conn, msg2, NULL);
    dbus_connection_flush(conn);

    
    
    dbus_message_unref(msg2);
    
}
