#pragma once

#include <iterator>

#include "../../../compose.hpp"

#include "type_traits/iterators.hpp"

namespace functional {
    namespace list {

        using namespace type_traits::iterators;

        static struct _scanr1: composable<2, _scanr1> {

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
                    r.push_back(c.back());
                    auto out_it = r.begin();
                    for (auto it = next(c.rbegin()); it != c.rend(); ++it)
                        out_it = r.insert(out_it, f(*it, *out_it));
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

                if (!c.empty())
                    reverse_helper(r, c.begin(), c.end(), f);

                return r;
            }

        private:

            template <class Cr, class It, class F>
            static inline void reverse_helper(Cr & r, const It & it,
                                              const It & end, const F & f) {
                using std::next;

                auto n_it = next(it);
                if (n_it != end)
                {
                    reverse_helper(r, n_it, end, f);
                    r.insert_after(r.before_begin(), f(*it, r.front()));
                }
                else
                    r.insert_after(r.before_begin(), *it);
            }

        } scanr1;

    }
}
