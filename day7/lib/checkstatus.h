#ifndef CHECK_STATUS_H
#define CHECK_STATUS_H

#include <gio/gio.h>
#include <string.h>
#include <functional>
// #include<string>
#include <NetworkManager.h>

class networkStatusCheck{
    private:


    public:
    using callback = std::function<void(GDBusProxy* , gchar* , gchar* , GVariant* , gpointer )>;
    networkStatusCheck(){}

    void Init(callback ,GDBusProxy* , gchar* , gchar* , GVariant* , gpointer );

    // typedef void  (*GCallback)  (void);
    
    char * nm_stat_to_string(NMState);
    void on_call(GDBusProxy*, gchar*, gchar*, GVariant*, gpointer);
    
    ~networkStatusCheck(){}

};

// void on_call(GDBusProxy* ,gchar* ,gchar* ,GVariant* ,gpointer );
                    
// void tempToCheck(int,int);

// char * nm_stat_to_string(NMState state);


#endif // CHECK_STATUS_H
