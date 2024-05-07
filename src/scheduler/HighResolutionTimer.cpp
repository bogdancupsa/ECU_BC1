#include "HighResolutionTimer.h"
#include <iostream>

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

void HighResolutionTimer::timerLoop() {
    using namespace std::chrono;

    auto last1msTick = steady_clock::now();
    auto last10msTick = last1msTick;

    while (running_) {
        auto now = steady_clock::now();

        if (now - last1msTick >= milliseconds(1)) {
            eventSetter_.set1msEvent();
            last1msTick += milliseconds(1);
        }

        if (now - last10msTick >= milliseconds(10)) {
            eventSetter_.set10msEvent();
            last10msTick += milliseconds(10);
        }

        std::this_thread::sleep_until(last1msTick);
    }
}



