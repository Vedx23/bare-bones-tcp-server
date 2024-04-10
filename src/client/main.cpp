#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    // create a socket
    int soc = socket(AF_INET, SOCK_STREAM, 0);
    if (soc == -1)
    {
        cout << "error creating a socket" << endl;
        return -1;
    }
    // create a hint structure for the server to be connected with
    int port = 54000;               // server to which we are connecting to
    string ipAddress = "127.0.0.1"; // localhost
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
    // connect to the server on the socket

    int connectRes = connect(soc, reinterpret_cast<sockaddr *>(&hint), sizeof(hint));
    if (connectRes == -1)
    {
        return 1;
    }

    // while loop:
    // enter lines of text
    // send to the server
    // wait for the response from the server
    // display the response

    char buf[4096];
    string userInput;

    do {
    cout << ">";
    getline(cin, userInput);
    int sendRes = send(soc, userInput.c_str(), userInput.size() + 1, 0);
    if (sendRes == -1) {
        cout << "couldnt connect to the server" << endl;
        continue;
    }
    memset(buf, 0, 4096);
    int bytesReceived = recv(soc, buf, 4096, 0);
    if (bytesReceived == -1) {
        cout << "there was an error getting a response from server" << endl;
    } else {
        cout << "server> " << string(buf, bytesReceived) << endl;
    }
} while (true);


    // close the socket
    close(soc);
    return 0;
}
