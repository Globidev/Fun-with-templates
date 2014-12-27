#pragma once

#include <tuple>

#include "../../../compose.hpp"

#include "type_traits/iterators.hpp"

namespace functional {
    namespace list {

        using namespace type_traits::iterators;

        static struct _map_accum_l: composable<3, _map_accum_l> {

            template <
                class F,
                class T,
                class U,
                template <class...> class C,
                class enabler = enable_for<C<U>, bidirectional, random_access>
            >
            auto operator()(const F & f, T t, const C<U> & c) const {
                using PairR = typename std::result_of<F(T, U)>::type;
                using R = typename std::tuple_element<1, PairR>::type;
                using std::get;
                using std::move;

                C<R> cr;

                for (auto it = c.begin(); it != c.end(); ++it)
                {
                    auto tuple = f(t, *it);
                    cr.push_back(get<1>(tuple));
                    t = move(get<0>(tuple));
                }

                return make_tuple(t, cr);
            }

            template <
                class F,
                class T,
                class U,
                template <class...> class C,
                class enabler = enable_for<C<U>, forward, input>,
                class = void
            >
            auto operator()(const F & f, T t, const C<U> & c) const {
                using PairR = typename std::result_of<F(T, U)>::type;
                using R = typename std::tuple_element<1, PairR>::type;
                using std::get;
                using std::move;

                C<R> cr;

                auto out_it = cr.before_begin();
                for (auto it = c.begin(); it != c.end(); ++it)
                {
                    auto tuple = f(t, *it);
                    out_it = cr.insert_after(out_it, get<1>(tuple));
                    t = move(get<0>(tuple));
                }

                return make_tuple(t, cr);
            }

        } map_accum_l;

    }
}
