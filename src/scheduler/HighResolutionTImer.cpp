#include "HighResolutionTimer.h"

void HighResolutionTimer::start (void) {

    running_ = true;
    timerThread_ = std::thread(&HighResolutionTimer::timerLoop, this);

}

void HighResolutionTimer::stop (void) {

    running_ = false;
    if (timerThread_.joinable()) {
        timerThread_.join();
    }

}

void HighResolutionTimer::timerLoop (void) {

    using namespace std::chrono;
    auto next1ms = steady_clock::now();
    auto next10ms = next1ms;

    while (running_) {
        auto now = steady_clock::now()

        if (now >= next1ms) {
            eventSetter_.set1msEvent();
            next1ms += milliseconds(1);
        }

        if (now >= next10ms) {
            eventSetter_.set10msEvent();
            next10ms += milliseconds(10);
        }
    }

    std::this_thread::sleep_for(microseconds(100));

}   