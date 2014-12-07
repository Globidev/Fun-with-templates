#pragma once

#include <iterator>

namespace functional {
    namespace list {

        struct {

            template <class C>
            auto operator()(const C & c) const {
                using std::distance;

                return distance(c.begin(), c.end());
            }

        } length;

    }
}


