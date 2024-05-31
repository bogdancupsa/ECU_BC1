#ifndef SOMEIP_SERVICE_H
#define SOMEIP_SERVICE_H

#include <stdlib.h>
#include <stdio.h>
#include "udpSock.h"

#define SOMEIP_MSG_SIZE 0xFF  

enum MessageType 
{  
    REQUEST   = 0x00,
    RESPONSE  = 0x01 
};

struct SomeIPHeader
{
    uint32_t message_id;
    uint32_t length;
    uint8_t  protocol_version;
    uint8_t  message_type;
    uint8_t  return_code;
};

struct SomeIPMessage
{
    SomeIPHeader someip_header;
    uint8_t someip_payload[SOMEIP_MSG_SIZE];
};

void          serialize_message    (SomeIPMessage* deserialized_msg, uint8_t* serialized_msg);
void          deserialize_message  (const uint8_t* serialized_msg, SomeIPMessage* deserialized_msg);
void          send_someip_msg      (SomeIPMessage* message, const char* ip, unsigned short port);
SomeIPMessage receive_someip_msg   (void);


#endif // SOMEIP_SERVICE_H