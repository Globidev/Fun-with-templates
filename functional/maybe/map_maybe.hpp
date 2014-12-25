#pragma once

#include <iterator>
#include <type_traits>

#include "maybe_t.hpp"

#include "../compose.hpp"

namespace functional {
    namespace maybe {

        static struct _map_maybe: composable<2, _map_maybe> {

            template <class F, class T, template <class...> class C>
            auto operator()(const F & f, const C<T> & c) const {
                using std::distance;
                using std::result_of;
                using MaybeR = typename result_of<F(T)>::type;
                using R = typename MaybeR::type;

                typename C<R>::size_type count = 0;
                C<R> r(distance(c.begin(), c.end()));

                auto out_it = r.begin();
                auto push = [&out_it](auto val) {
                    *out_it = val;
                    return true;
                };
                for (auto in_it = c.begin(); in_it != c.end(); ++in_it)
                {
                    auto maybe_r = f(*in_it);
                    if (maybe_r.visit(push, false))
                    {
                        ++out_it;
                        ++count;
                    }
                }
                r.resize(count);

                return r;
            }

        } map_maybe;

    }
}
