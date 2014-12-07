#pragma once

#include <stdexcept>
#include <iterator>
#include <numeric>

#include "../../../flip.hpp"

namespace functional {
    namespace list {

        struct {

            template <class F, class C>
            auto operator()(const F & f, const C & c) const {
                using std::out_of_range;
                using std::next;
                using std::accumulate;

                if (c.empty())
                    throw(out_of_range(__func__));

                return accumulate(next(c.begin()), c.end(), c.front(), flip(f));
            }

        } foldl1;

    }
}
