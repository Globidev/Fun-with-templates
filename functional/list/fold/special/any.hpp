#pragma once

#include "../../../compose.hpp"

namespace functional {
    namespace list {

        struct _any: composable<2, _any> {

            template <class F, class C>
            auto operator()(const F & f, const C & c) const {
                for (auto it = c.begin(); it != c.end(); ++it)
                    if (f(*it))
                        return true;
                return false;
            }

        } any;

    }
}
