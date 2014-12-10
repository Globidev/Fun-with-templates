#pragma once

#include "../reduce/foldl.hpp"
#include "../../../compose.hpp"

namespace functional {
    namespace list {

        static struct _sum: composable<1, _sum> {

            template <class C>
            auto operator()(const C & c) const {
                return foldl([](auto a, auto b) { return a + b; }, 0, c);
            }

        } sum;

    }
}
