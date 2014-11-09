#pragma once

namespace functional {
    namespace list {

        template <class F> struct map {

            template <class V, template <class...> class C>
            auto operator()(const C<V> & c) const {
                using std::transform;
                using std::result_of;
                using Vr = typename result_of<F(V)>::type;

                C<Vr> r(c.size());

                transform(c.begin(), c.end(), r.begin(), F{});

                return r;
            }

        };

        namespace impl {

            template <class F>
            struct map<F> map;

        };
    };
};
