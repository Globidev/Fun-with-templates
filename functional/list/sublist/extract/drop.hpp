#pragma once

#include <iterator>

#include "../../../compose.hpp"

namespace functional {
    namespace list {

        static struct _drop: composable<2, _drop> {

            template <class C>
            auto operator()(typename C::difference_type n, const C & c) const {
                using std::distance;
                using std::advance;

                auto size = distance(c.begin(), c.end());
                if (n > size)
                    return C{};

                auto start = c.begin();
                advance(start, n);

                return C { start, c.end() };
            }

        } drop;

    }
}
