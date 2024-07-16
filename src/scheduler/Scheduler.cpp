#include "Scheduler.h"
#include "SomeipService.h"
// #include "CanService.h"
#include "Tasks.h"
#include "udpSock.h"
#include "DoIP.h"
//bogdan
void Scheduler::initialize (void) 
{  
    highResTimer.start();

    // TODO - initialize canService
}

void Scheduler::run (void) 
{

#if TEST_SESSION_ACTIVE == 0

    SomeIPMessage request_msg;
    request_msg.someip_header.message_id = 1;
    request_msg.someip_header.length = 0;
    request_msg.someip_header.protocol_version = 1;
    request_msg.someip_header.message_type = REQUEST;
    request_msg.someip_header.return_code = 0;

#elif TEST_SESSION_ACTIVE == 1

    DoIPMessage request_msg;
    request_msg.doip_header.protocol_version = 0x02;
    request_msg.doip_header.inverse_protocol_version = 0xFD;
    request_msg.doip_header.payload_type = 0x0003; /*VIN*/
    request_msg.doip_header.payload_length = 0;

#endif
    
    
    UDPSocket sendSocket = UDPSocket(12345);

    while (!exitCondition) 
    {
        if ( eventSetter.check1msEvent() ) 
        {
            execute1msTask();
        }

        if ( eventSetter.check10msEvent() ) 
        {
            execute10msTask();
        }

        sendSocket.send("192.168.1.11", 12345, "Hello", 5);

#if TEST_SESSION_ACTIVE == 0

        send_someip_msg(&request_msg, "192.168.1.11", 12345);

        SomeIPMessage response_msg = receive_someip_msg();

        if (RESPONSE == response_msg.someip_header.message_type)
        {
            printf("Pedal status: %s", response_msg.someip_payload);
        }
#elif TEST_SESSION_ACTIVE == 1

        /* send request */
        send_doip(&request_msg, "192.168.1.11", 13400);

        /* get response */
        DoIPMessage response_msg = receive_doip(13401);
        if (0x0004 == response_msg.doip_header.payload_type)
        {
            std::cout << "received vin" << std::endl;
        }

#endif

    }

}

void Scheduler::shutdown (void) 
{
    highResTimer.stop();
}

int main (void) 
{
    Scheduler scheduler;
    
    scheduler.initialize();
    scheduler.run();
    scheduler.shutdown();

    return 0;
}