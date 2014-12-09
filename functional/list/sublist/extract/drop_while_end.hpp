#pragma once

#include <iterator>

#include "../../../compose.hpp"

#include "type_traits/iterators.hpp"

namespace functional {
    namespace list {

        using namespace type_traits::iterators;

        struct _drop_while_end: composable<2, _drop_while_end> {

            template <
                class C,
                class F,
                class enabler = enable_for<C, bidirectional, random_access>
            >
            auto operator()(const F & f, const C & c) const {
                using std::prev;
                using std::next;

                auto end = c.end();
                while(end-- != c.begin() && f(*end));

                return C { c.begin(), next(end) };
            }

            template <
                class C,
                class F,
                class enabler = enable_for<C, forward, input>,
                class = void
            >
            auto operator()(const F & f, const C & c) const {
                using std::next;

                auto end = c.begin();
                for (auto it = c.begin(); it != c.end(); ++it)
                    if (!f(*it))
                        end = next(it);

                return C { c.begin(), end };
            }

        } drop_while_end;

    }
}
