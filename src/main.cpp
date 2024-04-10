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
        return -1;
    }

    // 2. give some ip and port to the socket
    sockaddr_in hint; 
    hint.sin_family = AF_INET; //set the family to IPV4
    hint.sin_port = htons(54000); //host to nextwork short 
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);//convert an ip address to a string
    //hint.sin_addr is a buffer

    if( bind(listening,reinterpret_cast<sockaddr*>(&hint), sizeof(hint))){
        std::cerr<<"cannot bind to IP/port"<<std::endl;
        return -2;
    }
    // 3. start listening in on the socket
    // 4. accept a connection on the socket
    // 5. close the socket for listening
    // 6. display the receiving message
    // 7. close the socket
    
    std::cout<<"hello world"<<std::endl;
    return 0;
}
