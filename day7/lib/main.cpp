#include "checkstatus.h"
#include<iostream>
// #define G_CALLBACK(Init)        //((GCallback) (Init)) 

int main(){
    networkStatusCheck netobj;
    
    GMainLoop *loop;
    GError *error = NULL;
    GDBusProxyFlags flags;
    GDBusProxy *proxy; 
    gchar* sender_name;
    gchar* signal_name;
    GVariant* variant;
    gpointer usr_data;


    /* Initialize GType system */

    //REmove if def, if any error in initialization
    #ifndef GLIB_VERSION_2_36
    g_type_init ();
    #endif
    
    /* Monitor 'StateChanged' signal on 'org.freedesktop.NetworkManager' interface */
    g_print("Monitor NetworkManager's state\n");
    g_print("==============================\n");

    flags = G_DBUS_PROXY_FLAGS_DO_NOT_LOAD_PROPERTIES;// | G_DBUS_PROXY_FLAGS_DO_NOT_AUTO_START;
    proxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SYSTEM,
                                            // NULL,
                                          flags,
                                          NULL, /* GDBusInterfaceInfo */
                                          "org.freedesktop.NetworkManager",
                                          "/org/freedesktop/NetworkManager",
                                          "org.freedesktop.NetworkManager",
                                          NULL, /* GCancellable */
                                          &error);

    if (proxy == NULL)
    {
        g_printerr("Error creating D-Bus proxy: %s\n", error->message);
        g_error_free(error);
        return -1;
    }

    //binding callback
    auto instance = networkStatusCheck();//this->instance
    instance.execute(bind(&networkStatusCheck::on_call,this,proxy,sender_name,signal_name,variant,usr_data));
    // instance.Init(Callback, proxy, sender_name,signal_name,variant,usr_data);          
    /* Connect to g-signal to receive signals from proxy (remote object) */
    g_signal_connect(proxy,
                    "g-signal",
                    GCallback((instance->execute([this]{on_call}))),//(proxy,sender_name,signal_name,variant,usr_data)),
                    NULL);

    /* Run main loop */
    // tempToCheck(2,3);
    loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);
    g_object_unref(proxy);
    return 0;
}