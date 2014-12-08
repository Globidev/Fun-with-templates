#pragma once

#include "../reduce/foldr.hpp"
#include "../../../compose.hpp"

namespace functional {
    namespace list {

        struct _concat: composable<1, _concat> {

            template <class C, template <class...> class CC>
            auto operator()(const CC<C> & cc) const {
                return foldr(append, C{}, cc);
            }

        } concat;

    }
}
