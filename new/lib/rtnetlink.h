#ifndef RTNETLINK_H_
#define RTNETLINK_H_

#include <asm/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <net/if.h>
#include <netinet/in.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <functional>

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
     */
    using callback = std::function<int(int, struct sockaddr_nl *, struct nlmsghdr *)>;

    /*
     *init for bind
     */
    int Init(callback, int, struct sockaddr_nl *, struct nlmsghdr *);

    /*
     *opens netlink
     */
    int open_netlink();

    /*
     *read+print event for non static callback
     */
    int read_print(int sockint, struct sockaddr_nl *, struct nlmsghdr *);

    /*
     *print NIC state
     */
    int netlink_link_state(struct sockaddr_nl *nl, struct nlmsghdr *msg);

    /*
     *message handler - callback function(function pointer)
     */
    static int msg_handler(struct sockaddr_nl *nl, struct nlmsghdr *msg);

    /*
     *destructer
     */
    ~nicMonitor();
};

#endif // RTNETLINK_H_