#pragma once

namespace functional {
    namespace list {

        template <class F> struct zip_with {

            template <class V1, class V2, template <class...> class C>
            auto operator()(const C<V1> & c1, const C<V2> & c2) const {
                using std::min;
                using std::result_of;
                using Vr = typename result_of<F(V1, V2)>::type;

                auto min_size = min(c1.size(), c2.size());
                C<Vr> r(min_size);
                F f;

                for (decltype(min_size) i = 0; i < min_size; ++i)
                    r[i] = f(c1[i], c2[i]);

                return r;
            }
        };

        namespace impl {

            template <class F>
            struct zip_with<F> zip_with;

        };
    };
};
