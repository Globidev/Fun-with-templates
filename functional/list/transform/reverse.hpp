#pragma once

#include "../../compose.hpp"

#include "type_traits/iterators.hpp"

namespace functional {
    namespace list {

        using namespace type_traits::iterators;

        static struct _reverse: composable<1, _reverse> {

            template <
                class C,
                class enabler = enable_for<C, bidirectional, random_access>
            >
            auto operator()(const C & c) const {
                return C { c.rbegin(), c.rend() };
            }

            template <
                class C,
                class enabler = enable_for<C, forward>,
                class = void
            >
            auto operator()(const C & c) const {
                C r { c.begin(), c.end() };

                r.reverse();

                return r;
            }

        } reverse;

    }
}
