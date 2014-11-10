#pragma once

#include "fold/special.hpp"

namespace functional {
    namespace v1 {
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

            struct reverse {

                template <class V, template <class...> class C>
                auto operator()(const C<V> & c) const {
                    using std::copy;

                    C<V> r(c.size());

                    copy(c.rbegin(), c.rend(), r.begin());

                    return r;
                }

            };

            struct intersperse {

                template <class V, template <class...> class C>
                auto operator()(const V & v, const C<V> & c) const {
                    auto size = (c.size() >= 2 ? c.size() * 2 - 1 : c.size());
                    C<V> r(size);

                    for (decltype(size) i = 0; i < size; ++i)
                        r[i] = (i % 2 == 0 ? c[i / 2] : v );

                    return r;
                }

            };

            struct intercalate {

                template <
                    class V,
                    template <class...> class C,
                    template <class...> class CC
                >
                auto operator()(const C<V> & c, const CC<C<V>> & cc) const {
                    return impl::concat(intersperse()(c, cc));
                }

            };

            namespace impl {

                template <class F> struct map<F> map = {};
                struct reverse reverse;
                struct intersperse intersperse;
                struct intercalate intercalate;

            };
        };
    };
};
