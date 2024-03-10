#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "EventSetter.h"
#include "HighResolutionTimer.h"

class Scheduler {
    public:
        HighResolutionTimer    highResTimer;
        EventSetter            eventSetter;
        bool                   exitCondition = false;

        Scheduler() : eventSetter(), highResTimer(eventSetter) {}

        void initialize        ( void );
        void run               ( void );
        void shutdown          ( void );
};

#endif // SCHEDULER_H