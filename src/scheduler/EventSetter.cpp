#include "EventSetter.h"

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
    if (cv_1ms_.wait_for(lock, std::chrono::milliseconds(0), [this] {
        
            return event_1ms_; 
        
        })) 
    {
        event_1ms_ = false; // reset event
        return true;
    }

    return false;

}

bool EventSetter::check10msEvent(void) {

    std::unique_lock<std::mutex> lock(mtx_);
    if (cv_10ms_.wait_for(lock, std::chrono::milliseconds(0), [this] { // wait for cu 0 duration => thread-ul nu se blocheaza in cazul in care eventul nu se seteaza
        
            return event_10ms_; 
        
        })) 
    {
        event_10ms_ = false; // reset event
        return true;
    }

    return false;

}