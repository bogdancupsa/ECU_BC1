#include "Scheduler.h"
// #include "SomeipService.h"
// #include "CanService.h"
#include "Tasks.h"
#include "udpSock.h"

// SomeipService someip_service;

void Scheduler::initialize (void) 
{  
    highResTimer.start();

    // TODO - initialize canService
}

void Scheduler::run (void) 
{
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