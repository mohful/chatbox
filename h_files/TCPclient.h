#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class TCPClient {
public:
    TCPClient(const std::string& ipAddress, int port);
    void connectToServer();
    void sendMessage(const std::string& message);
    std::string receiveMessage();
    void closeConnection();
    void run();
    
private:
    int clientSocket;
    std::string ipAddress;
    int port;
};

#endif // CLIENT_H
