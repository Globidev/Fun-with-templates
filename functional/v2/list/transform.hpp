#pragma once

#include <algorithm>

#include "iterator_traits.hpp"

namespace functional {
    namespace v2 {
        namespace list {

            using namespace iterator_traits;

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

            struct {

                template <
                    class C,
                    class enabler = enable_for<C, bidirectional, random_access>
                >
                auto operator()(const C & c) const {
                    return C { c.rbegin(), c.rend() };
                }

                template <
                    class C,
                    class enabler = enable_for<C, forward>,
                    class = void
                >
                auto operator()(const C & c) const {
                    C r { c.begin(), c.end() };

                    r.reverse();

                    return r;
                }

            } reverse;

            struct {

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

        };
    };
};
