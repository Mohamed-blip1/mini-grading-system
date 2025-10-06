#pragma once
// debug_time.h
#include <iostream>
#include <chrono>

#ifdef DEBUG
struct Time
{
    using steady_clock = std::chrono::steady_clock;
    using duration = std::chrono::duration<double, std::micro>;
    std::string name_;
    steady_clock::time_point tp_;

    Time(const std::string &st) noexcept
    {
        name_ = st;
        tp_ = steady_clock::now();
    };

    ~Time() noexcept
    {
        auto elapsed = steady_clock::now();
        std::cout << "time of '" << name_ << "': "
                  << duration(elapsed - tp_).count()
                  << "μs\n";
    };
};
#endif