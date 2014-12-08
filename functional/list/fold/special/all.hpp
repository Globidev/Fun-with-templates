#pragma once

#include "../../../compose.hpp"

namespace functional {
    namespace list {

        struct _all: composable<2, _all> {

            template <class F, class C>
            auto operator()(const F & f, const C & c) const {
                for (auto it = c.begin(); it != c.end(); ++it)
                    if (!f(*it))
                        return false;
                return true;
            }

        } all;

    }
}
