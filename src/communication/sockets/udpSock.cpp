#include "udpSock.h"
#include <stdlib.h>
#include <stdio.h>

UDPSocket::UDPSocket(unsigned short port) 
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

    // bind
    if ( bind(socket_fd_, 
             reinterpret_cast<struct sockaddr*>(&addr_),
             sizeof(addr_) ) < 0 )
    {
        throw std::runtime_error("Error binding socket");
    }
}

void UDPSocket::send (const std::string& ip, unsigned short port, const std::string& message)
{
    struct sockaddr_in dest_addr;
    std::memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);

    inet_aton(ip.c_str(), &dest_addr.sin_addr);

    sendto( 
        socket_fd_, 
        message.c_str(), 
        message.length(), 
        0, 
        reinterpret_cast<const sockaddr*>(&dest_addr), 
        sizeof(dest_addr)
    );
}

void UDPSocket::receive (void)
{
    char buffer[1024];
    struct sockaddr_in in_addr;

    socklen_t len = sizeof(in_addr);

    ssize_t n = recvfrom(
            socket_fd_, buffer, 
            sizeof(buffer) - 1, 
            0, 
            reinterpret_cast<sockaddr*>(&addr_), 
            &len
        );

    buffer[n] = '\0';
    std::cout << "Received: " << buffer << std::endl;
}