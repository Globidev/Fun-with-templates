#pragma once

#include <algorithm>
#include <iterator>

#include "../../compose.hpp"

#include "type_traits/iterators.hpp"

namespace functional {
    namespace list {

        using namespace type_traits::iterators;

        static struct _filter: composable<2, _filter> {

            template <
                class F,
                class C,
                class enabler = enable_for<C, bidirectional, random_access>
            >
            auto operator()(const F & pred, const C & c) const {
                using std::copy_if;
                using std::back_inserter;

                C r;

                copy_if(c.begin(), c.end(), back_inserter(r), pred);

                return r;
            }

            template <
                class F,
                class C,
                class enabler = enable_for<C, forward, input>,
                class = void
            >
            auto operator()(const F & pred, const C & c) const {
                C r;

                auto out_it = r.before_begin();
                for (auto it = c.begin(); it != c.end(); ++it)
                    if (pred(*it))
                        out_it = r.insert_after(out_it, *it);

                return r;
            }

        } filter;

    }
}
