#pragma once

#include <numeric>

#include "../../../flip.hpp"

namespace functional {
    namespace list {

        struct {

            template <class F, class V, class C>
            auto operator()(const F & f, const V & v, const C & c) const {
                using std::accumulate;

                return accumulate(c.begin(), c.end(), v, flip(f));
            }

        } foldl;

    }
}
