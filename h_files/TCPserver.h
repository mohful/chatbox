#ifndef SERVER_H
#define SERVER_H

#include <string>

class TCPServer {
public:
    TCPServer(int port);
    void start();
    void stop();
    
private:
    int serverSocket;
    int port;
    bool running;
    
    void handleClient(int clientSocket);
};

#endif // SERVER_H
