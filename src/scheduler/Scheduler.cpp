#include "Scheduler.h"
#include "SomeipService.h"
// #include "CanService.h"
#include "Tasks.h"
#include "udpSock.h"

void Scheduler::initialize (void) 
{  
    highResTimer.start();

    // TODO - initialize canService
}

void Scheduler::run (void) 
{
    // UDPSocket sendSocket = UDPSocket(12345);
    
    SomeIPMessage request_msg;
    request_msg.someip_header.message_id = 1;
    request_msg.someip_header.length = 0;
    request_msg.someip_header.protocol_version = 1;
    request_msg.someip_header.message_type = REQUEST;
    request_msg.someip_header.return_code = 0;
    
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

        send_someip_msg(&request_msg, "192.168.1.11", 12345);

        SomeIPMessage response_msg = receive_someip_msg();

        if (RESPONSE == response_msg.someip_header.message_type)
        {
            printf("Pedal status: %s", response_msg.someip_payload);
        }

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