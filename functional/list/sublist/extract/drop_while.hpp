#pragma once

#include "../../../compose.hpp"

namespace functional {
    namespace list {

        static struct _drop_while: composable<2, _drop_while> {

            template <class C, class F>
            auto operator()(const F & f, const C & c) const {
                auto start = c.begin();
                while (start != c.end() && f(*start))
                    ++start;

                return C { start, c.end() };
            }

        } drop_while;

    }
}
