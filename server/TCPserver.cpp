#include "../h_files/TCPserver.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

TCPServer::TCPServer(int port) : port(port), running(false) {}

void TCPServer::start() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return;
    }
    
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);
    
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error binding socket" << std::endl;
        return;
    }
    
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Error listening on socket" << std::endl;
        return;
    }
    
    running = true;
    std::cout << "Server started, listening on port " << port << std::endl;
    
    while (running) {
        sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        
        if (clientSocket == -1) {
            std::cerr << "Error accepting client connection" << std::endl;
            continue;
        }
        
        handleClient(clientSocket);
        close(clientSocket);
    }
}

void TCPServer::stop() {
    running = false;
}

void TCPServer::handleClient(int clientSocket) {
    char buffer[4096];

    // Receive data from the client
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived == -1) {
            std::cerr << "Error receiving data from client" << std::endl;
            return;
        }

        if (bytesReceived == 0) {
            std::cout << "Client disconnected" << std::endl;
            return;
        }

        // Process the received data (you can replace this with your custom logic)
        std::cout << "Received message from client: " << buffer << std::endl;

        // Send a response back to the client (you can customize the response)
        std::string response = "Server received your message: ";
        response += buffer;
        send(clientSocket, response.c_str(), response.size(), 0);
    }
    // Close the connection with the client
    close(clientSocket);
}

int main() {
    TCPServer server(8888);
    server.start();
}