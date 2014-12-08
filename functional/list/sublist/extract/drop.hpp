#pragma once

#include "../../../compose.hpp"

namespace functional {
    namespace list {

        struct _drop: composable<2, _drop> {

            template <class C>
            auto operator()(typename C::difference_type n, const C & c) const {
                using std::distance;
                using std::advance;

                auto size = distance(c.begin(), c.end());
                if (n > size)
                    return C{};

                C r(size - n);
                auto in_it = c.begin();
                advance(in_it, n);
                auto out_it = r.begin();

                while (in_it != c.end())
                    *out_it++ = *in_it++;

                return r;
            }

        } drop;

    }
}
