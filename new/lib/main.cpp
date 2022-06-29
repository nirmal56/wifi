#include"rtnetlink.h"
#include <iostream>
using namespace std;

int main()
{
    nicMonitor instance;
    int nls = instance.open_netlink();

    printf("Started watching:\n");
    if (nls < 0)
    {
        printf("Open Error!");
    }

    while (1)
        instance.read_event(nls, instance.msg_handler);
    return 0;
}
