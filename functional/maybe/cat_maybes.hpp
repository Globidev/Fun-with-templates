#pragma once

#include <iterator>

#include "maybe_t.hpp"

#include "../compose.hpp"

namespace functional {
    namespace maybe {

        static struct _cat_maybes: composable<1, _cat_maybes> {

            template <class T, template <class...> class C>
            auto operator()(const C<maybe_t<T>> & c) const {
                using std::distance;

                typename C<T>::size_type count = 0;
                C<T> r(distance(c.begin(), c.end()));

                auto out_it = r.begin();
                auto push = [&out_it](auto val) {
                    *out_it = val;
                    return true;
                };
                for (auto in_it = c.begin(); in_it != c.end(); ++in_it)
                    if (in_it->visit(push, false))
                    {
                        ++out_it;
                        ++count;
                    }
                r.resize(count);

                return r;
            }

        } cat_maybes;

    }
}
