#pragma once

#include <stdexcept>
#include <iterator>
#include <numeric>

#include "../../../compose.hpp"
#include "../../../flip.hpp"

#include "type_traits/iterators.hpp"

namespace functional {
    namespace list {

        using namespace type_traits::iterators;

        static struct _foldr1: composable<2, _foldr1> {

            template <
                class F,
                class C,
                class enabler = enable_for<C, bidirectional, random_access>
            >
            auto operator()(const F & f, const C & c) const {
                using std::out_of_range;
                using std::next;
                using std::accumulate;

                if (c.empty())
                    throw(out_of_range(__func__));

                return accumulate(next(c.rbegin()), c.rend(), c.back(), flip(f));
            }

            template <
                class F,
                class C,
                class enabler = enable_for<C, forward, input>,
                class = void
            >
            auto operator()(const F & f, const C & c) const {
                return accumr(flip(f), c.begin(), c.end());
            }

        private:

            template <class F, class It>
            auto accumr(const F & f, const It & begin,
                        const It & end) const {
                using std::next;

                if (next(begin) == end)
                    return *begin;
                return f(accumr(f, next(begin), end), *begin);
            }

        } foldr1;

    }
}
