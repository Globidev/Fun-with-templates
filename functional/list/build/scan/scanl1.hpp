#pragma once

#include <iterator>

#include "../../../compose.hpp"

#include "type_traits/iterators.hpp"

namespace functional {
    namespace list {

        using namespace type_traits::iterators;

        static struct _scanl1: composable<2, _scanl1> {

            template <
                class F,
                class C,
                class enabler = enable_for<C, bidirectional, random_access>
            >
            auto operator()(const F & f, const C & c) const {
                using std::next;

                C r;

                if (!c.empty())
                {
                    r.push_back(c.front());
                    for (auto it = next(c.begin()); it != c.end(); ++it)
                        r.push_back(f(r.back(), *it));
                }

                return r;
            }

            template <
                class F,
                class C,
                class enabler = enable_for<C, forward, input>,
                class = void
            >
            auto operator()(const F & f, const C & c) const {
                using std::next;

                C r;

                if (!c.empty())
                {
                    auto out_it = r.insert_after(r.before_begin(), c.front());
                    for (auto it = next(c.begin()); it != c.end(); ++it)
                        out_it = r.insert_after(out_it, f(*out_it, *it));
                }

                return r;
            }

        } scanl1;

    }
}
