#pragma once

#include "../reduce/foldr.hpp"
#include "../../basic/append.hpp"
#include "../../../compose.hpp"

namespace functional {
    namespace list {

        struct {

            template <class F, class C>
            auto operator()(const F & f, const C & c) const {
                return foldr(make_composable<2>(append) ^ make_composable<1>(f), C{}, c);
            }

        } concat_map;

    }
}
