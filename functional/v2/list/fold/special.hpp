#pragma once

#include "../basic.hpp"
#include "basic.hpp"

namespace functional {
    namespace v2 {
        namespace list {

            struct {

                template <class CC>
                auto operator()(const CC & cc) const {
                    return foldl1(append, cc);
                }

            } concat;

        };
    };
};
