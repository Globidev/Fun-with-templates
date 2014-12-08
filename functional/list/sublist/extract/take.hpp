#pragma once

#include "../../../compose.hpp"

namespace functional {
    namespace list {

        struct _take: composable<2, _take> {

            template <class C>
            auto operator()(typename C::difference_type n, const C & c) const {
                using std::min;
                using std::distance;

                auto size = min(n, distance(c.begin(), c.end()));
                C r(size);
                auto in_it = c.begin();
                auto out_it = r.begin();

                while (size--)
                    *out_it++ = *in_it++;

                return r;
            }

        } take;

    }
}
