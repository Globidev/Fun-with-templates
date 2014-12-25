#pragma once

#include <tuple>
#include <algorithm>

#include "../../../compose.hpp"

namespace functional {
    namespace list {

        template <template <class...> class C>
        struct _unfoldr: composable<2, _unfoldr<C>> {

            template <
                class F,
                class T,
                class enabler = enable_for<C<T>, bidirectional, random_access>
            >
            auto operator()(const F & f, const T & t) const {
                using MaybeR = typename std::result_of<F(T)>::type;
                using Tuple = typename MaybeR::type;
                using R = typename std::tuple_element<0, Tuple>::type;
                using std::get;
                using std::move;

                C<R> r;
                Tuple rt;
                auto mb_r = f(t);
                auto on_just = [&rt](const Tuple & v) {
                    rt = move(v);
                    return true;
                };

                while (mb_r.visit(on_just, false))
                {
                    r.push_back(get<0>(rt));
                    mb_r = f(get<1>(rt));
                }

                return r;
            }

            template <
                class F,
                class T,
                class enabler = enable_for<C<T>, forward, input>,
                class = void
            >
            auto operator()(const F & f, const T & t) const {
                using MaybeR = typename std::result_of<F(T)>::type;
                using Tuple = typename MaybeR::type;
                using R = typename std::tuple_element<0, Tuple>::type;
                using std::get;
                using std::move;

                C<R> r;
                Tuple rt;
                auto mb_r = f(t);
                auto on_just = [&rt](const Tuple & v) {
                    rt = move(v);
                    return true;
                };

                auto out_it = r.before_begin();
                while (mb_r.visit(on_just, false))
                {
                    out_it = r.insert_after(out_it, get<0>(rt));
                    mb_r = f(get<1>(rt));
                }

                return r;
            }

        };

        template <template <class...> class C>
        static _unfoldr<C> unfoldr = { };
    }
}
