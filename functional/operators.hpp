#pragma once

#include <cstdlib>

namespace functional {

    template <int N> struct plus {
        template <class T> struct f {
            T operator()(const T & t) { return t + N; }
        };
    };

    template <int N> struct minus {
        template <class T> struct f {
            T operator()(const T & t) { return t - N; }
        };
    };

    template <class T, class T2 = T> struct diff {
        T operator()(const T & t1, const T2 & t2) { return std::abs(t1 - t2); }
    };

};
