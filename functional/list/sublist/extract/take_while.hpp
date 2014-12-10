#pragma once

#include "../../../compose.hpp"

namespace functional {
    namespace list {

        static struct _take_while: composable<2, _take_while> {

            template <class C, class F>
            auto operator()(const F & f, const C & c) const {
                auto end = c.begin();
                while (end != c.end() && f(*end))
                    ++end;

                return C { c.begin(), end };
            }

        } take_while;

    }
}
