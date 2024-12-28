#ifndef TIMER_H
#define TIMER_H

#include <chrono>

template <typename T>

/// Base Timer class that measures elapsed time
class Timer {
public:
    /// Constructor to initialize the start time
    Timer() : start_time(std::chrono::high_resolution_clock::now()) {}

    /// Method to get the elapsed time as a template data type
    T elapsed_time() {
        auto end_time = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<T>(end_time - start_time);
    }

private:
    /// Start time point
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};

#endif ///TIMER_H
