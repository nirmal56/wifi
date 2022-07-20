#include "rtnetlink.h"
#include <iostream>
using namespace std;

int main()
{
    serenity::nicMonitor instance;
    int nls = instance.open_netlink();
    struct sockaddr_nl *nl;
    struct nlmsghdr *msg;
    printf("Started watching:\n");

    if (nls < 0)
    {
        printf("Open Error!");
    }
    auto Callback = std::bind(&serenity::nicMonitor::read_print,
                              &instance,
                              std::placeholders::_1,
                              std::placeholders::_2,
                              std::placeholders::_3);
    while (1)
    {
        instance.Init(Callback, nls, nl, msg);
    }

    return 0;
}

// instance.read_event(nls, instance.msg_handler);

// for rapid json init
//  rapidjson::StringBuffer buffer;
//  rapidjson::Writer<rapidjson::StringBuffer>writer(buffer);
//  auto timestamp = std::chrono::system_clock::now();;
//  writer.Key(std::string("timestamp").c_str());
//  writer.StartObject();
//  writer.Int64(std::chrono::duration_cast<std::chrono::milliseconds>(timestamp.time_since_epoch()).count());
//  writer.EndObject();
//  std::cout<<instance.toJson("timestamp",(std::string)(timestamp.time_since_epoch().count()));
//  std::cout<<"timestamp is:"<<timestamp.time_since_epoch().count()<<std::endl;
//  std::cout<<buffer.GetString();