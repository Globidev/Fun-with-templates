#pragma once

#include "../../compose.hpp"

namespace functional {
    namespace list {

        struct _null: composable<1, _null> {

            template <class C>
            auto operator()(const C & c) const {
                return c.empty();
            }

        } null;

    }
}
