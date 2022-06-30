#include "rtnetlink.h"
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
    addr.nl_groups = RTMGRP_LINK | RTMGRP_IPV4_IFADDR | RTMGRP_IPV6_IFADDR;
    //    addr.nl_groups = RTMGRP_LINK;
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

    nl = nl;

    ifi = (struct ifinfomsg *)NLMSG_DATA(msg);

    printf("netlink_link_state: Link %s\n", (ifi->ifi_flags & IFF_UP) ? "Up" : "Down");
    return 0;
}

int nicMonitor::msg_handler(struct sockaddr_nl *nl, struct nlmsghdr *msg)
{
    nicMonitor mtr;
    switch (msg->nlmsg_type)
    {
    case RTM_NEWADDR:
        printf("msg_handler: RTM_NEWADDR\n");
        mtr.netlink_link_state(nl, msg);
        break;
    case RTM_DELADDR:
        printf("msg_handler: RTM_DELADDR\n");
        mtr.netlink_link_state(nl, msg);
        break;
    case RTM_NEWROUTE:
        printf("msg_handler: RTM_NEWROUTE\n");
        break;
    case RTM_DELROUTE:
        printf("msg_handler: RTM_DELROUTE\n");
        break;
    case RTM_NEWLINK:
        printf("msg_handler: RTM_NEWLINK\n");
        mtr.netlink_link_state(nl, msg);
        break;
    case RTM_DELLINK:
        printf("msg_handler: RTM_DELLINK\n");
        break;
    default:
        printf("msg_handler: Unknown netlink nlmsg_type %d\n",
               msg->nlmsg_type);
        break;
    }
    return 0;
}

nicMonitor::~nicMonitor()
{
}