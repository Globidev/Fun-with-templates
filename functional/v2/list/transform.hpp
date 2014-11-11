#pragma once

#include <algorithm>
#include <type_traits>

namespace functional {
    namespace v2 {
        namespace list {

            struct {

                template <class F, class V, template <class...> class C>
                auto operator()(const F & f, const C<V> & c) const {
                    using std::distance;
                    using std::transform;
                    using std::result_of;
                    using Vr = typename result_of<F(V)>::type;

                    C<Vr> r(distance(c.begin(), c.end()));

                    transform(c.begin(), c.end(), r.begin(), f);

                    return r;
                }

            } map;

        };
    };
};
