#pragma once

#include "../../../compose.hpp"

namespace functional {
    namespace list {

        struct _or: composable<1, _or> {

            template <class C>
            auto operator()(const C & c) const {
                for (auto it = c.begin(); it != c.end(); ++it)
                    if (*it)
                        return true;
                return false;
            }

        } or_;

    }
}
