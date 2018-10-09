#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <string.h>

using namespace std;

void timeProtocolUDPClient(const char address[]);

int main(int argc, const char * argv[]){
    if(argc != 2){
        cout << "Improper amount of arguments" << endl;
        return 1;
    }
    cout << argv[0] << endl;
    timeProtocolUDPClient(argv[1]);
    return 0;
}

void timeProtocolUDPClient(const char address[]){
    int port = 123;
    int maxLength = 1024;
    unsigned char msg[48]={010,0,0,0,0,0,0,0,0};
    unsigned long buffer[maxLength];
    struct protoent * proto;
    struct sockaddr_in server_addr;
    int socket;
    long timeLimit;

    proto = getprotobyname("udp");
    socket = socket(PF_INET, SOCK_DGRAM, proto->p_proto);
    
    memset( &server_addr, 0, sizeof( server_addr ));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(address);
    server_addr.sin_port=htons(port);

    int i = i=sendto(socket, msg, sizeof(msg), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    struct sockaddr socketAddr;
    socklen_t socketAddr_l = sizeof(socketAddr);
    i = recvfrom(socket, buffer, 48, 0, &socketAddr,&socketAddr_l);

    timeLimit = ntohl((time_t)buffer[4]); //# get transmit time
    timeLimit-= 2208988800U;
    cout << "NTP time is " << ctime(&timeLimit) << endl;
    i=time(0);
    cout << "System time is " << (i-tmit) << " seconds off" << endl;
 
}