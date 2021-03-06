#pragma once

#include <iterator>

#include "../../compose.hpp"

namespace functional {
    namespace list {

        static struct _intersperse: composable<2, _intersperse> {

            template <class V, template <class...> class C>
            auto operator()(const V & v, const C<V> & c) const {
                using std::distance;

                auto size = distance(c.begin(), c.end());
                auto new_size = size >= 2 ? size * 2 - 1 : size;
                C<V> r(new_size);

                auto it_ref = c.begin();
                decltype(size) i = 0;
                for (auto it = r.begin(); it != r.end(); ++it)
                    *it = (i++ % 2 == 0 ? *(it_ref++) : v);

                return r;
            }

        } intersperse;

    }
}
