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

}

void deserialize_message (uint8_t* serialized_msg, SomeIPMessage* deserialized_msg)
{

    std::memcpy(&(deserialized_msg->someip_header), serialized_msg, sizeof(deserialized_msg->someip_header));

    std::memcpy(deserialized_msg->someip_payload, serialized_msg + sizeof(deserialized_msg->someip_header), deserialized_msg->someip_header.length);

}

void send_someip_msg (SomeIPMessage* message) 
{
    UDPSocket socket(12345);
    uint8_t buffer[1024];

    serialize_message(message, buffer);
    socket.send("192.168.1.11", 12345, buffer);
}

void receive_someip_msg (void)
{
    UDPSocket socket(12345);
    uint8_t buffer[1024];
    SomeIPMessage message;

    socket.receive();
    deserialize_message(buffer, &message);
}