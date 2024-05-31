#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>

class UDPSocket {
    public:
        UDPSocket(unsigned short port, bool bind_socket = false);
        ~UDPSocket();

        void        send    (const std::string& ip, unsigned short port, const uint8_t* message, size_t message_size);
        std::string receive (void);

    private:
        int socket_fd_;
        struct sockaddr_in addr_;
};

#endif // UDPSOCKET_H