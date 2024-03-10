#ifndef EVENTSETTER_H
#define EVENTSETTER_H

#include <mutex>
#include <condition_variable>
#include <chrono>

class EventSetter {
    public:
        EventSetter();
        void set1msEvent();
        void set10msEvent();
        bool check1msEvent();
        bool check10msEvent();

    private:
        std::condition_variable cv_1ms_;
        std::condition_variable cv_10ms_;
        std::mutex mtx_;
        bool event_1ms_ = false;
        bool event_10ms_ = false;
};

#endif // EVENTSETTER_H