#pragma once

#include <algorithm>
#include <iterator>

#include "../../compose.hpp"

namespace functional {
    namespace list {

        static struct _append: composable<2, _append> {

            template <class C>
            auto operator()(const C & c1, const C & c2) const {
                using std::distance;
                using std::copy;

                auto c1_size = distance(c1.begin(), c1.end());
                auto c2_size = distance(c2.begin(), c2.end());
                C r(c1_size + c2_size);

                auto end = copy(c1.begin(), c1.end(), r.begin());
                copy(c2.begin(), c2.end(), end);

                return r;
            }

        } append;

    }
}
