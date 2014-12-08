#pragma once

#include <stdexcept>
#include <iterator>

#include "../../compose.hpp"

#include "type_traits/iterators.hpp"

namespace functional {
    namespace list {

        using namespace type_traits::iterators;

        struct _last: composable<1, _last> {

            template <
                class C,
                class enabler = enable_for<C, bidirectional, random_access>
            >
            auto operator()(const C & c) const {
                using std::out_of_range;

                if (c.empty())
                    throw out_of_range(__func__);

                return c.back();
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

                return *it;
            }

        } last;

    }
}
