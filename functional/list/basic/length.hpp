#pragma once

#include <iterator>

#include "../../compose.hpp"

namespace functional {
    namespace list {

        static struct _length: composable<1, _length> {

            template <class C>
            auto operator()(const C & c) const {
                using std::distance;

                return distance(c.begin(), c.end());
            }

        } length;

    }
}


