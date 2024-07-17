#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "EventSetter.h"
#include "HighResolutionTimer.h"
#include "udpSock.h"
#include <stdlib.h>
#include <stdio.h>

/* #define TEST_SESSION_ACTIVE
 * TEST_SESSION_ACTIVE 1 => testing
 * TEST_SESSION_ACTIVE 0 => no testing - normal functioning of ECU
*/
#define TEST_SESSION_ACTIVE 1

class Scheduler {
    public:
        HighResolutionTimer    highResTimer;
        EventSetter            eventSetter;
        bool                   exitCondition = false;

        Scheduler() : eventSetter(), 
                      highResTimer(eventSetter) {}

        void initialize        ( void );
        void run               ( void );
        void shutdown          ( void );
};

#endif // SCHEDULER_H