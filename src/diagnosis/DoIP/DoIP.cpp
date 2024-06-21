#include "DoIP.h"
#include <iostream>
#include <cstdlib>

void serialize_doip (DoIPMessage* deserialized_msg, uint8_t* serialized_msg)
{
    std::memcpy(serialized_msg, &(deserialized_msg->doip_header), sizeof(deserialized_msg->doip_header));

    std::memcpy(serialized_msg + sizeof(deserialized_msg->doip_header), deserialized_msg->doip_payload, deserialized_msg->doip_header.payload_length);
}

void deserialize_doip (const uint8_t* serialized_msg, DoIPMessage* deserialized_msg)
{
    std::memcpy(&(deserialized_msg->doip_header), serialized_msg, sizeof(deserialized_msg->doip_header));

    std::memcpy(deserialized_msg->doip_payload, serialized_msg + sizeof(deserialized_msg->doip_header), deserialized_msg->doip_header.payload_length);
}

void send_doip (DoIPMessage* message, const char* ip, unsigned short port)
{
    UDPSocket socket(port);
    uint8_t buffer[1024];

    serialize_doip(message, buffer);
    socket.send(ip, port, buffer, sizeof(buffer));
}

DoIPMessage receive_doip (unsigned short port)
{
    UDPSocket socket(port);
    DoIPMessage doip_msg;

    std::string data = socket.receive();

    deserialize_doip(reinterpret_cast<const uint8_t*>(data.c_str()), &doip_msg);

    return doip_msg;
}