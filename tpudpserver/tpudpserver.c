#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

void timeProtocolUDPServer();
void error(const char * msg);

int main(int argc, char *argv[]){
    //The server will run until it is shut down
     while(1){
         printf("Listening on port 37 \n");
         timeProtocolUDPServer();
     }
}

void timeProtocolUDPServer(){
    //Define port and max length of buffer
    int port = 37;
    int maxLength = 1024;

    //Create sockets, buffer, and lengths
    struct protoent * proto;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientLength;
    int sockLength = sizeof(clientAddr);
    char buffer[maxLength];

    //Open the UDP socket
    proto = getprotobyname("udp");
    int sockForward = socket(PF_INET, SOCK_DGRAM, proto->p_proto);
    if(sockForward < 0){
        error("Error opening socket");
        return;
    }

    //Defining the servers attributes
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    //Bind the socket
    if(bind(sockForward, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0){
        error("Error on binding");
        return;
    }

    //Listen to the socket with a max of 4 clients
    listen(sockForward, 4);

    //Used when receiving data
    clientLength = sizeof(clientAddr);

    //Receive the packet, only to obtain the IP address of the client
    int blen = recvfrom(sockForward, buffer, maxLength, 0, (struct sockaddr*) &clientAddr, &sockLength);
    if(blen < 0){
        error("Error on receiving data");
    }

    //Pull out the destination IP
    char * destination = inet_ntoa(clientAddr.sin_addr);

    //Get the current time and send it through the socket
    //Time stored as an unsigned 32 bit integer
    uint32_t currentTime = time(NULL);
    if(sendto(sockForward, (char *) &currentTime, (int)sizeof(currentTime), 0, (struct sockaddr *) &clientAddr, clientLength) == (int)sizeof(currentTime)){
        printf("Time sent: %d\n", currentTime);
    }

    //Close the socket
    close(sockForward);
    printf("End data \n");
    printf("\n");
}




void error(const char * error){
    perror(error);
    exit(1);
}

