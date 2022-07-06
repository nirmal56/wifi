#ifndef RTNETLINK_H_
#define RTNETLINK_H_
//for  getting events
#include <asm/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <net/if.h>
#include <netinet/in.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
//to convert in ip
#include <arpa/inet.h>
#include <sys/ioctl.h>
//for callback
#include <ifaddrs.h>
#include <functional>
#include <string>
//for timestamp
#include <chrono>
//for json
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#define MYPROTO NETLINK_ROUTE
#define MYMGRP RTMGRP_IPV4_ROUTE

class nicMonitor
{
public:
    /*
     *constructor
     */
    nicMonitor();

    /*
     *setting up for callback
     *Parameters:void
     *Parameters:int, struct sockaddr_nl*, sturct nlmsghdr *
     */
    using callback = std::function<int(int, struct sockaddr_nl *, struct nlmsghdr *)>;

    /*
     *init for bind
     *Parameters: callback_function, int, struct sockaddr_nl *, struct nlmsghdr*
     *returns: function itself
     */
    int Init(callback, int, struct sockaddr_nl *, struct nlmsghdr *);

    /*
     *opens netlink
     *Parameters:void
     *Returns: socket integer
     */
    int open_netlink();

    /*
     *read+print event for non static callback
     *Parameters: int , struct sockaddr_nl *, struct nlmsghdr *
     *Returns: success/failure
     */
    int read_print(int sockint, struct sockaddr_nl *, struct nlmsghdr *);

    /*
     *print NIC state
     *Parameters: struct sockaddr_nl *, struct nlmsghdr *
     *Returns:0
     */
    int netlink_link_state(struct sockaddr_nl *nl, struct nlmsghdr *msg);

    /*
     *message handler - callback function(function pointer)
     *Parameters: struct sockaddr_nl *, struct nlmsghdr *
     *Returns:0
     */
    static int msg_handler(struct sockaddr_nl *nl, struct nlmsghdr *msg);

    /*
     *tojson - converts key and value in json
     *Parameters: std::string key,std::string value
     *returns:json  in std::string  format
     */
    std::string toJson(std::string key, std::string value);

    /*
     *nametoIP - converts interface naem to its ipaddress
     *Parameters : char * interface name
     *returns : char * ip address
     */
    char *nametoIP(char *);

    /*
     *destructer
     *Parameters: struct sockaddr_nl *, struct nlmsghdr *
     *Returns:0
     */
    ~nicMonitor();
};

#endif // RTNETLINK_H_