#pragma once

#include "../../../compose.hpp"

namespace functional {
    namespace list {

        static struct _and: composable<1, _and> {

            template <class C>
            auto operator()(const C & c) const {
                for (auto it = c.begin(); it != c.end(); ++it)
                    if (!*it)
                        return false;
                return true;
            }

        } and_;

    }
}
