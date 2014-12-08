#pragma once

#include "../reduce/foldr.hpp"
#include "../../basic/append.hpp"
#include "../../../compose.hpp"

namespace functional {
    namespace list {

        struct _concat_map: composable<2, _concat_map> {

            template <class F, class C>
            auto operator()(const F & f, const C & c) const {
                return foldr(append ^ make_composable<1>(f), C{}, c);
            }

        } concat_map;

    }
}
