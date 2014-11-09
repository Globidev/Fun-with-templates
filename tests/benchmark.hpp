#pragma once

#include <iostream>
#include <sstream>
#include <chrono>

#include "tools/locale.hpp"

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

        std::cout << description_ << ": " << duration.count() << " ns"
                  << std::endl;
    }

private:
    std::string description_;
    Clock::time_point t0_;
};

template <
    uint n = 1,
    class F,
    class... Args,
    class R = typename std::result_of<F(Args...)>::type
>
R benchmark(const std::string & description, F && f, Args &&... args)
{
    std::ostringstream oss;
    oss.imbue(locale);
    oss << description << " (" << n << " times)";
    Benchmark b { oss.str() };

    std::vector<R> r(n);
    uint i = 0;
    while (i < n)
        r[i++] = f(std::forward<Args>(args)...);

    return r[0];
}
