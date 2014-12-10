#pragma once

#include <stdexcept>
#include <iterator>

#include "../../compose.hpp"

#include "type_traits/iterators.hpp"

namespace functional {
    namespace list {

        using namespace type_traits::iterators;

        static struct _init: composable<1, _init> {

            template <
                class C,
                class enabler = enable_for<C, bidirectional, random_access>
            >
            auto operator()(const C & c) const {
                using std::out_of_range;
                using std::prev;

                if (c.empty())
                    throw out_of_range(__func__);

                return C { c.begin(), prev(c.end()) };
            }

            template <
                class C,
                class enabler = enable_for<C, forward, input>,
                class = void
            >
            auto operator()(const C & c) const {
                using std::out_of_range;
                using std::distance;
                using std::advance;

                if (c.empty())
                    throw out_of_range(__func__);

                auto it = c.begin();
                advance(it, distance(c.begin(), c.end()) - 1);

                return C { c.cbegin(), it };
            }

        } init;

    }
}
