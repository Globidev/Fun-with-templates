#pragma once

#include <iterator>
#include <numeric>

#include "../../../compose.hpp"
#include "../../../flip.hpp"

#include "type_traits/iterators.hpp"

namespace functional {
    namespace list {

        using namespace type_traits::iterators;

        static struct _foldr: composable<3, _foldr> {

            template <
                class F,
                class V,
                class C,
                class enabler = enable_for<C, bidirectional, random_access>
            >
            auto operator()(const F & f, const V & v, const C & c) const {
                using std::accumulate;

                return accumulate(c.rbegin(), c.rend(), v, flip(f));
            }

            template <
                class F,
                class V,
                class C,
                class enabler = enable_for<C, forward, input>,
                class = void
            >
            auto operator()(const F & f, const V & v, const C & c) const {
                return accumr(flip(f), v, c.begin(), c.end());
            }

        private:

            template <class F, class V, class It>
            auto accumr(const F & f, const V & v,
                        const It & begin, const It & end) const {
                using std::next;

                if (begin == end)
                    return v;
                return f(accumr(f, v, next(begin), end), *begin);
            }

        } foldr;

    }
}
