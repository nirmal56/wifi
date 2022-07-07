#include "rtnetlink.h"
#include<iostream>
nicMonitor::nicMonitor()
{
}

int nicMonitor::Init(callback cb, int sockid, struct sockaddr_nl *sockaddr, struct nlmsghdr *nlms)
{
    return cb(sockid, sockaddr, nlms);
}

int nicMonitor::open_netlink()
{
    int sock = socket(AF_NETLINK, SOCK_RAW, MYPROTO);
    struct sockaddr_nl addr;

    memset((void *)&addr, 0, sizeof(addr));

    if (sock < 0)
        return sock;
    addr.nl_family = AF_NETLINK;
    addr.nl_pid = getpid();
    addr.nl_groups = /*RTMGRP_LINK |*/ RTMGRP_IPV4_IFADDR;// | RTMGRP_IPV6_IFADDR;
    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        return -1;
    return sock;
}

int nicMonitor::read_print(int sockint, struct sockaddr_nl *nl, struct nlmsghdr *msghdr)
{
    int status;
    int ret = 0;
    char buf[4096];
    struct iovec iov = {buf, sizeof buf};
    struct sockaddr_nl snl;
    struct msghdr msg = {(void *)&snl, sizeof snl, &iov, 1, NULL, 0, 0};
    struct nlmsghdr *h;

    status = recvmsg(sockint, &msg, 0);

    if (status < 0)
    {
        /* Socket non-blocking so bail out once we have read everything */
        if (errno == EWOULDBLOCK || errno == EAGAIN)
            return ret;

        /* Anything else is an error */
        printf("read_netlink: Error recvmsg: %d\n", status);
        perror("read_netlink: Error: ");
        return status;
    }

    if (status == 0)
    {
        printf("read_netlink: EOF\n");
    }

    /* We need to handle more than one message per 'recvmsg' */
    for (h = (struct nlmsghdr *)buf; NLMSG_OK(h, (unsigned int)status);
         h = NLMSG_NEXT(h, status))
    {
        /* Finish reading */
        if (h->nlmsg_type == NLMSG_DONE)
            return ret;

        /* Message is some kind of error */
        if (h->nlmsg_type == NLMSG_ERROR)
        {
            printf("read_netlink: Message is an error - decode TBD\n");
            return -1; // Error
        }

        /* Call message handler */
        if (msg_handler)
        {
            ret = (*msg_handler)(&snl, h);
            // std::cout<<"\nhere\n";
            if (ret < 0)
            {
                printf("read_netlink: Message hander error %d\n", ret);
                return ret;
            }
        }
        else
        {
            printf("read_netlink: Error NULL message handler\n");
            return -1;
        }
    }
    return ret;
}

int nicMonitor::netlink_link_state(struct sockaddr_nl *nl, struct nlmsghdr *msg)
{
    int len;
    struct ifinfomsg *ifi;
    char ifname[1024];
    nl = nl;

    ifi = (struct ifinfomsg *)NLMSG_DATA(msg);
    if_indextoname(ifi->ifi_index, ifname);

    // printf("netlink_link_state: Link %s\n",
           /*(ifi->ifi_flags & IFF_RUNNING)?"Up":"Down");*/
        //    (ifi->ifi_flags & IFF_UP) ? "Up" : "Down");
    return 0;
}

int nicMonitor::msg_handler(struct sockaddr_nl *nl, struct nlmsghdr *msg)
{
    struct ifinfomsg *ifi = (struct ifinfomsg *)NLMSG_DATA(msg);
    struct ifaddrmsg *ifa = (struct ifaddrmsg *)NLMSG_DATA(msg);
    char ifname[1024];
    std::string ip;
    nicMonitor mtr;

    //for json payload
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    //for timestamp
    auto timestamp = std::chrono::system_clock::now();

    writer.StartObject();

    writer.Key("timestamp");
    writer.Int64(std::chrono::duration_cast<std::chrono::milliseconds>(timestamp.time_since_epoch()).count());

    // switch (msg->nlmsg_type)
    // {
        if(msg->nlmsg_type == RTM_DELADDR) {

            // std::cout<<"\n"<<msg->nlmsg_type<<"\n\n";

            if_indextoname(ifi->ifi_index, ifname);
            ip=mtr.nametoIP(ifname);

            printf("msg_handler: RTM_DELADDR\n");
            // printf("msg_handler: Interface_name:%s\n", ifname);
            mtr.netlink_link_state(nl, msg);

            writer.Key("Interface Name");
            writer.String(ifname);
            writer.Key("IP Address");
            writer.String("");
        }
            
            // break;
        if(msg->nlmsg_type == RTM_NEWLINK){

            // std::cout<<"\n"<<msg->nlmsg_type<<"\n\n";

            if_indextoname(ifi->ifi_index, ifname);
            ip=mtr.nametoIP(ifname);
            printf("msg_handler: RTM_NEWLINK\n");
            // printf("msg_handler: Interface_name:%s Interface IP:%s\n", ifname,ip.c_str());
            mtr.netlink_link_state(nl, msg);

            writer.Key("Interface Name");
            writer.String(ifname);
            writer.Key("IP Address");
            writer.String(ip.c_str());

        }
            
            // break;

        if(msg->nlmsg_type == RTM_NEWADDR) {

            // std::cout<<"\n"<<msg->nlmsg_type<<"\n\n";

            if_indextoname(ifi->ifi_index, ifname);
            ip=mtr.nametoIP(ifname);
            printf("msg_handler: RTM_NEWADDR\n");
            // printf("msg_handler: Interface_name:%s\n", ifname);
            mtr.netlink_link_state(nl, msg);

            writer.Key("Interface Name");
            writer.String(ifname);
            writer.Key("IP Address");
            writer.String(ip.c_str());
        }
            
            // break;
    // }
    writer.EndObject();
    std::cout<<buffer.GetString()<<std::endl<<std::endl;
    return 0;
}


char* nicMonitor::nametoIP(char * name)
{
    struct ifreq ifr;
    int sock_id = socket(AF_INET, SOCK_DGRAM, 0);

    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, name, IFNAMSIZ -1);
    ioctl(sock_id, SIOCGIFADDR, &ifr);
    close(sock_id);

    return inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr);
}
std::string toJson(std::string key, std::string value, bool close = false)
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    writer.StartObject();
    writer.Key(key.c_str());
    writer.String(value.c_str());

    if (!close)
    {
        writer.EndObject();
    }
    return buffer.GetString();
}


nicMonitor::~nicMonitor()
{
}

//bunch of comments for unncessary events for now

        // case RTM_NEWROUTE:
        //     if_indextoname(ifi->ifi_index, ifname);
        //     ip=mtr.nametoIP(ifname);
        //     printf("msg_handler: RTM_NEWROUTE\n");
        //     // printf("msg_handler: Interface_name:%s\n", ifname);

        //     writer.Key("Interface Name");
        //     writer.String(ifname);
        //     writer.Key("IP Address");
        //     writer.String(ip.c_str());
        //     break;

        // case RTM_DELROUTE:
        //     if_indextoname(ifi->ifi_index, ifname);
        //     ip=mtr.nametoIP(ifname);
        //     printf("msg_handler: RTM_DELROUTE\n");
        //     // printf("msg_handler: Interface_name:%s\n", ifname);

        //     writer.Key("Interface Name");
        //     writer.String(ifname);
        //     writer.Key("IP Address");
        //     writer.String(ip.c_str());
        //     break;

        // case RTM_DELLINK:
        //     if_indextoname(ifi->ifi_index, ifname);
        //     ip=mtr.nametoIP(ifname);
        //     printf("msg_handler: RTM_DELLINK\n");
        //     // printf("msg_handler: Interface_name:%s\n", ifname);

        //     writer.Key("Interface Name");
        //     writer.String(ifname);
        //     writer.Key("IP Address");
        //     writer.String(ip.c_str());
        //     break;

        // default:
        //     printf("msg_handler: Unknown netlink nlmsg_type %d\n",
        //            msg->nlmsg_type);
        //     break;

// old msg_handler without interface name

// int nicMonitor::msg_handler(struct sockaddr_nl *nl, struct nlmsghdr *msg)
// {
//     nicMonitor mtr;
//     switch (msg->nlmsg_type)
//     {
//     // case RTM_NEWADDR:
//     //     printf("msg_handler: RTM_NEWADDR\n");
//     //     mtr.netlink_link_state(nl, msg);
//     //     break;
//     case RTM_DELADDR:
//         printf("msg_handler: RTM_DELADDR\n");
//         mtr.netlink_link_state(nl, msg);
//         break;
//     case RTM_NEWLINK:
//         printf("msg_handler: RTM_NEWLINK\n");
//         mtr.netlink_link_state(nl, msg);
//         break;
//     // case RTM_NEWROUTE:
//     //     printf("msg_handler: RTM_NEWROUTE\n");
//     //     break;
//     // case RTM_DELROUTE:
//     //     printf("msg_handler: RTM_DELROUTE\n");
//     //     break;
//     // case RTM_DELLINK:
//     //     printf("msg_handler: RTM_DELLINK\n");
//     //     break;
//     // default:
//     //     printf("msg_handler: Unknown netlink nlmsg_type %d\n",
//     //            msg->nlmsg_type);
//     //     break;
//     }
//     return 0;
// }

// old message_handler completed

// Some other netlink_state.

//    printf("netlink_link_state: family: %d\n", ifi->ifi_family);
//    if(ifi->ifi_family == AF_INET)
//    {
//         printf("Link index: %d Flags: (0x%x) ",
//                ifi->ifi_index, ifi->ifi_flags);
//         if(ifi->ifi_flags & IFF_UP)
//             printf("IFF_UP ");
//         if(ifi->ifi_flags & IFF_BROADCAST)
//             printf("IFF_BROADCAST ");
//         if(ifi->ifi_flags & IFF_DEBUG)
//             printf("IFF_DEBUG ");
//         if(ifi->ifi_flags & IFF_LOOPBACK)
//             printf("IFF_LOOPBACK ");
//         if(ifi->ifi_flags & IFF_POINTOPOINT)
//             printf("IFF_POINTOPOINT ");
//         if(ifi->ifi_flags & IFF_NOTRAILERS)
//             printf("IFF_NOTRAILERS ");
//         if(ifi->ifi_flags & IFF_RUNNING)
//             printf("IFF_RUNNING ");
//         if(ifi->ifi_flags & IFF_NOARP)
//             printf("IFF_NOARP ");
//         if(ifi->ifi_flags & IFF_PROMISC)
//             printf("IFF_PROMISC ");
//         if(ifi->ifi_flags & IFF_ALLMULTI)
//             printf("IFF_ALLMULTI ");
//         if(ifi->ifi_flags & IFF_MASTER)
//             printf("IFF_MASTER ");
//         if(ifi->ifi_flags & IFF_SLAVE)
//             printf("IFF_SLAVE ");
//         if(ifi->ifi_flags & IFF_MULTICAST)
//             printf("IFF_MULTICAST ");
//         if(ifi->ifi_flags & IFF_PORTSEL)
//             printf("IFF_PORTSEL ");
//         if(ifi->ifi_flags & IFF_AUTOMEDIA)
//             printf("IFF_AUTOMEDIA ");
//         printf("\n");
//    }