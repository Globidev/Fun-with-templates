#pragma once

namespace functional {
    namespace list {

        template <template <class> class F> struct map {

            template <class V, template <class...> class C>
            auto operator()(const C<V> & c) const {
                using std::transform;
                using std::result_of;
                using Vr = typename result_of<F<V>(V)>::type;

                C<Vr> r(c.size());

                transform(c.begin(), c.end(), r.begin(), F<V>{});

                return r;
            }

        };

        namespace impl {

            template <template <class> class F>
            struct map<F> map;

        };
    };
};
