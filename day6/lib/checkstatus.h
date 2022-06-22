#ifndef CHECK_STATUS_H
#define CHECK_STATUS_H

#include <gio/gio.h>
#include <string.h>
// #include<string>
#include <NetworkManager.h>

class networkStatusCheck{

    public:

    networkStatusCheck(){}

    static char * nm_stat_to_string(NMState state);
    static void on_call(GDBusProxy*, gchar*, gchar*, GVariant*, gpointer);
    void tempToCheck(int,int);
    ~networkStatusCheck(){}

    private:


};

// void on_call(GDBusProxy* ,gchar* ,gchar* ,GVariant* ,gpointer );
                    
// void tempToCheck(int,int);

// char * nm_stat_to_string(NMState state);


#endif // CHECK_STATUS_H
