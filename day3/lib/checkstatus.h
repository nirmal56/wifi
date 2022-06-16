#include <gio/gio.h>
#include <string.h>
#include <NetworkManager.h>

class networkStatusCheck{
    private:
    static const char * nm_stat_to_string(NMStat state);

    public:

    networkStatusCheck(){}

    static void on_call(GDBusProxy *proxy,
                        gchar *sender_name,
                        gchar *signal_name,
                        GVariant *parameters,
                        gpointer user_data);
    
    ~networkStatusCheck(){}

};