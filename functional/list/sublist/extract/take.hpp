#pragma once

#include "../../../compose.hpp"

namespace functional {
    namespace list {

        struct _take: composable<2, _take> {

            template <class C>
            auto operator()(typename C::difference_type n, const C & c) const {
                using std::min;
                using std::distance;
                using std::advance;

                auto end = c.begin();
                advance(end, min(n, distance(c.begin(), c.end())));

                return C { c.begin(), end };
            }

        } take;

    }
}
