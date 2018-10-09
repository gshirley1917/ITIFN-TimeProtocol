#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

void timeProtocolUDPServer();
void error(const char * msg);

int main(int argc, char *argv[]){
     while(true){
         timeProtocolUDPServer();
     }
}

void timeProtocolUDPServer(){
    int port = 37;
    int maxLength = 1024;
    struct protoent * proto;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientLength;

    char buffer[maxLength];

    proto = getprotobyname("udp");
    int sockForward = socket(PF_INET, SOCK_DGRAM, proto->p_proto);
    if(sockForward < 0){
        error("Error opening socket");
        return;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if(bind(sockForward, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0){
        error("Error on binding");
        return;
    }

    listen(sockForward, 4);

    clientLength = sizeof(clientAddr);

    int newSocketForward = accept(sockForward, (struct sockaddr *) &clientAddr, &clientLength);
    if(newSocketForward < 0){
        error("Error on accepting socket");
        return;
    }

    bzero(buffer, maxLength);

    int in = read(newSocketForward, buffer, maxLength - 1);
    if(in < 0){
        error("Error on reading from socket");
    }

    //TODO write time instead of buffer and length
    int out = write(newSocketForward, buffer, maxLength);
    cout << in << endl;
    if(out < 0){
        error("Error on writing to socket");
    }

    close(newSocketForward);
    close(sockForward);
}




void error(const char * error){
    perror(error);
    exit(1);
}

