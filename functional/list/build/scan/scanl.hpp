#pragma once

#include <iterator>

#include "../../../compose.hpp"

#include "type_traits/iterators.hpp"

namespace functional {
    namespace list {

        using namespace type_traits::iterators;

        static struct _scanl: composable<3, _scanl> {

            template <
                class F,
                class T,
                class U,
                template <class...> class C,
                class enabler = enable_for<C<U>, bidirectional, random_access>
            >
            auto operator()(const F & f, const T & t, const C<U> & c) const {
                C<T> r;

                r.push_back(t);
                for (auto it = c.begin(); it != c.end(); ++it)
                    r.push_back(f(r.back(), *it));

                return r;
            }

            template <
                class F,
                class T,
                class U,
                template <class...> class C,
                class enabler = enable_for<C<U>, forward, input>,
                class = void
            >
            auto operator()(const F & f, const T & t, const C<U> & c) const {
                C<T> r;

                auto out_it = r.insert_after(r.before_begin(), t);
                for (auto it = c.begin(); it != c.end(); ++it)
                    out_it = r.insert_after(out_it, f(*out_it, *it));

                return r;
            }

        } scanl;

    }
}
