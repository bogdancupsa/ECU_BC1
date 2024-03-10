#ifndef HIGH_RESOLUTION_TIMER_H
#define HIGH_RESOLUTION_TIMER_H

#include <chrono>
#include <thread>
#include <atomic>
#include "EventSetter.h"

class HighResolutionTimer {
    public:
        HighResolutionTimer(EventSetter& eventSetter) : eventSetter_(eventSetter), running_(false) {}
        void start                  (void);
        void stop                   (void);

    private:
        void timerLoop              (void);

        EventSetter&      eventSetter_;
        std::thread       timerThread_;
        std::atomic<bool> running_;
};

#endif // HIGH_RESOLUTION_TIMER_H