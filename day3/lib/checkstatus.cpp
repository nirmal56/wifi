#include "checkstatus.h"

networkStatusCheck::nm_stat_to_string(void){
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

networkStatusCheck::on_call(GDBusProxy *proxy,
                            gchar *sender_name,
                            gchar *signal_name,
                            GVariant *parameters,
                            gpointer user_Data){

    guint32 new_state;

    /* Print all signals */
    gchar *parameters_str;
    parameters_str = g_variant_print (parameters, TRUE);
    g_print (" *** Received Signal: %s: %s\n", signal_name, parameters_str);
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