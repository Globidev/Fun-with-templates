#pragma once

#include <algorithm>
#include <iterator>
#include <tuple>

#include "../../../compose.hpp"

namespace functional {
    namespace list {

        struct _split_at: composable<2, _split_at> {

            template <class C>
            auto operator()(typename C::difference_type n, const C & c) const {
                using std::min;
                using std::distance;
                using std::advance;
                using std::make_tuple;

                auto mid = c.begin();
                advance(mid, min(n, distance(c.begin(), c.end())));

                return make_tuple(C { c.begin(), mid }, C { mid, c.end() });
            }

        } split_at;

    }
}
