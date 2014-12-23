#pragma once

#include <algorithm>

#include "../../compose.hpp"

namespace functional {
    namespace list {

        static struct _not_elem: composable<2, _not_elem> {

            template <class T, template <class...> class C>
            auto operator()(const T & t, const C<T> & c) const {
                using std::find;

                auto found = find(c.begin(), c.end(), t);

                return found == c.end();
            }

        } not_elem;

    }
}
