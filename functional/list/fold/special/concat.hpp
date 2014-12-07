#pragma once

#include "../reduce/foldr.hpp"

namespace functional {
    namespace list {

        struct {

            template <class C, template <class...> class CC>
            auto operator()(const CC<C> & cc) const {
                return foldr(append, C{}, cc);
            }

        } concat;

    }
}
