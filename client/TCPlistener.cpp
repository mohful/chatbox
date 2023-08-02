#include "../h_files/TCPclient.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

TCPClient::TCPClient(const std::string& ipAddress, int port) : ipAddress(ipAddress), port(port) {}

void TCPClient::connectToServer() {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return;
    }
    
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &serverAddr.sin_addr);
    
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error connecting to server" << std::endl;
        return;
    }
}

void TCPClient::sendMessage(const std::string& message) {
    send(clientSocket, message.c_str(), message.size(), 0);
}

std::string TCPClient::receiveMessage() {
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived == -1) {
        std::cerr << "Error receiving message" << std::endl;
        return "";
    }
    
    return std::string(buffer, bytesReceived);
}

void TCPClient::closeConnection() {
    close(clientSocket);
}

void TCPClient::run() {
    connectToServer();
    while (true) {
        std::string message;
        std::cout << "Enter a message to send to the server (type 'exit' to quit): ";
        std::getline(std::cin, message);

        if (message == "exit") {
            break; // Exit the loop and close the connection
        }

        sendMessage(message);

        std::string response = receiveMessage();
        std::cout << "Server response: " << response << std::endl;
    }

    closeConnection();
}

int main() {
    TCPClient client("127.0.0.1", 8888);
    client.run();
}