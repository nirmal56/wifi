#include <gio/gio.h>
#include <string.h>
#include <string>
#include <NetworkManager.h>

class networkStatusCheck{

    public:

    networkStatusCheck(){}

    static void on_call(GDBusProxy *proxy,
                        gchar *sender_name,
                        gchar *signal_name,
                        GVariant *parameters,
                        gpointer user_data);
    
    ~networkStatusCheck(){}

    private:

    std::string nm_stat_to_string(NMState state);

};