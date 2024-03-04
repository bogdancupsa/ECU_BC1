#include "EventStter.h"

EventSetter::EventSetter() {
    // no init code needed
    // events set to false in the class definition
}

void EventSetter::set1msEvent() {

    std::lock_guard<std::mutex> lock(mtx_);
    event_1ms_ = true;

    cv_1ms_.notify_one();

}

void EventSetter::set10msEvent(void) {

    std::lock_guard<std::mutex> lock(mtx_);
    event_10ms_ = true;

    cv_10ms_.notify_one();
    
}

bool EventSetter::check1msEvent(void) {

    std::unique_lock<std::mutex> lock(mtx_);
    cv_1ms_.wait(lock, [this] { // wait automotically suspends the
        return event_1ms_;      // execution of the thread
    });
    cv_1ms_ = false;
    
    return true;

}

bool EventSetter::check10msEvent(void) {

    std::unique_lock<std::mutex> lock(mtx_);
    cv_10ms_.wait(lock, [this] {
        return event_10ms_;
    });
    cv_10ms_ = false;
    
    return true;

}