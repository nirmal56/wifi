#ifndef CHECK_STATUS_H
#define CHECK_STATUS_H

#include <gio/gio.h>
#include <string.h>
#include <NetworkManager.h>

// class networkStatusCheck{

//     public:

//     networkStatusCheck(){}

//     void on_call(GDBusProxy*, gchar*, gchar*, GVariant*, gpointer);
//     void tempToCheck(int,int);
//     ~networkStatusCheck(){}

//     private:

//     std::string nm_stat_to_string(NMState state);

// };

void on_call(GDBusProxy ,gchar ,gchar ,GVariant ,gpointer );
                    
void tempToCheck(int,int);

char * nm_stat_to_string(NMState state);


#endif // CHECK_STATUS_H
