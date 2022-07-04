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

#define MYPROTO NETLINK_ROUTE
#define MYMGRP RTMGRP_IPV4_ROUTE

int open_netlink()
{
    int sock = socket(AF_NETLINK, SOCK_RAW, MYPROTO);
    struct sockaddr_nl addr;

    memset((void *)&addr, 0, sizeof(addr));

    if (sock < 0)
        return sock;
    addr.nl_family = AF_NETLINK;
    addr.nl_pid = getpid();
    addr.nl_groups = RTMGRP_LINK | RTMGRP_IPV4_IFADDR | RTMGRP_IPV6_IFADDR;
    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        return -1;
    return sock;
}

int read_event(int sockint, int (*msg_handler)(struct sockaddr_nl *,
                                               struct nlmsghdr *))
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

static int netlink_link_state(struct sockaddr_nl *nl, struct nlmsghdr *msg)
{
    int len;
    struct ifinfomsg *ifi;

    nl = nl;

    ifi = NLMSG_DATA(msg);
    char ifname[1024];
    if_indextoname(ifi->ifi_index, ifname);

    printf("netlink_link_state: Link %s %s\n",
           /*(ifi->ifi_flags & IFF_RUNNING)?"Up":"Down");*/
           ifname, (ifi->ifi_flags & IFF_UP) ? "Up" : "Down");
    return 0;
}

static int msg_handler(struct sockaddr_nl *nl, struct nlmsghdr *msg)
{
    struct ifinfomsg *ifi = NLMSG_DATA(msg); /* for RTM_{NEW,DEL}ADDR */
    struct ifaddrmsg *ifa = NLMSG_DATA(msg); /* for RTM_{NEW,DEL}LINK */
    char ifname[1024];
    switch (msg->nlmsg_type)
    {
    case RTM_NEWADDR:
        if_indextoname(ifa->ifa_index, ifname);
        printf("msg_handler: RTM_NEWADDR : %s\n", ifname);
        break;
    case RTM_DELADDR:
        if_indextoname(ifa->ifa_index, ifname);
        printf("msg_handler: RTM_DELADDR : %s\n", ifname);
        break;
    case RTM_NEWLINK:
        if_indextoname(ifi->ifi_index, ifname);
        printf("msg_handler: RTM_NEWLINK\n");
        netlink_link_state(nl, msg);
        break;
    case RTM_DELLINK:
        if_indextoname(ifi->ifi_index, ifname);
        printf("msg_handler: RTM_DELLINK : %s\n", ifname);
        break;
    default:
        printf("msg_handler: Unknown netlink nlmsg_type %d\n",
               msg->nlmsg_type);
        break;
    }
    return 0;
}
int main(int argc, char *argv[])
{
    int nls = open_netlink();
    printf("Started watching:\n");
    if (nls < 0)
    {
        printf("Open Error!");
    }
    while (1)
        read_event(nls, msg_handler);
    return 0;
}