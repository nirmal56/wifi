#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>

using namespace std;

string givemeIp(char *name){
    struct ifreq ifr;
    int sock_id = socket(AF_INET, SOCK_DGRAM, 0);

    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, name, IFNAMSIZ -1);
    ioctl(sock_id, SIOCGIFADDR, &ifr);
    close(sock_id);

    return inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr);

}

int main()
{
    cout<<givemeIp("enp0s3")<<endl;
    int n;
    
    //code for ifname to ip
    struct ifreq ifr;
    char array[] = "enp0s3";
 
    n = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name , array , IFNAMSIZ - 1);
    ioctl(n, SIOCGIFADDR, &ifr);
    close(n);
    //display result
    printf("IP Address is %s - %s\n" , array , inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr) );
    return 0;
}