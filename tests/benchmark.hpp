#pragma once

#include <iostream>
#include <chrono>

#include "tools/locale.hpp"

template <size_t n>
struct Benchmark
{
    using Clock = std::chrono::high_resolution_clock;

    Benchmark(const std::string & description):
        description_(description), t0_(Clock::now()) {}

    ~Benchmark()
    {
        using nanoseconds = std::chrono::nanoseconds;

        auto t1 = Clock::now();
        auto duration = std::chrono::duration_cast<nanoseconds>(t1 - t0_);

        std::cout << description_ << " (" << n << " times)"
                  << ": " << duration.count() << " ns" << std::endl;
    }

private:
    std::string description_;
    Clock::time_point t0_;
};
