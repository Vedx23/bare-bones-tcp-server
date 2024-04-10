#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

int main(int argc, char const *argv[])
{
    // 1. create  socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        std::cerr << "error creating a socket" << std::endl;
        return -1;
    }

    // 2. give some ip and port to the socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;                     // set the family to IPV4
    hint.sin_port = htons(54000);                  // host to nextwork short
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr); // convert an ip address to a string
    // hint.sin_addr is a buffer

    if (bind(listening, reinterpret_cast<sockaddr *>(&hint), sizeof(hint)))
    {
        std::cerr << "cannot bind to IP/port" << std::endl;
        return -2;
    }
    // 3. start listening in on the socket
    if (listen(listening, SOMAXCONN) == -1)
    {
        std::cerr << "error while trying to listen" << std::endl;
        return -3;
    }
    // 4. accept a connection on the socket
    sockaddr_in client;
    socklen_t clientsize = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];

    int clientsocket = accept(listening, reinterpret_cast<sockaddr *>(&client), reinterpret_cast<socklen_t *>(&clientsize));

    if (clientsocket == -1)
    {
        std::cerr << "err connecting to client socket\n";
        return -4;
    }

    // 5. close the socket for listening
    close(listening);
    memset(host, 0, NI_MAXHOST);
    memset(svc, 0, NI_MAXSERV);

    int result = getnameinfo(reinterpret_cast<sockaddr*>(&client),sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV, 0);

    if(result){
        std::cout<< host << "connected on : " << svc <<std::endl; 
    }else{
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout<< host << "connected on : " << ntohs(client.sin_port)<< std::endl;
    }

    // 6. display the receiving message

    char buf[4096];
    while(true){
        //clear the buffer
        memset(buf, 0, 4096);
        //wait for a message
        int bytesRecv = recv(clientsocket, buf, 4096, 0);
        if(bytesRecv == -1){
            std::cerr << "there was a connection issue, message not received" <<std::endl;
            break;
        }

        if(bytesRecv == 0){
            std::cout<< "the client has been disconnected" <<std::endl;
            break;
        }

        //display message
        std::cout << "Received : " << std::string(buf, 0, bytesRecv) <<std::endl;
        //resend message
        send(clientsocket, buf, bytesRecv + 1, 0);
    }

    // 7. close the socket
    close(clientsocket);
    return 0;
}
