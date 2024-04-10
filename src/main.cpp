#include<iostream>
#include<sys/types.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<string.h>
#include<string>

int main(int argc, char const *argv[])
{
    // 1. create  socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if(listening == -1) {
        std::cerr<<"error creating a socket"<<std::endl;
    }


    // 2. give some ip and port to the socket
    // 3. start listening in on the socket
    // 4. accept a connection on the socket
    // 5. close the socket for listening
    // 6. display the receiving message
    // 7. close the socket
    
    std::cout<<"hello world"<<std::endl;
    return 0;
}
