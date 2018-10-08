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
}