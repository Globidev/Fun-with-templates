#pragma once

#include "../../compose.hpp"

#include "type_traits/iterators.hpp"

namespace functional {
    namespace list {

        using namespace type_traits::iterators;

        static struct _elem_indices: composable<2, _elem_indices> {

            template <
                class T,
                template <class...> class C,
                class enabler = enable_for<C<T>, random_access, bidirectional>
            >
            auto operator()(const T & t, const C<T> & c) const {
                using R = typename C<T>::size_type;

                R i {};
                C<R> r;

                for (auto it = c.begin(); it != c.end(); ++it, ++i)
                    if (*it == t)
                        r.push_back(i);

                return r;
            }

            template <
                class T,
                template <class...> class C,
                class enabler = enable_for<C<T>, forward, input>,
                class = void
            >
            auto operator()(const T & t, const C<T> & c) const {
                using R = typename C<T>::size_type;

                R i {};
                C<R> r;

                auto out_it = r.before_begin();
                for (auto it = c.begin(); it != c.end(); ++it, ++i)
                    if (*it == t)
                        out_it = r.insert_after(out_it, i);

                return r;
            }

        } elem_indices;

    }
}
