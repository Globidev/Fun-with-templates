#pragma once

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
                    class enabler = enable_for<C, forward>
                >
                auto operator()(const C & c, enabler * = nullptr) const {
                    C r { c.begin(), c.end() };

                    r.reverse();

                    return r;
                }

            } reverse;

        };
    };
};
