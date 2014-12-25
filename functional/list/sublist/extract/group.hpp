#pragma once

#include <iterator>

#include "../../../compose.hpp"

#include "type_traits/iterators.hpp"

namespace functional {
    namespace list {

        using namespace type_traits::iterators;

        static struct _group: composable<1, _group> {

            template <
                class T,
                template <class...> class C,
                class enabler = enable_for<C<T>, bidirectional, random_access>
            >
            auto operator()(const C<T> & c) const {
                using std::next;

                C<C<T>> r;

                auto it = c.begin();
                while (it != c.end())
                {
                    auto end = next(it);
                    while (end != c.end() && *end == *it)
                        ++end;
                    r.emplace_back(it, end);
                    it = end;
                }

                return r;
            }

            template <
                class T,
                template <class...> class C,
                class enabler = enable_for<C<T>, forward, input>,
                class = void
            >
            auto operator()(const C<T> & c) const {
                using std::next;

                C<C<T>> r;

                auto it = c.begin();
                auto out_it = r.before_begin();
                while (it != c.end())
                {
                    auto end = next(it);
                    while (end != c.end() && *end == *it)
                        ++end;
                    out_it = r.emplace_after(out_it, it, end);
                    it = end;
                }

                return r;
            }

        } group;

    }
}
