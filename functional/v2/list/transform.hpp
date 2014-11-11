#pragma once

#include "basic.hpp"

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

            struct {

                template <class C>
                auto operator()(const C & c) const
                    -> enable_for_iterators<
                        C, bidirectional_iterator_tag, C
                    > {
                    return C { c.rbegin(), c.rend() };
                }

                template <class C>
                auto operator()(const C & c) const
                    -> disable_for_iterators<
                        C, bidirectional_iterator_tag, C
                    > {
                    C r { c.begin(), c.end() };

                    r.reverse();

                    return r;
                }

            } reverse;

        };
    };
};
