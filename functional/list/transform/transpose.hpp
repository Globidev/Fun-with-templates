#pragma once

#include <tuple>

#include "../../compose.hpp"

#include "type_traits/iterators.hpp"

namespace functional {
    namespace list {

        using namespace type_traits::iterators;

        static struct _transpose: composable<1, _transpose> {

            template <
                class T,
                template <class...> class C,
                class enabler = enable_for<C<T>, bidirectional, random_access>
            >
            auto operator()(const C<C<T>> & c) const {
                C<C<T>> r;

                for (auto it = c.begin(); it != c.end(); ++it)
                {
                    auto r_it = r.begin();
                    for (auto it1 = it->begin(); it1 != it->end(); ++it1)
                    {
                        if (r_it == r.end())
                        {
                            r.push_back(C<T> { *it1 });
                            r_it = r.end();
                        }
                        else
                        {
                            r_it->push_back(*it1);
                            ++r_it;
                        }
                    }
                }

                return r;
            }

            template <
                class T,
                template <class...> class C,
                class enabler = enable_for<C<T>, forward, input>,
                class = void
            >
            auto operator()(const C<C<T>> & c) const {
                using IterRange = std::tuple<
                    typename C<T>::const_iterator,
                    typename C<T>::const_iterator
                >;
                using std::get;
                C<C<T>> r;
                auto out_it = r.before_begin();
                C<IterRange> iters;

                auto iter_out_it = iters.before_begin();
                for (auto it = c.begin(); it != c.end(); ++it)
                    iter_out_it = iters.emplace_after(iter_out_it, it->begin(),
                                                      it->end());

                while (true)
                {
                    C<T> cr;
                    bool found = false;
                    auto cr_out_it = cr.before_begin();
                    for (auto it = iters.begin(); it != iters.end(); ++it)
                    {
                        if (get<0>(*it) != get<1>(*it))
                        {
                            found = true;
                            cr_out_it = cr.insert_after(cr_out_it, *get<0>(*it));
                            ++(get<0>(*it));
                        }
                    }
                    if (!found)
                        break ;
                    out_it = r.insert_after(out_it, cr);
                }

                return r;
            }

        } transpose;

    }
}
