#pragma once

#include "../../compose.hpp"

#include "type_traits/iterators.hpp"

namespace functional {
    namespace list {

        using namespace type_traits::iterators;

        static struct _delete_by: composable<3, _delete_by> {

            template <
                class F,
                class T,
                template <class...> class C,
                class enabler = enable_for<C<T>, bidirectional, random_access>
            >
            auto operator()(const F & f, const T & t, const C<T> & c) const {
                C<T> r;

                auto it = c.begin();
                while (it != c.end())
                {
                    if (f(*it, t))
                    {
                        ++it;
                        break ;
                    }
                    r.push_back(*it++);
                }
                while (it != c.end())
                    r.push_back(*it++);

                return r;
            }

            template <
                class F,
                class T,
                template <class...> class C,
                class enabler = enable_for<C<T>, forward, input>,
                class = void
            >
            auto operator()(const F & f, const T & t, const C<T> & c) const {
                C<T> r;

                auto out_it = r.before_begin();
                auto it = c.begin();
                while (it != c.end())
                {
                    if (f(*it, t))
                    {
                        ++it;
                        break ;
                    }
                    out_it = r.insert_after(out_it, *it++);
                }
                while (it != c.end())
                    out_it = r.insert_after(out_it, *it++);

                return r;
            }

        } delete_by;

    }
}
