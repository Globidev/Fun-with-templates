#pragma once

#include <iterator>

#include "../../../compose.hpp"

#include "type_traits/iterators.hpp"

namespace functional {
    namespace list {

        using namespace type_traits::iterators;

        static struct _tails: composable<1, _tails> {

            template <
                class T,
                template <class...> class C,
                class enabler = enable_for<C<T>, bidirectional, random_access>
            >
            auto operator()(const C<T> & c) const {
                C<C<T>> r;

                for (auto it = c.begin(); it != c.end(); ++it)
                    r.emplace_back(it, c.end());
                r.emplace_back(c.end(), c.end());

                return r;
            }

            template <
                class T,
                template <class...> class C,
                class enabler = enable_for<C<T>, forward, input>,
                class = void
            >
            auto operator()(const C<T> & c) const {
                C<C<T>> r;

                auto out_it = r.before_begin();
                for (auto it = c.begin(); it != c.end(); ++it)
                    out_it = r.emplace_after(out_it, it, c.end());
                r.emplace_after(out_it, c.end(), c.end());

                return r;
            }

        } tails;

    }
}
