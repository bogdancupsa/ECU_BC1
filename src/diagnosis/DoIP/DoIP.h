#ifndef DOIP_H
#define DOIP_H

#include <cstdint>
#include <cstring>
#include "udpSock.h"

#define DOIP_MSG_SIZE 0xFF

struct DoIPHeader {
    uint8_t protocol_version;
    uint8_t inverse_protocol_version;
    uint16_t payload_type;
    uint32_t payload_length;
};

struct DoIPMessage {
    DoIPHeader doip_header;
    uint8_t doip_payload[DOIP_MSG_SIZE];
};

void          serialize_doip    (DoIPMessage* deserialized_msg, uint8_t* serialized_msg);
void          deserialize_doip  (const uint8_t* serialized_msg, DoIPMessage* deserialized_msg);
void          send_doip         (DoIPMessage* message, const char* ip, unsigned short port);
DoIPMessage   receive_doip      (unsigned short port);

#endif // DOIP_H