#pragma once

#include <iterator>

#include "../../../compose.hpp"

#include "type_traits/iterators.hpp"

namespace functional {
    namespace list {

        using namespace type_traits::iterators;

        static struct _scanr: composable<3, _scanr> {

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
                auto out_it = r.begin();
                for (auto it = c.rbegin(); it != c.rend(); ++it)
                    out_it = r.insert(out_it, f(*it, *out_it));

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

                r.insert_after(r.before_begin(), t);
                reverse_helper(r, c.begin(), c.end(), f);

                return r;
            }

        private:

            template <class Cr, class It, class F>
            static inline void reverse_helper(Cr & r, const It & it,
                                              const It & end, const F & f) {
                using std::next;

                if (it != end)
                {
                    reverse_helper(r, next(it), end, f);
                    r.insert_after(r.before_begin(), f(*it, r.front()));
                }
            }

        } scanr;

    }
}
