#pragma once

#include <iostream>
#include <chrono>

namespace tools {

    struct benchmark {

        using Clock = std::chrono::high_resolution_clock;

        benchmark(const std::string & description):
            description_(description), t0_(Clock::now()) { }

        ~benchmark() {
            using std::cout;
            using std::endl;
            using std::chrono::duration_cast;
            using nanoseconds = std::chrono::nanoseconds;

            auto t1 = Clock::now();
            auto duration = duration_cast<nanoseconds>(t1 - t0_);

            cout << description_ << ": " << duration.count() << " ns" << endl;
        }

    private:

        std::string description_;
        Clock::time_point t0_;

    };

}
