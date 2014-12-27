#pragma once

#include <tuple>
#include <iterator>

#include "../../../compose.hpp"

#include "type_traits/iterators.hpp"

namespace functional {
    namespace list {

        using namespace type_traits::iterators;

        static struct _map_accum_r: composable<3, _map_accum_r> {

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

                auto out_it = cr.begin();
                for (auto it = c.rbegin(); it != c.rend(); ++it)
                {
                    auto tuple = f(t, *it);
                    out_it = cr.insert(out_it, get<1>(tuple));
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

                C<R> cr;

                reverse_helper(cr, t, c.begin(), c.end(), f);

                return make_tuple(t, cr);
            }

        private:

            template <class C, class T, class It, class F>
            static inline void reverse_helper(C & c, T & t, const It & it,
                                              const It & end, const F & f) {
                using std::next;
                using std::get;
                using std::move;

                if (it != end)
                {
                    reverse_helper(c, t, next(it), end, f);
                    auto tuple = f(t, *it);
                    c.insert_after(c.before_begin(), get<1>(tuple));
                    t = move(get<0>(tuple));
                }
            }

        } map_accum_r;

    }
}
