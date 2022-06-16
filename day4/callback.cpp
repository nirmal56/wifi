#include <iostream>
#include <gio/gio.h>
#include <string.h>
#include <NetworkManager.h>
#include <functional>

class checker
{
    public:

    using fun_callback = std::function<void(GDBusProxy *proxy,
                                            gchar *sender_name,
                                            gchar *signal_name,
                                            GVariant *parameters,
                                            gpointer user_data)>
    fun_callback fncallback_;

    checker(fun_callback cb):fncallback_(std::move(cb)){

    }
    static const char *nm_state_to_string(NMState state)
    {
        switch (state)
        {
        case NM_STATE_ASLEEP:
            return "asleep";
        case NM_STATE_CONNECTING:
            return "connecting";
        case NM_STATE_CONNECTED_LOCAL:
            return "connected (local only)";
        case NM_STATE_CONNECTED_SITE:
            return "connected (site only)";
        case NM_STATE_CONNECTED_GLOBAL:
            return "connected";
        case NM_STATE_DISCONNECTING:
            return "disconnecting";
        case NM_STATE_DISCONNECTED:
            return "disconnected";
        case NM_STATE_UNKNOWN:
        default:
            return "unknown";
        }
    }

    static void on_call(GDBusProxy *proxy,
                        gchar *sender_name,
                        gchar *signal_name,
                        GVariant *parameters,
                        gpointer user_data)
    {
        guint32 new_state;

        /* Print all signals */
        gchar *parameters_str;
        parameters_str = g_variant_print(parameters, TRUE);
        g_print(" *** Received Signal:sender:%s %s: %s\n", sender_name, signal_name, parameters_str);
        // g_print("*** Received Signal: sender:%s\n*** Received Signal: signal:%s\n*** Received Signal:parameters:%s\n",sender_name,signal_name,parameters);
        // g_free (parameters_str);

        /* We are only interested in "StateChanged" signal */
        if (strcmp(signal_name, "StateChanged") == 0)
        {
            g_print("total chils in parameter is:%d\n", g_variant_n_children(parameters));
            GVariant *tmp = g_variant_get_child_value(parameters, 0);
            new_state = g_variant_get_uint32(tmp);
            g_variant_unref(tmp);
            g_print("NetworkManager state is: (%d) %s\n", new_state, nm_state_to_string((NMState)new_state));
        }
    }
};

int main(int argc, char *argv[])
{
    checker chk;
    GMainLoop *loop;
    GError *error = NULL;
    GDBusProxyFlags flags;
    GDBusProxy *proxy;

    /* Initialize GType system */
    g_type_init();

    /* Monitor 'StateChanged' signal on 'org.freedesktop.NetworkManager' interface */
    g_print("Monitor NetworkManager's state\n");
    g_print("==============================\n");

    flags = G_DBUS_PROXY_FLAGS_DO_NOT_LOAD_PROPERTIES | G_DBUS_PROXY_FLAGS_DO_NOT_AUTO_START;
    proxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SYSTEM,
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

    /* Connect to g-signal to receive signals from proxy (remote object) */
    g_signal_connect(proxy,
                     "g-signal",
                     chk.fncallback_,
                     NULL);

    /* Run main loop */
    loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);

    g_object_unref(proxy);

    return 0;
}
