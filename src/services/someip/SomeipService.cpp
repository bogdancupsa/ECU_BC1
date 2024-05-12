#include "SomeipService.h"
#include <stdlib.h>
#include <stdio.h>

void serialize_message (SomeIPMessage* deserialized_msg, uint8_t* serialized_msg)
{

    memcpy(&serialized_message, &deserialized_message.someip_header, sizeof(deserialized_message.someip_header));
  
    memcpy(&serialized_message + sizeof(deserialized_message.someip_header), &deserialized_message.someip_payload, sizeof(deserialized_message.someip_header.length));

}


void deserialize_message (uint8_t* serialized_msg, SomeIPMessage* deserialized_msg)
{

    memcpy(&deserialized_message.someip_header, &serialized_message, sizeof(deserialized_message.someip_header));

    memcpy(&deserialized_message.someip_payload, &serialized_message + sizeof(deserialized_message.someip_header), message.header.length);

}

void send_someip_msg (SomeIPMessage* message) 
{
    UDPSocket socket(12345);
    uint8_t buffer[1024];

    serialize_message(&message, &buffer);
    socket.send("192.168.1.11", 12345, buffer);
}

void receive_someip_msg (void)
{
    UDPSocket socket(12345);
    uint8_t buffer[1024];
    SomeIPMessage message;

    socket.receive(buffer);
    deserialize_message(&buffer, &message);
}