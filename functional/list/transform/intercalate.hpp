#pragma once

#include "intersperse.hpp"
#include "../fold/special/concat.hpp"
#include "../../compose.hpp"

namespace functional {
    namespace list {

        static struct _intercalate: composable<2, _intercalate> {

            template <class C, template <class...> class CC>
            auto operator()(const C & c, const CC<C> & cc) const {
                return concat(intersperse(c, cc));
            }

        } intercalate;

    }
}
