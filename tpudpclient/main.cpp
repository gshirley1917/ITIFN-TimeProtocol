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
    timeProtocolUDPClient(argv[1]);
    return 0;
}

void timeProtocolUDPClient(const char address[]){
    //Initial variable definitions

    //UDP uses port 37
    int port = 37;
    int maxLength = 1024;

    //Buffer for outgoing and incoming messages
    unsigned char msg[48]={010,0,0,0,0,0,0,0,0};
    unsigned long buffer[maxLength];

    //From netdb.h, just sets up the protocol, in this case udp
    struct protoent * proto;

    //From netinet/in.h, used for socket setup
    struct sockaddr_in server_addr;

    //Socket and time limit variables, timeLimit used similar to a time_t
    int sock;
    long timeLimit;

    //From netdb, set the protocol and the socket, PF_INET is protocol family, SOCK_DGRAM is socket datagram, p_proto is the protocol number
    proto = getprotobyname("udp");
    sock = socket(PF_INET, SOCK_DGRAM, proto->p_proto);
    
    //Just sets the memeory starting at &server_addr with a size of server_addr to 0 
    memset( &server_addr, 0, sizeof(server_addr));
    
    //Socket in family to address family
    server_addr.sin_family=AF_INET;

    //Socket address is the internet address of what is given to the program
    server_addr.sin_addr.s_addr = inet_addr(address);

    //Socket port is the port specified, 123 because of UDP
    server_addr.sin_port=htons(port);

    //Send to the socket the buffer, its length, any flags (0), socket address, and the length of that address
    //From sys/socket.h
    int i = sendto(sock, msg, sizeof(msg), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    //From sys/socket.h, gives a way to recieve the data
    struct sockaddr socketAddr;
    socklen_t socketAddr_l = sizeof(socketAddr);

    //From sys/socket.h
    //Receive on the socket into the buffer a message of size 48 with no flags into socketAddr with a length of socketAddr_l
    i = recvfrom(sock, buffer, 48, 0, &socketAddr,&socketAddr_l);

    //Get the transmit time
    timeLimit = ntohl((time_t)buffer[4]);

    //Subtract 2208988900 (unsigned) for formatting purposes
    timeLimit -= 2208988800U;
    
    //Output the time in a readable format
    cout << "NTP time is " << ctime(&timeLimit) << endl;

    //Output the difference between the system time
    i = time(0);
    cout << "System time is " << (i - timeLimit) << " seconds off" << endl;
}