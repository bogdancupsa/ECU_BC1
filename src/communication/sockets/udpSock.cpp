#include "udpSock.h"
#include <stdlib.h>
#include <stdio.h>

UDPSocket::UDPSocket(unsigned short port, bool bind_socket)
{
    // socket creation
    socket_fd_ = socket(AF_INET, SOCK_DGRAM, 0);

    if (socket_fd_ < 0)
    {
        printf("Error creating socket\n");
        exit(0);
    }

    // address structure
    std::memset(&addr_, 0, sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    addr_.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind_socket)
    { 
        if (bind(socket_fd_, 
            reinterpret_cast<struct sockaddr*>(&addr_),
            sizeof(addr_)) < 0)
        {
            throw std::runtime_error("Error binding socket");
        }
    }
}

UDPSocket::~UDPSocket()
{
    close(socket_fd_);
}

void UDPSocket::send(const std::string& ip, unsigned short port, const uint8_t* message, size_t message_size)
{
    struct sockaddr_in dest_addr;
    std::memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    inet_aton(ip.c_str(), &dest_addr.sin_addr);

    ssize_t sent_size = sendto(
        socket_fd_,
        message,
        message_size,
        0,
        (const sockaddr*)&dest_addr,
        sizeof(dest_addr)
    );

    if (sent_size < 0) {
        perror("Error sending message");
    }
}

std::string UDPSocket::receive()
{
    char buffer[1024];
    struct sockaddr_in in_addr;
    socklen_t len = sizeof(in_addr);

    ssize_t n = recvfrom(
        socket_fd_,
        buffer,
        sizeof(buffer) - 1,
        0,
        reinterpret_cast<sockaddr*>(&in_addr),
        &len
    );

    if (n < 0) {
        perror("Error receiving message");
        return "";
    }

    buffer[n] = '\0';
    std::cout << "Received: " << buffer << std::endl;
    return std::string(buffer);
}
