#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "EventSetter.h"

class Scheduler {
    public:
        HighResolutionTimer    highResTimer;
        EventSetter            eventSetter;
        bool                   exitCondition = false;

        void initialize        ( void );
        void run               ( void );
        void shutdown          ( void );
};

#endif // SCHEDULER_H