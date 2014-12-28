#pragma once

#include <numeric>

#include "../../../compose.hpp"

namespace functional {
    namespace list {

        static struct _foldl: composable<3, _foldl> {

            template <class F, class V, class C>
            auto operator()(const F & f, const V & v, const C & c) const {
                using std::accumulate;

                return accumulate(c.begin(), c.end(), v, f);
            }

        } foldl;

    }
}
