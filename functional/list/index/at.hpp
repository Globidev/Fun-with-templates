#pragma once

#include <stdexcept>
#include <iterator>

#include "../../compose.hpp"

#include "type_traits/iterators.hpp"

namespace functional {
    namespace list {

        using namespace type_traits::iterators;

        static struct _at: composable<2, _at> {

            template <
                class C,
                class enabler = enable_for<C, random_access>
            >
            auto operator()(const C & c,
                            const typename C::size_type & i) const {
                return c.at(i);
            };

            template <
                class C,
                class enabler = enable_for<C, bidirectional, forward, input>,
                class = void
            >
            auto operator()(const C & c,
                            const typename C::difference_type & i) const {
                using std::out_of_range;
                using std::distance;
                using std::advance;

                if (i >= distance(c.begin(), c.end()))
                    throw out_of_range(__func__);

                auto it = c.begin();
                advance(it, i);

                return *it;
            };

        } at;

    }
}
