#include "SomeipService.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <cstdlib>

void serialize_message (SomeIPMessage* deserialized_msg, uint8_t* serialized_msg)
{

    std::memcpy(serialized_msg, &(deserialized_msg->someip_header), sizeof(deserialized_msg->someip_header));
  
    std::memcpy(serialized_msg + sizeof(deserialized_msg->someip_header), deserialized_msg->someip_payload, deserialized_msg->someip_header.length);
std::cout << "Message serialized" << std::endl;
}

void deserialize_message (const uint8_t* serialized_msg, SomeIPMessage* deserialized_msg)
{

    std::memcpy(&(deserialized_msg->someip_header), serialized_msg, sizeof(deserialized_msg->someip_header));

    std::memcpy(deserialized_msg->someip_payload, serialized_msg + sizeof(deserialized_msg->someip_header), deserialized_msg->someip_header.length);
std::cout << "Message deserialized" << std::endl;
}

void send_someip_msg (SomeIPMessage* message, const char* ip, unsigned short port) 
{
    UDPSocket socket(12346); /* default no binding for sender*/
    uint8_t buffer[1024];

    serialize_message(message, buffer);
    std::cout << "Sending SOME/IP message to " << ip << ":" << port << std::endl;
    socket.send(ip, port, buffer, sizeof(buffer));
}

SomeIPMessage receive_someip_msg (void)
{
    UDPSocket socket(12345);
    SomeIPMessage message;

    std::string data = socket.receive(); 

    if (!data.empty())
    {
        deserialize_message(reinterpret_cast<const uint8_t*>(data.c_str()), &message);
    }

    return message;
}