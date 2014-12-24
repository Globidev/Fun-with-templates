#pragma once

#include <algorithm>
#include <tuple>

#include "../../compose.hpp"

namespace functional {
    namespace list {

        static struct _partition: composable<2, _partition> {

            template <class F, class C>
            auto operator()(const F & pred, C c) const {
                using std::stable_partition;
                using std::make_tuple;

                auto mid = stable_partition(c.begin(), c.end(), pred);

                return make_tuple(C { c.begin(), mid }, C { mid, c.end() });
            }

        } partition;

    }
}
