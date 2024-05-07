#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

class UDPSocket {
    public:
        UDPSocket(unsigned short port);

        void send    (const std::string& ip, unsigned short port, const std::string& message);
        void receive (void);

    private:
        int socket_fd_;
        struct sockaddr_in addr_;
};

#endif // UDPSOCKET_H