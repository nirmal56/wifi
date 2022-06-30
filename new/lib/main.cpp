#include"rtnetlink.h"
#include <iostream>
using namespace std;

int main()
{
    nicMonitor instance;
    int nls = instance.open_netlink();

    struct sockaddr_nl *nl;
    struct nlmsghdr *msg;
    printf("Started watching:\n");
    if (nls < 0)
    {
        printf("Open Error!");
    }
    auto Callback = std::bind(&nicMonitor::read_print, &instance, std::placeholders::_1, 
                                                    std::placeholders::_2, 
                                                    std::placeholders::_3);
    while (1){
        // instance.read_event(nls, instance.msg_handler);
        instance.Init(Callback,nls,nl,msg);   
    }
    return 0;
}
