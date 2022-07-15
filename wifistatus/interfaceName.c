#include <asm/types.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, void ** argv) {

// This is the address we want the interface name for,
// expressed in dotted-quad format
// char * address_dq = "127.0.0.1";
char * address_dq = "10.0.2.15";
// Convert it to decimal format
unsigned int address;
inet_pton(AF_INET, address_dq, &address);

char buf[16384];

// Our first message will be a header followed by an address payload
struct {
    struct nlmsghdr nlhdr;
    struct ifaddrmsg addrmsg;
} msg;

// Our second message will be a header followed by a link payload
struct {
    struct nlmsghdr nlhdr;
    struct ifinfomsg infomsg;
} msg2;

struct nlmsghdr *retmsg;

// Set up the netlink socket
int sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);

// Fill in the message
// NLM_F_REQUEST means we are asking the kernel for data
// NLM_F_ROOT means provide all the addresses
// RTM_GETADDR means we want address information
// AF_INET means limit the response to ipv4 addresses
memset(&msg, 0, sizeof(msg));
msg.nlhdr.nlmsg_len = NLMSG_LENGTH(sizeof(struct ifaddrmsg));
msg.nlhdr.nlmsg_flags = NLM_F_REQUEST | NLM_F_ROOT;
msg.nlhdr.nlmsg_type = RTM_GETADDR;
msg.addrmsg.ifa_family = AF_INET;

// As above, but RTM_GETLINK means we want link information
memset(&msg2, 0, sizeof(msg2));
msg2.nlhdr.nlmsg_len = NLMSG_LENGTH(sizeof(struct ifinfomsg));
msg2.nlhdr.nlmsg_flags = NLM_F_REQUEST | NLM_F_ROOT;
msg2.nlhdr.nlmsg_type = RTM_GETLINK;
msg2.infomsg.ifi_family = AF_UNSPEC;

// Send the first netlink message
send(sock, &msg, msg.nlhdr.nlmsg_len, 0);

int len;

// Get the netlink reply
len = recv(sock, buf, sizeof(buf), 0);

retmsg = (struct nlmsghdr *)buf;

// Loop through the reply messages (one for each address)
// Each message has a ifaddrmsg structure in it, which 
// contains the prefix length as a member.  The ifaddrmsg
// structure is followed by one or more rtattr structures, 
// some of which (should) contain raw addresses.
while NLMSG_OK(retmsg, len) {

    struct ifaddrmsg *retaddr;
    retaddr = (struct ifaddrmsg *)NLMSG_DATA(retmsg);
    int iface_idx = retaddr->ifa_index;

    struct rtattr *retrta;
    retrta = (struct rtattr *)IFA_RTA(retaddr);

    int attlen;
    attlen = IFA_PAYLOAD(retmsg);

    char pradd[128];

    // Loop through the routing information to look for the 
    // raw address.
    while RTA_OK(retrta, attlen) {
        if (retrta->rta_type == IFA_ADDRESS) {
            // Found one -- is it the one we want?
            unsigned int * tmp = RTA_DATA(retrta);
            if (address == *tmp) {
                // Yes!
                inet_ntop(AF_INET, RTA_DATA(retrta), pradd, sizeof(pradd));
                printf("Address %s ", pradd);
                // Now we need to get the interface information
                // First eat up the "DONE" message waiting for us
                len = recv(sock, buf, sizeof(buf), 0);
                // Send the second netlink message and get the reply
                send(sock, &msg2, msg2.nlhdr.nlmsg_len, 0);
                len = recv(sock, buf, sizeof(buf), 0);
                retmsg = (struct nlmsghdr *)buf;
                while NLMSG_OK(retmsg, len) {
                    struct ifinfomsg *retinfo;
                    retinfo = NLMSG_DATA(retmsg);
                    if (retinfo->ifi_index == iface_idx) {
                        retrta = IFLA_RTA(retinfo);
                        attlen = IFLA_PAYLOAD(retmsg);
                        char prname[128];
                        // Loop through the routing information 
                        // to look for the interface name.
                        while RTA_OK(retrta, attlen) {
                            if (retrta->rta_type == IFLA_IFNAME) {
                                strcpy(prname, RTA_DATA(retrta));
                                printf("on %s\n", prname);
                                exit(EXIT_SUCCESS);
                            }
                            retrta = RTA_NEXT(retrta, attlen);

                        }
                    }

                    retmsg = NLMSG_NEXT(retmsg, len);       
                }

            }
        }
        retrta = RTA_NEXT(retrta, attlen);

    }

    retmsg = NLMSG_NEXT(retmsg, len);       
}

}   