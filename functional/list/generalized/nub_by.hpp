#pragma once

#include "../../compose.hpp"

#include "type_traits/iterators.hpp"

namespace functional {
    namespace list {

        using namespace type_traits::iterators;

        static struct _nub_by: composable<2, _nub_by> {

            template <
                class F,
                class C,
                class enabler = enable_for<C, bidirectional, random_access>
            >
            auto operator()(const F & f, const C & c) const {
                C r;

                for (auto it = c.begin(); it != c.end(); ++it)
                {
                    bool dup = false;
                    for (auto it2 = r.begin(); it2 != r.end(); ++it2)
                        if (f(*it, *it2))
                        {
                            dup = true;
                            break;
                        }
                    if (!dup)
                        r.push_back(*it);
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
                C r;

                auto out_it = r.before_begin();
                for (auto it = c.begin(); it != c.end(); ++it)
                {
                    bool dup = false;
                    for (auto it2 = r.begin(); it2 != r.end(); ++it2)
                        if (f(*it, *it2))
                        {
                            dup = true;
                            break;
                        }
                    if (!dup)
                        out_it = r.insert_after(out_it, *it);
                }

                return r;
            }

        } nub_by;

    }
}
