#include "Scheduler.h"
// #include "SomeipService.h"
// #include "CanService.h"
#include "Tasks.h"

void Scheduler::initialize (void) 
{
    highResTimer.start();
    // TODO - initialize someipService
    // TODO - initialize canService
}

void Scheduler::run (void) 
{
    while (!exitCondition) {
        if ( eventSetter.check1msEvent() ) {
            execute1msTask();
        }

        if ( eventSetter.check10msEvent() ) {
            execute10msTask();
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